/* COMPILE-TIME ERROR: a semicolon is missing, so the compiler cannot parse the file. */
#include <stdio.h>

int main(void)
{
    long paise = 5000L
    printf("Rs %ld.%02ld\n", paise / 100, paise % 100);
    return 0;
}
