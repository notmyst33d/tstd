#include <tstd.h>

void print(char* buf) {
    sys_write(1, buf, strlen(buf));
}
