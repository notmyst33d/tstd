#include <tstd.h>

int randint() {
    int i, fd = sys_open("/dev/random", 0, 0);
    sys_read(fd, (char*)&i, 4);
    sys_close(fd);
    return i;
}
