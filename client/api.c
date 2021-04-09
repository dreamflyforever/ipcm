#include "api.h"

static int sub_index;
struct sub_str sub_obj[SUB_COUNT];
struct mg_connection *mgc;


int pub(char *topic, char *data, int len)
{
	int retval;
	struct mg_str topic_str = mg_str(topic), data_n = mg_str_n(data, len);

	/*XXX:return*/
	mg_mqtt_pub(mgc, &topic_str, &data_n);
	return retval;
}

int sub(char *topic, sub_cb cb)
{
	int retval;
	int len = strlen(topic);
	sub_obj[sub_index].topic = malloc(len+1);
	strncpy(sub_obj[sub_index].topic, topic, len);
	sub_obj[sub_index].cb = cb;
	sub_index++;
	if (sub_index >= SUB_COUNT) {
		printf("error: sub topic number > %d\n", SUB_COUNT);
		exit(0);
	}
	struct mg_str topic_str = mg_str(topic);
	mg_mqtt_sub(mgc, &topic_str);
	return retval;
}
