#include <stdio.h>

#define KV \
	X(char *, out, ".") \
	X(double, Om, 0.0) \
	X(double, Ol, 0.0) \
	X(int, nout, 1) \
	X(bool, flat, true)

#include "kv.h"

int
main(int argc, char *argv[]) {
	kv c = kv_init();

	if(argc > 1) {
		FILE *f = fopen(argv[1], "r");
		kv_read(f, &c);
		fclose(f);
	} else {
		kv_read(stdin, &c);
	}

	kv_print(stdout, c);

	return 0;
}
