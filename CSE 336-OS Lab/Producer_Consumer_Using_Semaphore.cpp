// #include <iostream>
// #include <thread>
// #include <mutex>
// #include <semaphore.h>
// #include <vector>
// #include <unistd.h>

// using namespace std;

// const int BUFFER_SIZE = 5;

// vector<int> buffer(BUFFER_SIZE);
// int in = 0;
// int out = 0;

// sem_t empty;
// sem_t full;
// mutex mtx;

// void produce(int item) {
//     sem_wait(&empty);
//     mtx.lock();
//     buffer[in] = item;
//     cout << "Producer Produced item no. : " << item << endl;
//     in = (in + 1) % BUFFER_SIZE;
//     mtx.unlock();
//     sem_post(&full);
// }

// void consume() {
//     sem_wait(&full);
//     mtx.lock();
//     int item = buffer[out];
//     cout << "Consumer Consumed item no. : " << item << endl;
//     out = (out + 1) % BUFFER_SIZE;
//     mtx.unlock();
//     sem_post(&empty);
// }

// void producer() {
//     for (int i = 0; i < 5; ++i) {
//         produce(i);
//         sleep(1);
//     }
// }

// void consumer() {
//     for (int i = 0; i < 5; ++i) {
//         consume();
//         sleep(2);
//     }
// }

// int main() {
//     sem_init(&empty, 0, BUFFER_SIZE);
//     sem_init(&full, 0, 0);

//     thread producer_thread(producer);
//     thread consumer_thread(consumer);

//     producer_thread.join();
//     consumer_thread.join();

//     sem_destroy(&empty);
//     sem_destroy(&full);

//     return 0;
// }



#include <iostream>
#include <thread>
#include <mutex>
#include <semaphore.h>
#include <vector>
#include <unistd.h>

using namespace std;

const int BUFFER_SIZE = 5;

vector<int> buffer(BUFFER_SIZE);
int in = 0;
int out = 0;

// Rename the semaphore to avoid conflicts
sem_t empty_slots;
sem_t full;
mutex mtx;

void produce(int item) {
    sem_wait(&empty_slots);
    mtx.lock();
    buffer[in] = item;
    cout << "Producer Produced item no. : " << item << endl;
    in = (in + 1) % BUFFER_SIZE;
    mtx.unlock();
    sem_post(&full);
}

void consume() {
    sem_wait(&full);
    mtx.lock();
    int item = buffer[out];
    cout << "Consumer Consumed item no. : " << item << endl;
    out = (out + 1) % BUFFER_SIZE;
    mtx.unlock();
    sem_post(&empty_slots);
}

void producer() {
    for (int i = 0; i < 5; ++i) {
        produce(i);
        sleep(1);
    }
}

void consumer() {
    for (int i = 0; i < 5; ++i) {
        consume();
        sleep(2);
    }
}

int main() {
    sem_init(&empty_slots, 0, BUFFER_SIZE); // Initialize with BUFFER_SIZE
    sem_init(&full, 0, 0); // Initialize with 0, since buffer starts empty

    thread producer_thread(producer);
    thread consumer_thread(consumer);

    producer_thread.join();
    consumer_thread.join();

    sem_destroy(&empty_slots);
    sem_destroy(&full);

    return 0;
}
