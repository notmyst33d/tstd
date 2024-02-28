// sys.S
int sys_write(unsigned int fd, const char *buf, unsigned int count);
void sys_exit(int error_code);

// crt.c
int main(int argc, char **argv);

// str.c
int strlen(char *buf);

// conv.c
void intstr(int i, char *buf);
int strint(char *buf);

// io.c
void print(char *buf);
