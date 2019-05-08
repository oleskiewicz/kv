#include <stdio.h>

#define KV \
	X(char *, out, "%s", atos, "./") \
	X(double, Om, "%.3f", atof, 0.0) \
	X(double, Ol, "%.3f", atof, 0.0) \
	X(int, nout, "%d", atoi, 1) \
	X(bool, flat, "%d", atob, true) \

#include "kv.h"

int
main(int argc, char *argv[]) {
	kv c = kv_init();

	if(argc > 1) {
		FILE *f = fopen(argv[1], "r");
		kv_read(f, &c);
		fclose(f);
	}
	else {
		kv_read(stdin, &c);
	}

	kv_print(c);
	return 0;
}
