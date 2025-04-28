#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct string string;
struct string {
	char *cstring;
	size_t len; // length is excluding null terminator (to maintain strlen() compaatibitly)
	size_t capacity;
};

string *str_create();
string *str_append_string(string *s, const char *cstring, size_t len);
string *str_append_char(string *s, char c);
string *str_clear(string *s);
void str_destroy(string *s);
void evaluate(string *s);

int main()
{
	string *s = str_create();
	str_append_string(s, "Hello ", 0);
	str_append_string(s, "World!", 0);

	printf("%s\n", s->cstring);


	printf("Welcome to this custom REPL\n");

	bool running = true;
	string *line = str_create();
	while (running) {
		printf(">> ");
		char c;
		while ((c = getchar()) != '\n') {
			if (c == EOF) {
				running = false;
				goto label;
			}
			str_append_char(line, c);
		}
		str_append_char(line, '\n');

label:
		evaluate(line);
		str_clear(line);
	}
	str_destroy(line);

	putchar('\n');
	return EXIT_SUCCESS;
}

void evaluate(string *s)
{
	if (s == NULL || s->len == 0)
		return;

	char *argv[] = {"/usr/bin/nvim", "repl.c", 0};

	pid_t child_pid = fork();
	if (child_pid == -1) { // fork failed
		// handle error
	} else if (child_pid == 0) { // child process
		int ret = execv(argv[0], argv);
		if (ret == -1) {
			perror("child process creation failed\n");
		}
	} else { // parent process
		int status;
		do {
			waitpid(child_pid, &status, 0);
			if (WIFEXITED(status)) {
				printf("Child process exited with status %d\n", WEXITSTATUS(status));
			}
		} while (!WIFEXITED(status));
	}
}




// ---- Sring Functions ---- //

#define STR_MIN_CAP 32

string *str_create()
{
	string *str = malloc(sizeof(*str));
	if (str == NULL)
		return NULL;

	size_t capacity = STR_MIN_CAP;
	str->cstring = malloc(sizeof(char) * capacity);
	if (str->cstring == NULL) {
		free(str);
		return NULL;
	}

	str->cstring[0] = '\0';
	str->len = 0;
	str->capacity = capacity;
	return str;
}

string *str_append_string(string *s, const char *cstring, size_t len)
{
	if (cstring == NULL || s == NULL)
		return s;

	if (len == 0)
		len = strlen(cstring);

	size_t prev_capacity = s->capacity;
	while (s->len + len + 1 > s->capacity) {
		s->capacity *= 5; // exponential backoff
	}

	if (prev_capacity != s->capacity)
		s->cstring = realloc(s->cstring, sizeof(char) * s->capacity);

	// TODO: change this as we do not need to seek to the specified len as we have len already
	// char *ptr = s->cstring;
	// while (*ptr != '\0')
	// 	ptr++;

	char *ptr = &(s->cstring[s->len]);

	// TODO: try to implement this using memcpy or something similar
	// for (size_t i = 0; i < len && *cstring != '\0'; i++) {
	// 	*ptr = *cstring;
	// 	ptr++;
	// 	cstring++;
	// }

	strcpy(ptr, cstring);
	// *ptr = '\0';
	s->len += len;

	return s;
}


// TODO
string *str_append_char(string *s, char c)
{
	if (s == NULL)
		return s;

	if (s->len + 2 > s->capacity) {
		s->capacity *= 2;
		s->cstring = realloc(s->cstring, sizeof(char) * s->capacity);
	}
	s->cstring[s->len++] = c;
	s->cstring[s->len] = '\0';

	return s;
}

void str_destroy(string *s)
{
	if (s == NULL)
		return;

	free(s->cstring);
	free(s);
}

string *str_clear(string *s)
{
	if (s == NULL)
		return s;

	s->cstring[0] = '\0';
	s->len = 0;

	return s;
}

