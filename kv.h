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

#define X(type, name, parse, format, init) \
	type name;
typedef struct {
	KV
} kv;
#undef X

kv
kv_init() {
	kv c;
#define X(type, name, parse, format, init) \
	c.name = init;
	KV
#undef X
	return c;
}

void
kv_print(FILE *f, kv c) {
#define X(type, name, parse, format, init) \
	fprintf(f, "%s = "format"\n", #name, c.name);
	KV
#undef X
}

void
kv_read(FILE *f, kv *c) {
	char k[MAXLEN], v[MAXLEN];
#define X(type, name, parse, format, init) \
	if(strncmp(k, #name, MAX(strlen(k), strlen(#name))) == 0) \
		c->name = parse(v);
	while(fscanf(f, "%s = %s\n", k, v) == 2) {
		KV
	}
#undef X
}
