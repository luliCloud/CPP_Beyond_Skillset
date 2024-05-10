#include <iostream>
#include <memory>
using namespace std;
/**
 * std::unique_ptr
*/
struct Resource {
    Resource() { cout << "Resource acquired.\n"; }
    ~Resource() { cout << "Resource releadsed.\n"; }    
};

struct SharedResource {
    SharedResource() { cout << "Shared Resource acquired.\n"; }
    ~SharedResource() { cout << "Shared Resource releadsed.\n"; }    
};

/**
 * unique_ptr 是一种智能指针，提供了对单一对象的独占所有权。即，在任何时间点，
 * 只有一个unique_ptr实例可以拥有对象的所有权。当这个指针被销毁时，所管理的对象
 * 也会自动销毁 （通过调用对象的destructor释放内存。者提供了一种非常安全的方式
 * 来确保资源（如动态分配的内存）在不在需要时被自动释放。
 * 
 * make_unique：C++14中引入的辅助函数，用于创建一个unique_ptr。这个函数在创建
 * 对象和封装他到unique-ptr中时提供了一种安全简洁的方法。使用make-uniuqe比new来
 * 操作uqniue-ptr好处包括：1. 可以避免在使用new时抛出异常而导致的内存泄漏。make-unique
 * 在分配内存和构造对象时提供原子操作，如果构造对象时发生异常，分配的内存被安全释放。
 * 2.代码简洁。
*/
void processResource() {
    /**
     * 这行代码执行以下操作：1.调用Resource的默认构造函数来创建一个新的Resource对象
     * 2. 将这个新对象封装到一个unique_ptr<Resource>中
     * 3. 将这个新创建的unique_ptr<Resource>实例赋值给ptr
     * 注意，这个ptr仍然指向Resource的实例。但是它在离开作用域时会自动销毁自己和它管理的对象
     * 当 std::unique_ptr 类型的 ptr 离开其作用域时，它会自动销毁，
     * 并且在其析构过程中自动删除它所管理的对象。
     * 这是 std::unique_ptr 的一个重要特性，它使得内存管理变得更加安全和简单。
    */
    unique_ptr<Resource> ptr = make_unique<Resource>();
}

/**
 * SharedResource 的实例被两个 std::shared_ptr 所共享。注意引用计数的变化，
 * 它显示了资源是如何被多个所有者共享的。
*/
void processSharedResource() {
    shared_ptr<SharedResource> ptr1 = make_shared<SharedResource>();
    /**
     * use_count() is provided by shared_ptr. It returns the number of 
     * shared_ptr objects that manage the same resources. 
    */
    cout << "First pointer created, ref count = " 
         << ptr1.use_count() << endl;
    {
        shared_ptr<SharedResource> ptr2 = ptr1; // take resource from ptr1
        cout << "Second pointer created, ref count = " << ptr2.use_count() << endl;
    }
    // ptr2 leave the code segment it belongs, auto destroyed
    cout << "Second pointer out of scope, ref count = " << ptr1.use_count() << endl;
}

/**
 * weak_ptr 也是智能指针，被设计为对shared-ptr所管理的对象进行非拥有（弱）引用。
 * 它不会增加对象的引用计数（注意我们通过shared——ptr而不是weak-ptr获得）。
 * weak和shared不会共享所有权资源，只是提供一种共享方式。
 * weak的主要作用
 * 1. 帮助解决share-ptr可能导致的循环引用问题。如果两个或更多的share-ptr相互引用，
 * 可能会创建一个循环，导致管理对象永远不被销毁。weak-ptr允许对这些对象观察，但不拥有
 * 2. weak不承担维持对象生存的责任，如果所有shared-ptr都被销毁，那么即使还是weak存在，
 * 对象也会被销毁。
 * 但它在离开block时也会自动销毁
*/
void processWeakPtr() {
    weak_ptr<SharedResource> wptr;
    {
        shared_ptr<SharedResource> ptr = make_shared<SharedResource>();
        wptr = ptr;
        cout << "Inside block: sharedPtr count = " << ptr.use_count() << endl;

    }
    cout << "Outside block: weak ptr expired? " << wptr.expired() << endl;
}

int main() {
    processResource();  // 自动创建智能指针,unique_ptr, when leave this function
    // it is already destryoed. As its scope is precessResource func, not main
    cout << endl;
    processSharedResource();

    cout << endl;
    processWeakPtr();

    cout << "when leaving this main function, \ 
all resource no longer in use.\n";
    return 0;
}
/**
Resource acquired.
Resource releadsed.

Shared Resource acquired.
First pointer created, ref count = 1
Second pointer created, ref count = 2
Second pointer out of scope, ref count = 1
Shared Resource releadsed.

Shared Resource acquired.
Inside block: sharedPtr count = 1
Shared Resource releadsed.
Outside block: weak ptr expired? 1
when leaving this main function, all resource no longer in use.
*/