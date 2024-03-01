// File descriptors
#define STDIN 0
#define STDOUT 1
#define STDERR 2

// sys.S
int sys_read(unsigned int fd, char *buf, unsigned int count);
int sys_write(unsigned int fd, const char *buf, unsigned int count);
int sys_open(const char *filename, int flags, unsigned short mode);
int sys_close(unsigned int fd);
void sys_exit(int error_code);

// crt.c
int main(int argc, char **argv);

// str.c
int strlen(char *buf);
void strrev(char *buf);

// conv.c
void intstr(int num, char *buf);
int strint(char *buf);

// io.c
static inline int read(char *buf, unsigned int count) {
    return sys_read(STDIN, buf, count);
}

static inline int print(char *buf) {
    return sys_write(STDOUT, buf, strlen(buf));
}

int randint();

static inline unsigned int randuint() {
    return randint();
}
