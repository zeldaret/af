#include "xstdio.h"
#include "string.h"
#include "os.h"

// TODO: this comes from a header
#ident "$Revision: 1.23 $"

static void* proutSprintf(void* s, const char* buf, size_t n);

int sprintf(char* s, const char* fmt, ...) {
    int ans;
    va_list ap;
    va_start(ap, fmt);
    ans = _Printf(proutSprintf, s, fmt, ap);
    if (ans >= 0) {
        s[ans] = 0;
    }
    return ans;
}
static void* proutSprintf(void* s, const char* buf, size_t n) {
    return (char*)memcpy(s, buf, n) + n;
}
