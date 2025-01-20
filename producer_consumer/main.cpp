#include <iostream>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <queue>
#include <vector>
#include <chrono>
#include <random>

// Must use g++ -std=c++11 main.cpp -o main, C++ version must be >= 11 to have lambda, auto and range based loops

std::queue<int> buffer;
const int BUFFER_SIZE = 10;

std::mutex mutex;
std::condition_variable cv_producer, cv_consumer;

void producer(int id, int num_items) {
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(1, 100);
    int delay = 100;

    for (int i = 0; i < num_items; ++i) {
        int item = distribution(generator);

        std::unique_lock<std::mutex> lock(mutex);

        cv_producer.wait(lock, [&]{ return buffer.size() < BUFFER_SIZE; });

        buffer.push(item);

        std::cout << "Producer: " << id << " Produced: " << item << std::endl;

        cv_consumer.notify_one();

        lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

void consumer(int id, int num_items) {
    int delay = 100;

    for (int i = 0; i < num_items; ++i) {
        int item;

        std::unique_lock<std::mutex> lock(mutex);

        cv_consumer.wait(lock, [&]{ return !buffer.empty(); });

        item = buffer.front();
        buffer.pop();

        std::cout << "Consumer: " << id << " Consumed: " << item << std::endl;

        cv_producer.notify_one();

        lock.unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(delay));
    }
}

int main() {
    int num_producers = 4, num_consumers = 4, num_items = 5;

    std::vector<std::thread> producers, consumers;

    for (int i = 0; i < num_producers; ++i) {
        producers.emplace_back(producer, i, num_items);
    }

    for (int i = 0; i < num_consumers; ++i) {
        consumers.emplace_back(consumer, i, num_items);
    }

    for (auto& p : producers) p.join();
    for (auto& c : consumers) c.join();

    return 0;
}
