#include <stdio.h>

#define KV \
	X(char *, out, strdup, "%s", ".") \
	X(double, Om, atof, "%f", 0.0) \
	X(double, Ol, atof, "%f", 0.0) \
	X(int, nout, atoi, "%d", 1) \
	X(bool, flat, atob, "%d", true)

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
