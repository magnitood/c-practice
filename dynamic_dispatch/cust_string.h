#ifndef CUSTOM_STRING_H
#define CUSTOM_STRING_H

#include <stdlib.h>
#include <stddef.h>
#include <string.h>


typedef struct {
	char *str;
	size_t length; // not including \0
} string;

static string *new_string(char *c_string) // takes any generic c string
{
	string *newthing = (string *) malloc(sizeof(*newthing));
	if (newthing == NULL)
		return NULL;

	size_t length = strlen(c_string);
	char *str = (char *) malloc(sizeof(*str) * (length+1));
	if (str == NULL) {
		free(newthing);
		return NULL;
	}
	
	newthing->str = strcpy(str, c_string);
	newthing->length = length;

	return newthing;
}

static void free_string(string *s)
{
	if (s == NULL)
		return;
	else if (s->str == NULL) {
		free(s);
	} else {
		free(s->str);
		free(s);
	}
}

#endif // CUSTOM_STRING_H
