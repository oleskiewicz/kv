#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>

#define MAXLEN 256
#define MAX(a, b) ((a) > (b) ? (a) : (b))

char *
strtrim(char *str) {
	char *end;

	while(isspace((int)*str))
		str++;

	if(*str == 0)
		return str;

	end = str + strlen(str) - 1;
	while(end > str && isspace((int)*end))
		end--;

	end[1] = '\0';

	return str;
}

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

int *
atoai(char *str) {
	size_t i = 0;
	int *a = NULL;
	char *e = strtok(str, ",");
	while(e != NULL) {
		a = (int *)realloc(a, sizeof *a);
		a[i] = atoi(e);
		i += 1;
		e = strtok(NULL, ",");
	}
	return a;
}

double *
atoaf(char *str) {
	int i = 0;
	double *a = NULL;
	char *e = strtok(str, ",");
	while(e != NULL) {
		a = (double *)realloc(a, sizeof *a);
		a[i] = atof(e);
		i += 1;
		e = strtok(NULL, ",");
	}
	return a;
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
kv_print(FILE * f, struct kv c) {
#define X(type, name, init) \
	fprintf(\
		f, \
		_Generic((type){0}, \
			bool: "%s = %d\n", \
			int: "%s = %d\n", \
			int *: "%s = %s\n", \
			double: "%s = %g\n", \
			double *: "%s = %s\n", \
			char: "%s = %c\n", \
			char *: "%s = %s\n" \
		), \
		#name, \
		_Generic((type){0}, \
			int *:  "array of ints", \
			double *: "array of floats", \
			default: c.name \
		) \
	);
	KV
#undef X
}

void
kv_read(FILE * f, struct kv *c) {
	char *_k = (char *)malloc(MAXLEN * sizeof(char));
	char *_v = (char *)malloc(MAXLEN * sizeof(char));

#define X(type, name, init) \
	if (!strncmp(k, #name, MAX(strlen(k), strlen(#name)))) \
		c->name = _Generic((type){0}, \
			bool: atob, \
			int: atoi, \
			int *: atoai, \
			double: atof, \
			double *: atoaf, \
			char: atoc, \
			char *: strdup \
		)(v);
	while(fscanf(f, "%[^=]=%[^=\n]", _k, _v) == 2) {
		char *k = strtrim(_k), *v = strtrim(_v);
		KV
	}
#undef X
}
