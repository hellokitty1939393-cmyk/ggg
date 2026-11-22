/* Compiles, but gcc -Wall -Wextra reports four warnings (see warn_fixed.c for the cure). */
#include <stdio.h>

long compute(int units, int unused_param)
{
    int never_used;
    long paise = 5000L;
    unsigned int limit = 100;
    if (units > limit)
        paise += (units - 100) * 225L;
    printf("%d\n", paise);
    return paise;
}

int main(void)
{
    compute(150, 0);
    return 0;
}
