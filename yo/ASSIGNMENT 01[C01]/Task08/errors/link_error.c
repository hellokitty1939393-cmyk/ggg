/* LINK-TIME ERROR: compute_bill_total is declared (so the compiler is happy)
 * but no .c file defines it, so the linker cannot find the code. */
#include <stdio.h>

long compute_bill_total(int units);     /* declaration only */

int main(void)
{
    long p = compute_bill_total(150);
    printf("Rs %ld.%02ld\n", p / 100, p % 100);
    return 0;
}
