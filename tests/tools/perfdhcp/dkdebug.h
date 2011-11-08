#ifdef __cplusplus
extern "C" {
#endif

#include <stdarg.h>

#define DK_ALL (~0)

struct dkdesc {
    char keyletter;
    unsigned mask;
};

void dkprintf(unsigned diag_req, const char format[], ...);
void vdkprintf(unsigned diag_req, const char format[], va_list ap);
int dk_setup(const char* diag_str, const struct dkdesc* diags);
int dk_set(unsigned diag_req);

#ifdef __cplusplus
}
#endif
