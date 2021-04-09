#include "api.h"

struct node_str node_obj;

int pub(char *topic, char *data, int len)
{
	int retval;
	struct mg_str topic_str = mg_str(topic), data_n = mg_str_n(data, len);

	/*XXX:return*/
	mg_mqtt_pub(node_obj.mgc, &topic_str, &data_n);
	return retval;
}

int sub(char *topic, sub_cb cb)
{
	int retval;
	int len = strlen(topic);
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
	return retval;
}
