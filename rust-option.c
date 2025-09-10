#include <stdio.h>

typedef enum {NONE, SOME} OptionType;

#define Some(x) ((Option) { .type = SOME, .some = x, })
#define None ((Option) { .type = NONE })

typedef struct {
    OptionType type;
    union {
        float some;
    };
} Option;

Option some_func(int a)
{
    if (a < 0)
        return None;
    else
        return Some(a);
}

int main()
{
    float a;
    scanf("%f", &a);
    Option res = Some(a);

    res = some_func(a);

    switch (res.type) {
        case NONE:
            printf("Some error done occured cro\n");
            break;
        case SOME:
            printf("%f\n", res.some);
            break;
    }

    return 0;
}

