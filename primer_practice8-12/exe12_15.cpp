/** use shared_ptr to manage connection, using lambda */
#include <iostream>
#include <memory>
#include <string>
using namespace std;

struct connection {
    string ip;
    int port;
    connection(string i, int pi) : ip(i), port(pi){}
};
/** 网络连接的目的地 */
struct destination {
    string ip;
    int port;
    destination(string i, int pi) : ip(i), port(pi) {}
};
/** creating connection. we modified it to return shared ptr instead of obj 
 * connection 对象只是使用了 destination 提供的 ip 和 port 信息来进行初始化，
 * 但代码本身并没有显示实际建立网络连接的逻辑。这意味着在这个特定示例中，
 * 尽管 connection 对象已经准备好了所需的连接信息，它还没有与任何客户端或服务器建立实际的网络连接。
*/
connection connect(destination* pDest) {
    shared_ptr<connection> pConn(new connection(pDest->ip, pDest->port));
    cout << "creating conenction(" << pConn.use_count() << ")" << endl;
    // return pConn;
    return *pConn;  // 返回的connection对象与pConn指向的对象是独立的，不会共享shared_ptr
}

void disconnet(connection pConn) {
    cout << "connection close(" << pConn.ip << ":" << pConn.port << ")" << endl;
}
/*establish the whole connection and destory the connection when leave this f()*/
void f(destination &d) {
    connection conn = connect(&d);  // copy a connection obj, not obtain shared ptr
    // create a shaerd ptr here using &conn, aand lambda. but actually we can 
    // return shared ptr from connect and use a shared_ptr to take this memory directly (use : 1)
    // then a second shared ptr can also point to this memory and use increase to 2
    shared_ptr<connection> pConn(&conn, [](connection* pConn){
        disconnet(*pConn);
    });
    cout << "connecting now(" << pConn.use_count() << ")" << endl;
}

int main() {
    destination dest("220.181.111.111", 10086);
    f(dest);
    return 0;
}
/**
 * output:
creating conenction(1)
connecting now(1)
connection close(220.181.111.111:10086)
*/