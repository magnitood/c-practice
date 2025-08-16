#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#define arr_size(arr) (sizeof(arr)/sizeof(arr[0]))

bool does_match(char *restrict input, char *restrict array_string)
{
	if (strlen(input) < strlen(array_string))
		return false;

	char *input_ptr = input;
	char *array_string_ptr = array_string;

	while (*array_string_ptr != '\0' && *input_ptr != '\0') {
		if (*array_string_ptr == *input_ptr)
			array_string_ptr++;

		input_ptr++;
	}

	return *array_string_ptr == '\0' ? true : false;
}

int main()
{
	char *test1[] = {"abcde", "a", "bb", "acd", "ace"};
	char *test2[] = {"dsahjpjauf", "ahjpjau", "ja", "ahbwzgqnuk", "tnmlanowax"};

	// uint64_t match_count = 0;
	printf("%s %s: %d\n",test2[0], test2[1], does_match(test2[0], test2[1]));
	printf("%s %s: %d\n",test2[0], test2[2], does_match(test2[0], test2[2]));
	printf("%s %s: %d\n",test2[0], test2[3], does_match(test2[0], test2[3]));
	printf("%s %s: %d\n",test2[0], test2[4], does_match(test2[0], test2[4]));

	return 0;
}
