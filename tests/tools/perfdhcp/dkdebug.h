#ifdef __cplusplus
extern "C" {
#endif 

#include <stdarg.h>

extern unsigned dk_diag_mask;

#define dk_set(diag_req) ((diag_req) & dk_diag_mask)
#define DK_ALL (~0)

struct dkdesc {
    char keyletter;
    unsigned mask;
};

void dkprintf(unsigned diag_req, const char format[], ...);
void vdkprintf(unsigned diag_req, const char format[], va_list ap);
int dk_setup(const char *diag_str, const struct dkdesc *diags);

#ifdef __cplusplus
}
#endif
