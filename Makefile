all:
	$(CC) -ansi -pedantic-errors -Wall -g  -lcrypto -lssl main2.c -o areyouworkingson
