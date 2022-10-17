linux:
	$(CC) -ansi -pedantic-errors -Wall -g -lcrypto -lssl main2.c -o areyouworkingson

macos:
	$(CC) -std=c99 -pedantic-errors -Wall -g -I/opt/homebrew/opt/openssl/include -L/opt/homebrew/opt/openssl/lib -lcrypto -lssl main2.c -o areyouworkingson
