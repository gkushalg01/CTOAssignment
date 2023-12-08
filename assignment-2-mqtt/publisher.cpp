#include <mqtt/async_client.h>
#include <iostream>

int main() {
    const std::string server_address = "tcp://localhost:1883";
    const std::string client_id = "mqtt-publisher";

    try {
        mqtt::async_client client(server_address, client_id);

        mqtt::connect_options connOpts;
        client.connect(connOpts)->wait();

        // Publisher
        std::string topic = "test";
        std::string payload = "Hello, MQTT from Publisher!";
        int qos = 1;
        bool retained = false;

        mqtt::message_ptr pubmsg = mqtt::make_message(topic, payload, qos, retained);
        client.publish(pubmsg)->wait();

        std::cout << "Message published: " << payload << std::endl;

        // Disconnect from the broker
        client.disconnect()->wait();

    } catch (const mqtt::exception& exc) {
        std::cerr << "MQTT Exception: " << exc.what() << std::endl;
        return 1;
    }

    return 0;
}
