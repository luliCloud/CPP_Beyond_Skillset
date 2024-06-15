/**
 * 生产者-消费者模式：一种多线程的协作模式，用于解决两个或多个线程间的通信问题。在这个模式中，生产者
 * 线程负责生成数据，而消费者线程负责处理数据。为了防止数据竞争，通常使用同步机制（mutex，condition_variable）
 * 来控制对共享数据的访问
 */
#include <iostream>
#include <mutex>
#include <queue>
#include <condition_variable>
// #include <chrono>
#include <thread> // for this_thread?
using namespace std;

mutex mtx;
condition_variable cv;
queue<int> product;

void producer(int id) {
    for (int i = 0; i < 5; i++) {
        unique_lock<mutex> lock(mtx);
        // no need to cv.wair, as it is write data, don't need for other producer update
        product.push(id * 100 + i);
        cout << "Producer " << id << " produced " << product.back() << endl;
        cv.notify_one();
        lock.unlock(); // 离开作用域不是会自动解锁吗？为什么还需要unlcok
        /**
         * 通常情况下是不必要的，离开作用域时会自动解锁。但是在这里我们想提高并发的性能，因为接下来的
         * sleep是模拟一些耗时操作，比如I/O，所以我们需要提前解锁，方便别的thread可以先开始实行任务
         * 而不用等到该thread sleep完再开始执行其他任务
         */
        this_thread::sleep_for(chrono::microseconds(100));
    }
}

void consumer(int id) {
    for (int i = 0; i < 5; i++) {
        unique_lock<mutex> lock(mtx);
        cv.wait(lock, []{ return !product.empty(); }); // 等有数据再读
        int prod = product.front(); // pop front in queue
        product.pop();
        cout << "Consumer " << id << " consumed " << prod << endl;
        // 这里是我加的，应该也要解锁？
        lock.unlock();
        this_thread::sleep_for(chrono::microseconds(100));
    }
}

int main() {
    thread producers[2];  // array of size 2, containing producer threads
    thread consumers[2];

    for (int i = 0; i < 2; i++) {
        producers[i] = thread(producer, i + 1);
        consumers[i] = thread(consumer, i + 1);
    }

    for (int i = 0; i < 2; i++) {
        producers[i].join();
        consumers[i].join();
    }
    return 0;

}
/**
 * Producer 1 produced 100
Consumer 1 consumed 100
Producer 2 produced 200
Consumer 2 consumed 200
Producer 1 produced 101
Consumer 1 consumed 101
Producer 2 produced 201
Consumer 2 consumed 201
Producer 1 produced 102
Consumer 1 consumed 102
Producer 2 produced 202
Consumer 2 consumed 202
Producer 1 produced 103
Consumer 1 consumed 103
Producer 2 produced 203
Consumer 2 consumed 203
Producer 1 produced 104
Consumer 1 consumed 104
Producer 2 produced 204
Consumer 2 consumed 204

thread1 and 2: 对应 producer1 and consumer1
producer1: 100， push， sleep（100）
consumer1: 100， pop， sleep（100）

thread3 and 4: 对应 producer2 and consumer2
producer2: 200， push， sleep（100）
consumer2: 200， pop， sleep（100）

看上去就是先走了main里面的外循环，而不是函数里的内循环。为什么呢
因为producer and consumer 1执行完后要先sleep，这时候如果要继续执行，
就会走producer and consumer 2。所以看上去就是先走了外循环，而函数内的循环实际上是在同一个thread里
执行（注意producer一个thread，consumer 一个thread，而不是共用一个thread）所以要等待100.
另外外循环已经规定好了producer后先接对应的consumer，而不是下一个producer。所以我们会看到producer和
consumer交替进行。
 */