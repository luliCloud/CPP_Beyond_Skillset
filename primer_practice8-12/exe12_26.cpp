/**using allocator
 * 虽然大多数时候标准容器（如 std::vector, std::list）的默认内存管理已经足够高效和安全，
 * 但在某些特定场景下，你可能需要更精细的内存控制或优化。这时，自定义分配器可以提供以下好处：
性能优化：针对特定类型或特定大小的内存请求优化分配策略。
降低内存碎片：通过定制的分配策略减少内存碎片。
跟踪和分析：在分配和释放时插入额外的逻辑，用于调试或监测内存使用。
*/
#include <iostream>
#include <string>
#include <memory>
using namespace std;

int main() {
    int n = 5;
    /**
     * allocator<std::string> alloc; 时，你创建了一个能够为 std::string 
     * 类型对象分配内存的分配器对象。这种类型的
     * 分配器通常用在需要手动控制内存分配和对象生命周期的场合，
     * 比如在实现自定义容器或处理内存管理的高级场景中。
    */
    allocator<string> alloc;
    // string* p = alloc.allocate(1); // allocate space to store one string obj
    // alloc.construct(p, "Hello"); // construct a string obj in the allcated space
    // alloc.destroy(p); // destroy obj pointed by p
    // alloc.deallocate(p, 1); // release memory
    string* p = alloc.allocate(n);
    string s;
    auto q = p;
    while (cin >> s && q != p + n) {
        // new way to construct obj in C++17 beyond
        new (q) string(s);
        q++;
    }
    while (q != p) {
        cout << *--q << endl;  // q reach p + n first, so we need to have --q
        // destroy
        q->~string();
    }
    alloc.deallocate(p, n);
    return 0;
}
/*
yes
i
do
may
day
ok // this the 6, ignore by compiler
day
may
do
i
yes
*/