#include <gssapi/gssapi.h>

bool foo() { return (gss_str_to_oid(0, 0, 0)); }

int main() {
    return 0;
}
