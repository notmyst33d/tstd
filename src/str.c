int strlen(char *buf) {
	unsigned int i = 0;

	while (buf[i] != 0)
		i++;

	return i;
}
