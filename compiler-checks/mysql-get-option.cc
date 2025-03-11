#include <mysql.h>
int foo(MYSQL handle, unsigned int timeout) {
    return (mysql_get_option(&handle, MYSQL_OPT_CONNECT_TIMEOUT, &timeout));
}

int main() {
    return 0;
}
