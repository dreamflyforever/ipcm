#include "mongoose.h"
#define SUB_COUNT 10

typedef int (*sub_cb)(int fd, char *data, int len);
struct sub_str {
	char *topic;
	sub_cb cb;
};
extern struct sub_str sub_obj[SUB_COUNT];
extern struct mg_connection *mgc;

int sub(char *topic, sub_cb cb);

int pub(char *topic, char *data, int len);
