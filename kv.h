#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXLEN 256
#define MAX(a, b) ((a) > (b) ? (a) : (b))

bool
atob(const char *str) {
	if((str[0] == 'T') || (str[0] == 't')) {
		return true;
	} else if((str[0] == 'F') || (str[0] == 'f')) {
		return false;
	} else {
		fprintf(stderr, "boolean must be true or false, got \"%s\"\n", str);
		exit(1);
	}
}

char
atoc(char *str) {
	return strlen(str) > 0 ? str[0] : '\0';
}

#define X(type, name, init) \
	type name;
struct kv {
	KV
};
#undef X

struct kv
kv_init() {
	struct kv c;
#define X(type, name, init) \
	c.name = init;
	KV
#undef X
	return c;
}

void
kv_print(FILE *f, struct kv c) {
#define X(type, name, init) \
	fprintf(f, _Generic((type){0}, \
		char *: "%s = %s\n", \
		double: "%s = %f\n", \
		int: "%s = %d\n", \
		bool: "%s = %d\n" \
		), #name, c.name);
	KV
#undef X
}

void
kv_read(FILE *f, struct kv *c) {
	char k[MAXLEN], v[MAXLEN];
#define X(type, name, init) \
	if(strncmp(k, #name, MAX(strlen(k), strlen(#name))) == 0) \
		c->name = _Generic((type){0}, \
			char *: strdup, \
			double: atof, \
			int: atoi, \
			bool: atob \
			)(v);
	while(fscanf(f, "%s = %s\n", k, v) == 2) {
		KV
	}
#undef X
}
