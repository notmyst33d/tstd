#include <tstd.h>

int main(int argc, char **argv) {
    int n1, n2;
    char buf[32];

    if (argc < 4) {
        print("Usage: calc [number 1] [operation] [number 2]\n");
        return -1;
    }

    n1 = strint(argv[1]);
    n2 = strint(argv[3]);

    switch (argv[2][0]) {
        case '+':
            intstr(n1 + n2, buf);
            print(buf);
            print("\n");
            break;
    }

    return 0;
}
