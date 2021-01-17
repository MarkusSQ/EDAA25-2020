#define  _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdbool.h>

int main() {
	char *longest = NULL;
    char *line = NULL;
    size_t len = 0;

	while(getline(&line, &len, stdin) != EOF) {
		printf("%s\n", );
	}
}