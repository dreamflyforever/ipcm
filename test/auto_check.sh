datename=$(date +%Y%m%d-%H%M%S)
count=0;
while (( $count < 10000000 ));
do
mosquitto_pub -h 0.0.0.0 -p 1883 -t pd/usbinit -m $(date +%Y%m%d-%H%M%S) &
mosquitto_pub -h 0.0.0.0 -p 1883 -t pd/send/usb -m "hello" &
mosquitto_pub -h 0.0.0.0 -p 1883 -t pd/send/esp32 -m "world" &

((count=$count+1));
echo $count
done;
