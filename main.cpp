#include "src/test.hpp"

#include <cstring>
#include "src/Socket/Util.hpp"
#include "src/Global.hpp"

int main() {
    SocketServerGlobal::gl_pNumber = new Number(1000);
    SocketServerGlobal::threadPool = new ThreadPool(6);

    if (!Socket_Util::initalizeSocket()) {
        return -1;
    }

    WSACleanup();
    return 0;
}
