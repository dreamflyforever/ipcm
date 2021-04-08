gcc -g src/mqtt.c src/mqtt_pal.c simple_publisher.c -I include  -o pub -lpthread
gcc -g src/mqtt.c src/mqtt_pal.c simple_subscriber.c -I include  -o sub -lpthread
