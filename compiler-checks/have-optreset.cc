#include <unistd.h>

int main() {
    extern int optreset;
    optreset=1;
    return 0;
}
