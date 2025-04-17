#include <stdio.h>
#include <stdint.h>

void ser_cstring(const char *cstring) { printf("cstring: \"%s\"\n", cstring); }

#define ser_number(x) _Generic((x), \
	signed short: printf("signed short: %hd\n", x), \
	unsigned short: printf("unsigned short: %hu\n", x), \
	signed int: printf("signed int: %d\n", x), \
	unsigned int: printf("unsigned int: %u\n", x), \
	signed long: printf("signed long: %ld\n", x), \
	unsigned long: printf("unsigned long: %lu\n", x), \
	signed long long: printf("signed long long: %lld\n", x), \
	unsigned long long: printf("unsigned long long: %llu\n", x), \
	default: printf("default caught\n"))

struct animal {
	const char *name; // used as cstring
	uint64_t age;
};

void ser_animal(struct animal *a) {
	ser_cstring(a->name);
	ser_number(a->age);
}

int main()
{
	int num = 5;
	long long hello = 2341;
	long long int hi = 1234;

	struct animal a;
	a.name = "Bohr";
	a.age = 5;
	ser_animal(&a);
	return 0;
}
