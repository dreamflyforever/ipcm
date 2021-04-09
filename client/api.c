
#include <pthread.h>
#include "api.h"

static const char *s_url = "mqtt://0.0.0.0:1883";
static const char *s_topic = "mg/test";

struct node_str node_obj;
pthread_t _node_thread;

void *_node_loop(void *arg);
int pub(char *topic, char *data, int len)
{
	int retval;
	int i = 0;
	while (node_obj.state == false) {
		printf("[%s %d]no connect\n", __func__, __LINE__);
		sleep(1);
		i++;
		if (i >= 10) goto _OUT;
	}
	struct mg_str topic_str = mg_str(topic), data_n = mg_str_n(data, len);

	/*XXX:return*/
	mg_mqtt_pub(node_obj.mgc, &topic_str, &data_n);
_OUT:
	return retval;
}

int sub(char *topic, sub_cb cb)
{
	int retval;
	int len = strlen(topic);
	int i = 0;
	while (node_obj.state == false) {
		printf("[%s %d]no connect\n", __func__, __LINE__);
		sleep(1);
		i++;
		if (i >= 10) goto _OUT;
	}
	node_obj.sub_obj[node_obj.sub_index].topic = malloc(len+1);
	strncpy(node_obj.sub_obj[node_obj.sub_index].topic, topic, len);
	node_obj.sub_obj[node_obj.sub_index].cb = cb;
	node_obj.sub_index++;
	if (node_obj.sub_index >= SUB_COUNT) {
		printf("error: sub topic number > %d\n", SUB_COUNT);
		exit(0);
	}
	struct mg_str topic_str = mg_str(topic);
	mg_mqtt_sub(node_obj.mgc, &topic_str);
_OUT:
	return retval;
}

/*block the process*/
int mqtt_init(void)
{
	if (pthread_create(&_node_thread,
		NULL, _node_loop, NULL)
		!= 0) {
        	printf("Create thread error!\n");
        	exit(1);
	}
	printf("node thread create success\n");
	return 0;
}

int mqtt_deinit(void)
{
	int i;
	node_obj.state = false;
	mg_mgr_free(&(node_obj.mgr));
	for (i = 0; i <= node_obj.sub_index; i++) {
		free(node_obj.sub_obj[i].topic);
	}
	/*destroy node thread*/
}

int hello_cb(int fd, char *data, int len)
{
	printf("[%s %d]data: %.*s\n", __func__, __LINE__, len, data);
	return 0;
}

int world_cb(int fd, char *data, int len)
{
	printf("[%s %d]data: %.*s\n", __func__, __LINE__, len, data);
	return 0;
}
static void fn(struct mg_connection *c, int ev, void *ev_data, void *fn_data) {
	if (ev == MG_EV_ERROR) {
		// On error, log error message
		LOG(LL_ERROR, ("%p %s", c->fd, (char *) ev_data));
	} else if (ev == MG_EV_CONNECT) {
		// If target URL is SSL/TLS, command client connection to use TLS
		if (mg_url_is_ssl(s_url)) {
			struct mg_tls_opts opts = {.ca = "ca.pem"};
			mg_tls_init(c, &opts);
		}
	} else if (ev == MG_EV_MQTT_OPEN) {
		node_obj.state = true;
		// MQTT connect is successful
		struct mg_str topic = mg_str(s_topic), data = mg_str("hello");
		LOG(LL_INFO, ("CONNECTED to %s", s_url));
		mg_mqtt_sub(c, &topic);
		sub("hello", hello_cb);
		sub("world", world_cb);
		LOG(LL_INFO, ("SUBSCRIBED to %.*s", (int) topic.len, topic.ptr));
		mg_mqtt_pub(c, &topic, &data);
		LOG(LL_INFO, ("PUBSLISHED %.*s -> %.*s", (int) data.len, data.ptr,
					(int) topic.len, topic.ptr));
	} else if (ev == MG_EV_MQTT_MSG) {
		// When we get echo response, print it
		struct mg_mqtt_message *mm = (struct mg_mqtt_message *) ev_data;
		//LOG(LL_INFO, ("RECEIVED %.*s <- %.*s", (int) mm->data.len, mm->data.ptr,
		//			(int) mm->topic.len, mm->topic.ptr));
		int i;
		for (i = 0; i <= SUB_COUNT; i++) {
			if (node_obj.sub_obj[i].topic != NULL) {
				if (0 == strncmp(node_obj.sub_obj[i].topic, mm->topic.ptr,
					(strlen(node_obj.sub_obj[i].topic)-1))) {
					if (node_obj.sub_obj[i].cb != NULL) {
						node_obj.sub_obj[i].cb(0, (char *)mm->data.ptr, mm->data.len);
						goto _OUT;
					}
				}
			}
		}
	}

	if (ev == MG_EV_ERROR || ev == MG_EV_CLOSE ) {
		printf("mqtt close\n");
		*(bool *) fn_data = true;  // Signal that we're done
	}
_OUT:
	return ;
}

void *_node_loop(void *arg)
{
	node_obj.state = false;
	struct mg_mqtt_opts opts;  // MQTT connection options
	bool done = false;         // Event handler flips it to true when done
	mg_mgr_init(&(node_obj.mgr));         // Initialise event manager
	memset(&opts, 0, sizeof(opts));                 // Set MQTT options
	opts.qos = 1;                                   // Set QoS to 1
	opts.will_topic = mg_str(s_topic);              // Set last will topic
	opts.will_message = mg_str("goodbye");          // And last will message
	node_obj.mgc = mg_mqtt_connect(&(node_obj.mgr), s_url, &opts, fn, &done);  // Create client connection
	while (done == false) mg_mgr_poll(&(node_obj.mgr), 1000);  // Event loop
	node_obj.state = false;
}
