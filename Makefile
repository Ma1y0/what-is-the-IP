CC := clang

whatIsTheIP: whatIsTheIP.c
	$(CC) whatIsTheIP.c -o whatIsTheIP -Wall -Wextra -pedantic
