#include "src/test.hpp"

#include <cstring>
#include "src/Socket/Util.hpp"

int main() {

    if (!Socket_Util::initalizeSocket()) {
        return -1;
    }

    WSACleanup();
    return 0;
}
