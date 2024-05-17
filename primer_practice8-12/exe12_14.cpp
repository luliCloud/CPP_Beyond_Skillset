/**
 * create your own shared_ptr to manage the connection
*/
#include <iostream>
#include <string>
#include <memory>
using namespace std;

class Connection { // 连接地
public:
    string ip;
    int port;
    Connection(string i, int p) : ip(i), port(p) {}
};

class Destination {  // 目的地
public:
    string ip;
    int port;
    Destination(string i, int p) : ip(i), port(p) {}
};

void disconnect(Connection pConn) {
    cout << "connection close(" << pConn.ip << ":" << pConn.port << ")" << endl;
}

void end_connection(Connection* pConn) {
    // 在实际引用中，这里可能需要添加关闭连接等清理操作
    disconnect(*pConn);
    delete pConn;
}

// 创建一个Connection对象，接受Destination的ip和port号。并使用shared ptr 来管理它
shared_ptr<Connection> connect(Destination* pDest) {
    /** assign the string and port of des as a new memory space as an connection obj */
    /**
     * 使用shared_ptr来管理conn对象，并指定自定义删除函数 end_connection
    */
    shared_ptr<Connection> pConn(new Connection(pDest->ip, pDest->port), end_connection);

    /**
     * 如果我们写成shared_ptr<Connection> pConn = make_shared(pDest->ip, pDest->port); 
     * make_shared 或者 shared_ptr()都可以用来构建智能指针
     * 但不管是那种，如果我们没有传入自定义删除器，那么系统就会自动为我们创造默认删除器并管理智能指针
     * 指向的空间。但是这里如果我们传入了自定义删除器，那么就需要在自定义删除器中delete智能指针管理的空间
     * 当所有智能指针都离开作用域，use-count为0时，shared-ptr就会自动call自定义删除器来释放管理的空间
    */
    cout << "creating connection(" << pConn.use_count() << ")" << endl;
    return pConn;  // 返回管理对象的ptr，而不是对象本身
}

void f(Destination& d) {
    /**
     * 在复制时，connect return的这个智能指针负责把自己的值全部传递给pConn，然后它就会销毁。
     * 也有可能有一个缓存，存了return的信息，而connect内的pConn在离开scope那一刻已经销毁了
     * 但不管怎样，可以完成pConn在这里的初始化。但是connect中return的内容一定会在这一句销毁
     * 我们在cout打出来的时候就只有一个指针在指向这片内存了
    */
    shared_ptr<Connection> pConn = connect(&d);
    cout << "connecting now(" << pConn.use_count() << ")" << endl;

    /* 而这里我们pConn仍然存在，另一个pConn就复制了它的内容，所以会有两个ptr指向一个内存。
    */
    shared_ptr<Connection> anotherPConn = pConn;
    cout << "connecting now(" << pConn.use_count() << ")" << endl;
}

int main() {
    Destination dest("220,181.111.111", 10086);
    f(dest);

    return 0;
}

