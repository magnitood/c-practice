#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STR_MIN_CAP 32

typedef struct {
	char *cstring;
	size_t len;
	size_t capacity;
} string;
// length is excluding null terminator (to maintain strlen() compaatibitly)

string *create_string()
{
	string *str = malloc(sizeof(*str));
	size_t capacity = STR_MIN_CAP;
	str->cstring = malloc(sizeof(char) * capacity);
	str->cstring[0] = '\0';
	str->len = 0;
	str->capacity = capacity;
	return str;
}

string *append(string *s, const char *cstring, size_t len)
{
	if (cstring == NULL || s == NULL)
		return s;

	if (len == 0)
		len = strlen(cstring);

	size_t prev_capacity = s->capacity;
	while (s->len + len + 1 > s->capacity) {
		s->capacity *= 2;
	}

	if (prev_capacity != s->capacity)
		s->cstring = realloc(s->cstring, sizeof(char) * s->capacity);

	char *ptr = s->cstring;
	while (*ptr != '\0')
		ptr++;

	for (size_t i = 0; i < len && *cstring != '\0'; i++) {
		*ptr = *cstring;
		ptr++;
		cstring++;
	}
	*ptr = '\0';

	return s;
}

void destroy_string(string *s)
{
	if (s == NULL)
		return;

	free(s->cstring);
	free(s);
}

void clear_string(string *s)
{
	if (s == NULL)
		return;

	s->cstring[0] = '\0';
	s->len = 0;
}

void evaluate(string *s)
{
	if (s == NULL)
		return;

	printf("%s\n", s->cstring);
}

int main()
{
	printf("Welcome to this custom REPL\n");
	printf("Enter something and it will be repeated\n\n");

	bool running = true;
	string *line = create_string();
	while(running) {
		printf(">> ");
		char c;
		while ((c = getchar()) != '\n') {
			if (c == EOF) {
				running = false;
				goto label;
			}
			append(line, &c, 1);
		}

label:
		evaluate(line);
		clear_string(line);
	}
	destroy_string(line);
	return 0;
}
