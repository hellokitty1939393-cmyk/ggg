/* The same program with every warning of warn_demo.c resolved. */
#include <stdio.h>

long compute(unsigned int units)               /* unused parameter removed; type matches limit */
{
    long paise = 5000L;                        /* never_used variable removed */
    const unsigned int limit = 100;
    if (units > limit)                         /* both operands unsigned: no sign-compare warning */
        paise += (long)(units - 100) * 225L;
    printf("%ld\n", paise);                    /* %ld for a long */
    return paise;
}

int main(void)
{
    compute(150);
    return 0;
}
