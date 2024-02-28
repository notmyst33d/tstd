#include <tstd.h>

const char *digits = "0123456789";

// Int to string conversion
void intstr(int i, char *buf) {
    int count = 0;
    int start = 0;
    int base = 10;
    int base2 = 1;

    if (i == 0) {
        buf[0] = '0';
        buf[1] = 0;
        return;
    } else if (i < 0) {
        base = -10;
        base2 = -1;
        start = 1;
        buf[0] = '-';
    }

    while (i % base != i) {
        count += 1;
        base *= 10;
        base2 *= 10;
    }

    for (int i2 = start; i2 <= count + start; i2++) {
    	buf[i2] = digits[(i % base) / base2];
        base /= 10;
        base2 /= 10;
    }

    buf[count + start + 1] = 0;
}

// String to int conversion
int strint(char *buf) {
    int length = strlen(buf);
    int result = 0;
    int base = 1;
    int end = 0;

    // Check for negative numbers
    if (length >= 1) {
        if (buf[0] == '-') {
            base = -1;
            end = 1;
        }
    }

    // Start from end to start, multiplying base by 10 with each number
    for (int i = length - 1; i >= end; i--) {
        result += (buf[i] - 48) * base;
        base *= 10;
    }

    return result;
}
