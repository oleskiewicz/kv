CC     = cc
CFLAGS = -std=c99 -Wall -O2 -march=native

example: example.c kv.h

%: %.c
	$(CC) $(CFLAGS) -o $@ $< $(LDFLAGS)
