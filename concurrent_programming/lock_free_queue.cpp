/**
 * 无锁数据结构使用原子操作来保证线程安全，避免了锁的开销。但可能需要复杂的算法来保证操作的一致性和原子性
 * 实现：用std::atomic来实现无锁队列，栈等
 */
#include <iostream>
#include <atomic>
using namespace std;

class AtomicStack {
private:
    struct Node {
        int data;
        atomic<Node*> next; // 注意这是一个template，Node*作为输入。而不是container
    };
    alignas(64) atomic<Node*> head_{nullptr}; // 内存对齐。用花括号初始化head_，注意括号内的值要与成员变量声明的顺序一致
public:
    void push(int data) {
        Node* node = new Node{data, nullptr}; // still uniform initialization, not constructor
        // 更换head值到新node，并将node的next指向oldHead（也就是原head-）
        while (true) {
            /**
             * 加载当前head_, assign给oldHead。这个操作保证当前线程安全，但不会给其他内存操作任何同步或排序限制。
             * 加载就是将head的当前值复制到oldhead中，即一个指针。load是一个原子操作
             */
            Node* oldHead = head_.load(memory_order_relaxed); 
            node->next = oldHead; // 将新node加在oldHead前面

            /**
             * compare_exchange_weak： 原子操作，尝试将头节点从oldHead（以及head_）换到node。它会比较head和oldHead的值，如果相同
             * 则将head值变为node的值。这里遵循两个原则：1. memory_order_release。表示更新操作成功后。所以之前的写操作
             * 都将可见，包括node-》next。2. memory_order_relaxed，如果操作失败，不对其他任何内存操作进行同步约束或排序。只会
             * 重新加载当前head值
             */
            if (head_.compare_exchange_weak(oldHead, node, memory_order_release, memory_order_relaxed)) {
                break;
            }
        }
    }

    bool pop(int& data) {
        // 将head设为nullptr，oldHead获得head的值
        // memory_order_acquire 保证在读head的值之前，所有的写操作已经完成了。
        Node* oldHead = head_.exchange(nullptr, memory_order_acquire); 
        /** 这里就是将oldHead去掉，拿到它的数据，并将head改为oldHead的下一个node */
        if(oldHead != nullptr) {
            // atomic_load 是atomic类成员的函数，所以一定要用atomic<T>,来定义head和next
            Node* newHead = oldHead->next.load(memory_order_acquire); // 本来就是个指针，为什么还要取引用？
            data = oldHead->data;
            delete oldHead; // 释放内存后，可能该指针依然指向该内存，但没有用（悬空指针）。可以让它等于nullptr。或者不用它（危险，可能仍然修改）
            head_.store(newHead, memory_order_release);
            return true;
        }
        return false;
    }
};

int main() {
    AtomicStack stack;
    // 这里模拟thread。一边读一边写。
    /**
     * LockFreeStack stack;
     * 
     * void producer(LockFreeStack& stack, int id) {
    for (int i = 0; i < 10; ++i) {
        stack.push(id * 10 + i); // push的时候不能读
    }
}

void consumer(LockFreeStack& stack, int id) {
    int value;
    for (int i = 0; i < 10; ++i) {
        while (!stack.pop(value)) {  // pop的时候，读取oldHead要等所有写完。改新head时不能读。
            // 等待直到成功弹出
        }
        std::cout << "Consumer " << id << " popped: " << value << std::endl;
    }
}

    std::thread t1(producer, std::ref(stack), 1);
    std::thread t2(producer, std::ref(stack), 2);
    std::thread t3(consumer, std::ref(stack), 1);
    std::thread t4(consumer, std::ref(stack), 2);

    t1.join();
    t2.join();
    t3.join();
    t4.join();
     */
    stack.push(42);
    int value;
    if (stack.pop(value)) {
        cout << "Popped value: " << value << endl;
    }
    return 0;
}
/**
 * load跟acquire一起用，用从共享内存中读数据（这些数据可能被其他线程修改）
 * store和release一起用，用于从外部读取读取数据存储到共享内存中中。
 * 
 * acquire是针对读共享数据，所以要保证写队列清空，保证所有写任务已经完成（atomic管理）。相当于一个read队列的锁
 * release是针对写共享数据，所以要先锁住读任务队列，保证该写任务已经完成后，才能进行读。
 * 
 * atomic会管理这些读写队列，比如有一个任务在run的时候其他任务在排队是有一个顺序的，然后根据顺序一个个让读或写的任务进来
 * 不会造成资源竞争。另外也可以时刻检查读或者写队列的情况，比如是否为空。
 */