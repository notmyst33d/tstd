int strlen(char *buf) {
	unsigned int i = 0;

	while (buf[i] != 0)
		i++;

	return i;
}

void strrev(char *buf) {
    int i, j;
    char c;

    for (i = 0, j = strlen(buf) - 1; i < j; i++, j--) {
        c = buf[i];
        buf[i] = buf[j];
        buf[j] = c;
    }
}
