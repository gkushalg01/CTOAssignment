#include <mqtt/async_client.h>
#include <iostream>

int main() {
    const std::string server_address = "tcp://localhost:1883";
    const std::string client_id = "mqtt-subscriber";

    try {
        mqtt::async_client client(server_address, client_id);

        mqtt::connect_options connOpts;
        client.connect(connOpts)->wait();

        // Subscriber
        std::string topic = "test";
        int qos = 1;

        client.subscribe(topic, qos)->wait();

        // Message callback for incoming messages
        client.set_message_callback([](const mqtt::const_message_ptr& msg) {
            std::cout << "Received message: " << msg->to_string() << std::endl;
        });

        std::cout << "Subscriber is now listening for messages." << std::endl;

        // Keep the program running indefinitely
        std::this_thread::sleep_for(std::chrono::hours(1));

        // Disconnect from the broker
        client.disconnect()->wait();

    } catch (const mqtt::exception& exc) {
        std::cerr << "MQTT Exception: " << exc.what() << std::endl;
        return 1;
    }

    return 0;
}
