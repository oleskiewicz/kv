#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAXLEN 256

bool
atob(const char *str) {
	if(strcmp(str, "true") == 0) {
		return true;
	} else if(strcmp(str, "True") == 0) {
		return true;
	} else if(strcmp(str, ".true.") == 0) {
		return true;
	} else if(strcmp(str, "T") == 0) {
		return true;
	} else if(strcmp(str, "t") == 0) {
		return true;
	} else if(strcmp(str, "false") == 0) {
		return false;
	} else if(strcmp(str, "False") == 0) {
		return false;
	} else if(strcmp(str, ".false.") == 0) {
		return false;
	} else if(strcmp(str, "F") == 0) {
		return false;
	} else if(strcmp(str, "f") == 0) {
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

char *
atos(char *str) {
	char *res = (char *)malloc(sizeof(char) * strlen(str) + 1);
	strncpy(res, str, strlen(str) + 1);
	return res;
}

typedef struct {
#define X(type, name, format, parse, init) type name;
	KV
#undef X
} kv;

kv
kv_init() {
	kv c;
#define X(type, name, format, parse, init) \
	c.name = init;
	KV
#undef X
	return c;
}

void
kv_print(kv c) {
#define X(type, name, format, parse, init) \
	printf("%s = "format"\n", #name, c.name);
	KV
#undef X
}

void
kv_read(FILE *f, kv *c) {
	char k[MAXLEN], v[MAXLEN];

#define X(type, name, format, parse, init) \
	if(strcmp(k, #name) == 0) \
		c->name = parse(v);
	while(fscanf(f, "%s = %s\n", k, v) == 2) {
		KV
	}
#undef X
}
