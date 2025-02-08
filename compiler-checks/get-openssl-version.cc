#include <openssl/opensslv.h>
#include <iostream>

int main() {
    std::cout << OPENSSL_VERSION_TEXT << "\n";
    return 0;
}
