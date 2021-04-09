// Copyright (c) 2020 Cesanta Software Limited
// All rights reserved
//
// Example MQTT client. It performs the following steps:
//    1. Connects to the MQTT server specified by `s_url` variable
//    2. When connected, subscribes to the topic `s_topic`
//    3. Publishes message `hello` to the `s_topic`
//    4. Receives that message back from the subscribed topic and exits
//
// To enable SSL/TLS for this client, build it like this:
//    make MBEDTLS_DIR=/path/to/your/mbedtls/installation

#include "api.h"

int main(void)
{
	mqtt_init();
	while (1) {
		sleep(1);
	};
	return 0;
}
