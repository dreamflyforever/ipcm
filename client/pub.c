#include "api.h"

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

int main(void)
{
	mqtt_init();
	sub("hello", hello_cb);
	sub("world", world_cb);
	while (1) {
		printf("hello world\n");
		sleep(1);
	};
	return 0;
}
