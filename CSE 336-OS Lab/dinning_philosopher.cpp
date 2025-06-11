#include <iostream>
#include <thread>
#include <mutex>

const int NUM_PHILOSOPHERS = 5;

std::mutex chopsticks[NUM_PHILOSOPHERS];

void philosopher(int id) {
    int left = id;
    int right = (id + 1) % NUM_PHILOSOPHERS;

    // Acquire chopsticks in a fixed order to prevent deadlock
    std::unique_lock<std::mutex> leftLock(chopsticks[left]);
    std::unique_lock<std::mutex> rightLock(chopsticks[right]);

    std::cout << "Philosopher " << id << " is eating" << std::endl;
    // Simulate eating
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    std::cout << "Philosopher " << id << " has finished eating" << std::endl;
}

int main() {
    std::thread philosophers[NUM_PHILOSOPHERS];

    // Start philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers[i] = std::thread(philosopher, i);
    }

    // Join philosopher threads
    for (int i = 0; i < NUM_PHILOSOPHERS; ++i) {
        philosophers[i].join();
    }

    return 0;
}
