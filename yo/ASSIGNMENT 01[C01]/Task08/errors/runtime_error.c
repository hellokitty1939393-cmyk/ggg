/* RUN-TIME ERROR: compiles and links, but dividing by zero stops the program
 * (SIGFPE) when it runs, e.g. an average bill computed for zero households. */
#include <stdio.h>

int main(void)
{
    volatile int households = 0;         /* volatile: stops the compiler folding the division */
    long total_paise = 160000L;
    printf("about to compute the average bill...\n");
    fflush(stdout);
    printf("average = %ld paise\n", total_paise / households);
    return 0;
}
