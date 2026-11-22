$ gcc -std=c11 -Wall -Wextra  -o task01_alt_text_readings.out task01_alt_text_readings.c -lm
$ ./task01_alt_text_readings.out
pairs processed          : 2000000
integer  total units     : 398536064  rollovers: 5932
text     total units     : 398536064  rollovers: 5932
results identical        : yes
integer  time per pair   : 3.31 ns  (O(1))
text     time per pair   : 31.68 ns  (O(d), d = 5 digits)
slowdown of text         : 9.6x
space per reading        : integer 2 bytes, text 6 bytes (d+1 incl. '\0')
$ gcc -std=c11 -Wall -Wextra  -o task01_data_items.out task01_data_items.c -lm
$ ./task01_data_items.out
DATA ITEM          ROLE      TYPE            JUSTIFICATION
household number   input     unsigned long   800,000 houses > 65535, never negative
category           input     char            one letter code: 'D' domestic, 'C' commercial
previous reading   input     meter_t (u16)   meter register is 16-bit: 0..65535
current reading    input     meter_t (u16)   same register; may be LOWER after roll-over
units              output    unsigned int    (current-previous) mod 65536; never negative
fixed charge       constant  long (paise)    Rs 50.00 = 5000 paise, integer so no rounding
slab limits        constant  int (units)     100 and 200 units, whole units
slab rates         constant  long (paise)    0, 225, 450 paise per unit (fractional rupees!)
energy charge      output    long (paise)    up to 5000*450 = 2,250,000 > 32767
total bill         output    long (paise)    fixed + energy; never negative
district total     output    long long       800,000 bills * ~Rs 415 = 3.3e10 paise > INT_MAX

Rule checks on every consumption 0..5000 units:
  rule 1: bill never negative
  rule 2: total == fixed + energy
  rule 3: more units never gives a smaller bill
  15003 checks run, 0 failed

Sample bills (units -> fixed + energy = total):
    0 units -> Rs 50.00 + Rs 0.00 = Rs 50.00
  100 units -> Rs 50.00 + Rs 0.00 = Rs 50.00
  150 units -> Rs 50.00 + Rs 112.50 = Rs 162.50
  200 units -> Rs 50.00 + Rs 225.00 = Rs 275.00
  350 units -> Rs 50.00 + Rs 900.00 = Rs 950.00

sizeof(meter_t) = 2 bytes
$ gcc -std=c11 -Wall -Wextra  -o task02_alt_double.out task02_alt_double.c -lm
$ ./task02_alt_double.out
Each bill = Rs 123.45 (12345 paise)
       n  double total (rupees)  llround(x*100)   exact paise       
    4000  493800.0000000320      49380000         49380000           error before rounding: 3.201e-08 rupees
   60000  7407000.0000074534     740700000        740700000          error before rounding: 7.453e-06 rupees
  800000  98760000.0014311969    9876000000       9876000000         error before rounding: 1.431e-03 rupees

time per addition: double 2.556 ns, long long 0.874 ns (both O(1))
space per value  : double 8 bytes, long long 8 bytes
note: 100,000,000 additions of 0.01 in double give 1000000.000779 (exact 1000000.000000)
$ gcc -std=c11 -Wall -Wextra  -o task02_consumption.out task02_consumption.c -lm
$ ./task02_consumption.out
sizeof(meter_t) = 2 bytes, maximum reading = 65535
Consumption: 330 units
Consumption: 256 units
$ gcc -std=c11 -Wall -Wextra  -o task02_datatypes.out task02_datatypes.c -lm
$ ./task02_datatypes.out
TYPE                 BYTES  RANGE
char                 1      -128 .. 127
short                2      -32768 .. 32767
unsigned short       2      0 .. 65535
int                  4      -2147483648 .. 2147483647
unsigned int         4      0 .. 4294967295
long                 8      -9223372036854775808 .. 9223372036854775807
long long            8      -9223372036854775808 .. 9223372036854775807
unsigned long long   8      0 .. 18446744073709551615
float                4      max 3.402823e+38, 6 digits, epsilon 1.192093e-07
double               8      max 1.797693e+308, 15 digits, epsilon 2.220446e-16

Worst-case bill = 2187500 paise; worst-case district total = 1750000000000 paise
  fits in int       (max 2147483647)?  NO
  fits in long      (max 9223372036854775807)? yes
  fits in long long (max 9223372036854775807)? yes

unsigned short 65535 + 1 -> 0  (wraps to 0, defined behaviour for unsigned types)

4000 bills of Rs 123.45 each (exact total Rs 493800.00)
  float  rupees total : 493781.2188
  float  error        : -18.7812 rupees
  paise  integer total: 49380000  -> Rs 493800.00  (exact)
$ gcc -std=c11 -Wall -Wextra  -o task03_alt_const_enum.out task03_alt_const_enum.c -lm
$ ./task03_alt_const_enum.out
  0 units -> Rs 50.00
100 units -> Rs 50.00
150 units -> Rs 162.50
200 units -> Rs 275.00
350 units -> Rs 950.00

What is different from #define:
  sizeof(RATE2_PAISE) as const long = 8 bytes   (a #define 225 is an int literal: 4 bytes)
  const variable has an address     = yes (visible in debugger)
  array sized by enum constant      = 3 elements
$ gcc -std=c11 -Wall -Wextra  -o task03_constants.out task03_constants.c -lm
$ ./task03_constants.out
  0 units -> Rs 50.00
100 units -> Rs 50.00
150 units -> Rs 162.50
200 units -> Rs 275.00
350 units -> Rs 950.00
--- the only difference between the two sources:
6c6
< #define RATE2_PAISE 225 /* Rs 2.25 per unit */
---
> #define RATE2_PAISE 230 /* Rs 2.30 per unit */
$ gcc -std=c11 -Wall -Wextra  -o task03_constants_rate230.out task03_constants_rate230.c -lm
$ ./task03_constants_rate230.out
  0 units -> Rs 50.00
100 units -> Rs 50.00
150 units -> Rs 165.00
200 units -> Rs 280.00
350 units -> Rs 955.00
$ gcc -std=c11 -Wall -Wextra  -o task04_alt_inline.out task04_alt_inline.c -lm
$ ./task04_alt_inline.out
  square_long(a+1) = 25
  10 * max_int(2, 3) = 30
  max_int(i++, j) with i=5, j=3 -> result 5, i is now 6 (i++ evaluated once)
  rupees_to_paise(2+3) = 500 paise
=== time per use (400,000,000 uses) ===
-O0
macro            : sum=255900000000  2.267 ns per use
inline function  : sum=255900000000  2.064 ns per use
-O2
macro            : sum=255900000000  0.415 ns per use
inline function  : sum=255900000000  0.405 ns per use

=== code size when the operation is used k = 1000 times (gcc -c, 'size' text section) ===
--- -O0
   text	   data	    bss	    dec	    hex	filename
  29312	      0	      0	  29312	   7280	macro_k1000.o
  33371	      0	      0	  33371	   825b	inline_k1000.o
--- -O2
   text	   data	    bss	    dec	    hex	filename
   5968	      0	      0	   5968	   1750	macro_k1000.o
   5968	      0	      0	   5968	   1750	inline_k1000.o
$ gcc -std=c11 -Wall -Wextra  -o task04_macros.out task04_macros.c -lm
$ ./task04_macros.out
Pitfall 1: missing parentheses around the argument
  BAD_SQUARE(a+1) = 9   (expands to a+1*a+1 = 4+4+1)
  SQUARE(a+1)     = 25   (expands to ((a+1)*(a+1)))
Pitfall 2: missing parentheses around the whole expansion
  10 * BAD_MAX(2, 3) = 2  (expected 30)
  10 * MAX(2, 3)     = 30
Pitfall 3: an argument with a side effect is evaluated twice
  MAX(i++, j) with i=5, j=3 -> result 6, i is now 7 (i++ ran twice; expected 5 and 6)
Useful macro: RUPEES_TO_PAISE
  RUPEES_TO_PAISE(50)  = 5000 paise
  RUPEES_TO_PAISE(2+3) = 500 paise  (argument parenthesised, so 500 and not 202)

=== gcc -E : what the preprocessor really produced for main() ===
$ gcc -std=c11 -E task04_macros.c -o task04_macros.i
553:    printf("  BAD_SQUARE(a+1) = %d   (expands to a+1*a+1 = 4+4+1)\n", a + 1 * a + 1);
554:    printf("  SQUARE(a+1)     = %d   (expands to ((a+1)*(a+1)))\n", ((a + 1) * (a + 1)));
557:    printf("  10 * BAD_MAX(2, 3) = %d  (expected 30)\n", 10 * 2 > 3 ? 2 : 3);
558:    printf("  10 * MAX(2, 3)     = %d\n", 10 * ((2) > (3) ? (2) : (3)));
562:    int r = ((i++) > (j) ? (i++) : (j));
566:    printf("  RUPEES_TO_PAISE(50)  = %ld paise\n", ((long)(50) * 100L));
567:    printf("  RUPEES_TO_PAISE(2+3) = %ld paise  (argument parenthesised, so 500 and not 202)\n", ((long)(2 + 3) * 100L));
$ gcc -std=c11 -Wall -Wextra -o billing_release.out main.c billing.c
  0 units -> Rs 50.00
150 units -> Rs 162.50
350 units -> Rs 950.00

$ gcc -std=c11 -Wall -Wextra -DDEBUG -o billing_debug.out main.c billing.c
[DEBUG] units=0, start with fixed charge=5000 paise
[DEBUG]   total = 5000 paise
  0 units -> Rs 50.00
[DEBUG] units=150, start with fixed charge=5000 paise
[DEBUG]   slab 2: 50 units x 225 = 11250 paise
[DEBUG]   total = 16250 paise
150 units -> Rs 162.50
[DEBUG] units=350, start with fixed charge=5000 paise
[DEBUG]   slab 3: 150 units x 450 = 67500 paise
[DEBUG]   slab 2: 100 units x 225 = 22500 paise
[DEBUG]   total = 95000 paise
350 units -> Rs 950.00

$ gcc -std=c11 -Wall -Wextra -o alt_runtime_debug.out alt_runtime_debug.c
$ ./alt_runtime_debug.out        (debug off)
  0 units -> Rs 50.00
150 units -> Rs 162.50
350 units -> Rs 950.00
$ ./alt_runtime_debug.out -d     (debug on)
[DEBUG] units=0, start with fixed charge=5000 paise
[DEBUG]   total = 5000 paise
  0 units -> Rs 50.00
[DEBUG] units=150, start with fixed charge=5000 paise
[DEBUG]   slab 2: 50 units x 225 = 11250 paise
[DEBUG]   total = 16250 paise
150 units -> Rs 162.50
[DEBUG] units=350, start with fixed charge=5000 paise
[DEBUG]   slab 3: 150 units x 450 = 67500 paise
[DEBUG]   slab 2: 100 units x 225 = 22500 paise
[DEBUG]   total = 95000 paise
350 units -> Rs 950.00

=== include guard evidence: header included twice, compiles without redefinition errors ===
OK: guard_test compiled and ran (exit status 0)

=== space: size of the executables (text = machine code) ===
   text	   data	    bss	    dec	    hex	filename
   2451	    624	      8	   3083	    c0b	billing_release.out
   2769	    624	      8	   3401	    d49	billing_debug.out
   2863	    624	      8	   3495	    da7	alt_runtime_debug.out
debug strings present in executable?
  billing_release.out : 0 lines containing DEBUG
  billing_debug.out   : 4 lines containing DEBUG
  alt_runtime_debug   : 4 lines containing DEBUG

=== time per bill (gcc -O2, 100,000,000 bills) ===
bench: sum=4142187500000, 1.936 ns per bill
bench: sum=4142187500000, 2.091 ns per bill
$ gcc -std=c11 -Wall -Wextra -o task06_alt_fgets.out task06_alt_fgets.c

$ ./task06_alt_fgets.out < input_valid.txt
Enter: household category(D/C) previous current   (end with Ctrl+D, or Ctrl+Z on Windows)
Record 1: household 101 [D] previous=1200 current=1530 units=330 bill=Rs 860.00
Record 2: household 102 [D] previous=65400 current=120 units=256 bill=Rs 527.00
Record 3: household 103 [D] previous=500 current=500 units=0 bill=Rs 50.00
Record 4: household 104 [D] previous=0 current=100 units=100 bill=Rs 50.00
Record 5: household 105 [D] previous=3000 current=3150 units=150 bill=Rs 162.50
Summary: 5 valid, 0 rejected, total Rs 1649.50

$ ./task06_alt_fgets.out < input_invalid.txt
Enter: household category(D/C) previous current   (end with Ctrl+D, or Ctrl+Z on Windows)
Record 1: INVALID INPUT - skipped
Record 2: NEGATIVE READING - skipped
Record 3: IMPLAUSIBLE CONSUMPTION (65206 units) - skipped
Record 4: READING ABOVE 65535 - skipped
Record 5: INVALID CATEGORY 'X' - skipped
Record 6: household 206 [D] previous=100 current=250 units=150 bill=Rs 162.50
Record 7: INVALID INPUT - skipped
Record 8: INVALID INPUT - skipped
Record 9: INVALID INPUT - skipped
Summary: 1 valid, 8 rejected, total Rs 162.50

diff scanf-version vs fgets-version on input_valid.txt : identical output
diff scanf-version vs fgets-version on input_invalid.txt : DIFFERENT
8c8
< Record 7: household 207 [D] previous=100 current=208 units=108 bill=Rs 68.00
---
> Record 7: INVALID INPUT - skipped
10,11c10,11
< Record 9: READING ABOVE 65535 - skipped
< Summary: 2 valid, 7 rejected, total Rs 230.50
---
> Record 9: INVALID INPUT - skipped
> Summary: 1 valid, 8 rejected, total Rs 162.50
$ gcc -std=c11 -Wall -Wextra -o task06_billing_io.out task06_billing_io.c

$ ./task06_billing_io.out < input_valid.txt
Enter: household category(D/C) previous current   (end with Ctrl+D, or Ctrl+Z on Windows)
Record 1: household 101 [D] previous=1200 current=1530 units=330 bill=Rs 860.00
Record 2: household 102 [D] previous=65400 current=120 units=256 bill=Rs 527.00
Record 3: household 103 [D] previous=500 current=500 units=0 bill=Rs 50.00
Record 4: household 104 [D] previous=0 current=100 units=100 bill=Rs 50.00
Record 5: household 105 [D] previous=3000 current=3150 units=150 bill=Rs 162.50
Summary: 5 valid, 0 rejected, total Rs 1649.50

$ ./task06_billing_io.out < input_invalid.txt
Enter: household category(D/C) previous current   (end with Ctrl+D, or Ctrl+Z on Windows)
Record 1: INVALID INPUT - skipped
Record 2: NEGATIVE READING - skipped
Record 3: IMPLAUSIBLE CONSUMPTION (65206 units) - skipped
Record 4: READING ABOVE 65535 - skipped
Record 5: INVALID CATEGORY 'X' - skipped
Record 6: household 206 [D] previous=100 current=250 units=150 bill=Rs 162.50
Record 7: household 207 [D] previous=100 current=208 units=108 bill=Rs 68.00
Record 8: INVALID INPUT - skipped
Record 9: READING ABOVE 65535 - skipped
Summary: 2 valid, 7 rejected, total Rs 230.50
$ gcc -std=c11 -Wall -Wextra -o task06_wrong_specifier.out task06_wrong_specifier.c      (warnings expected)
task06_wrong_specifier.c: In function 'main':
task06_wrong_specifier.c:14:24: warning: format '%d' expects argument of type 'int', but argument 2 has type 'long int' [-Wformat=]
   14 |     printf("  %%d  -> %d   (WRONG: only the low 32 bits are used)\n", big);
      |                       ~^                                              ~~~
      |                        |                                              |
      |                        int                                            long int
      |                       %ld
task06_wrong_specifier.c:22:22: warning: format '%f' expects argument of type 'float *', but argument 3 has type 'double *' [-Wformat=]
   22 |     sscanf("3.14", "%f", &d);               /* %f stores a 4-byte float into an 8-byte double */
      |                     ~^   ~~
      |                      |   |
      |                      |   double *
      |                      float *
      |                     %lf

$ ./task06_wrong_specifier.out
-- printing a long (5,000,000,000)
  %ld -> 5000000000   (correct)
  %d  -> 705032704   (WRONG: only the low 32 bits are used)
-- printing an unsigned int (4,000,000,000)
  %u  -> 4000000000   (correct)
  %d  -> -294967296   (WRONG: read as signed)
-- reading 3.14 into a double
  sscanf with %f  -> d = 5.32861e-315   (WRONG: expected 3.14)
  sscanf with %lf -> d = 3.14   (correct)
-- return value of sscanf (number of fields converted)
  "12 34"  -> returned 2
  "12 abc" -> returned 1 (second field failed)
  "abc 34" -> returned 0 (first field failed)
  ""        -> returned -1 (EOF, no input at all)
-- printing rupees and paise from an integer amount
  16250 paise -> Rs 162.50
  5005 paise -> Rs 50.05   (%02ld keeps the leading zero; %ld.%ld would print Rs 50.5)
$ gcc -std=c11 -Wall -Wextra  -o task07_alt_float_error.out task07_alt_float_error.c -lm
$ ./task07_alt_float_error.out
       n      exact paise      float paise  error (paise)        error/n
    1000         41928350         41928352              2        0.00200
    4000        169001300        169001296             -4       -0.00100
   16000        665668250        665667968           -282       -0.01762
   60000       2487682875       2487673088          -9787       -0.16312
  240000       9988403250       9983227904       -5175346      -21.56394
  800000      33211060825      33238413312       27352487       34.19061

time per addition: float 2.493 ns, long 0.464 ns (both O(1))
space per value  : float 4 bytes, long 8 bytes
100,000,000 additions of 0.01f give 262144.00 (exact 1000000.00) -> float stops growing once the
sum is large enough that 0.01 is below half of one float step.
$ gcc -std=c11 -Wall -Wextra  -o task07_conversions.out task07_conversions.c -lm
task07_conversions.c: In function 'main':
task07_conversions.c:36:114: warning: comparison of integer expressions of different signedness: 'int' and 'unsigned int' [-Wsign-compare]
   36 |     printf("   (-1 < 1u) = %d       (-1 is converted to unsigned 4294967295, so the test is false)\n", minus_one < one);
      |                                                                                                                  ^
$ ./task07_conversions.out
1. integer division
   150 / 100        = 1       (both operands int: fraction .5 is discarded)
   150 / 100.0      = 1.50    (one operand double: the int is converted to double)
   16250 paise / 100 = 162 rupees, remainder 50 paise (use / and % together)
2. cast of a large long to int
   (int)5000000000L = 705032704   (value does not fit in 32 bits; the high bits are lost)
3. signed versus unsigned comparison
   (-1 < 1u) = 0       (-1 is converted to unsigned 4294967295, so the test is false)
4. integer promotion
   reg + 1 = 65536, but reg after reg++ = 0   (the sum is computed as int, the increment is stored back as 16-bit)
5. binary floating point
   0.1 + 0.2 == 0.3 is FALSE; 0.1 + 0.2 = 0.30000000000000004
6. converting rupees to paise
   1.005 * 100 = 100.49999999999999 -> (long) = 100, llround = 100   (the decimal rule says 101)
   integer rule: round_div(1005, 10) = 101
7. cast placed after the multiplication instead of before
   (long)(50000 * 450)   = 22500000   (fits in int, so no harm)
   (long)(5000000 * 450) = -2044967296   (product overflowed in int before the cast)
   (long)5000000 * 450   = 2250000000   (correct)

Rounding rule: whole-paise result = (numerator + denominator/2) / denominator in integers
   1235 Wh at 450 paise/kWh = 555750/1000 paise: truncated = 555, rounded half-up = 556
################ B. ERRORS, CLASSIFIED

--- COMPILE-TIME error
$ gcc -std=c11 -c compile_error.c
compile_error.c: In function 'main':
compile_error.c:7:5: error: expected ',' or ';' before 'printf'
    7 |     printf("Rs %ld.%02ld\n", paise / 100, paise % 100);
      |     ^~~~~~
exit status: 1

--- LINK-TIME error (compilation to .o succeeds, linking fails)
$ gcc -std=c11 -c link_error.c -o link_error.o
compile step OK
$ gcc -std=c11 link_error.o -o link_error.out
/usr/bin/ld: link_error.o: in function `main':
link_error.c:(.text+0x12): undefined reference to `compute_bill_total'
collect2: error: ld returned 1 exit status
exit status: 1

--- RUN-TIME error (compiles and links, fails while running)
$ gcc -std=c11 -Wall -Wextra -o runtime_error.out runtime_error.c
$ ./runtime_error.out
about to compute the average bill...
bash: line 1:   754 Floating point exception./runtime_error.out
exit status: 136  (136 = 128 + signal 8, SIGFPE)
################ D. ALTERNATIVE: several .c files + shared header + Makefile
$ make
gcc -std=c11 -Wall -Wextra -c input.c -o input.o
gcc -std=c11 -Wall -Wextra -c tariff.c -o tariff.o
gcc -std=c11 -Wall -Wextra -c report.c -o report.o
gcc -std=c11 -Wall -Wextra -o billing_split.out input.o tariff.o report.o
$ ./billing_split.out
  0 units -> Rs 50.00
100 units -> Rs 50.00
150 units -> Rs 162.50
200 units -> Rs 275.00
350 units -> Rs 950.00

--- space used by the object files and the executable
   text	   data	    bss	    dec	    hex	filename
    215	      0	      0	    215	     d7	input.o
    184	      0	      0	    184	     b8	tariff.o
    485	      0	      0	    485	    1e5	report.o
   2179	    608	      8	   2795	    aeb	billing_split.out
1576 input.o
2128 report.o
1312 tariff.o

--- build time in microseconds (average of 20 builds, tiny programs)
single file, any change (recompile everything + link) : 46055
split files, full rebuild (3 compiles + link)         : 90495
split files, ONE file changed (1 compile + link)      : 43524
################ A. THE FOUR STAGES (task08_billing.c)
$ gcc -std=c11 -E task08_billing.c -o stages/task08_billing.i      # 1. preprocess
$ gcc -std=c11 -S task08_billing.c -o stages/task08_billing.s      # 2. compile to assembly
$ gcc -std=c11 -c task08_billing.c -o stages/task08_billing.o      # 3. assemble to object file
$ gcc -std=c11 stages/task08_billing.o -o stages/task08_billing.out # 4. link to executable

--- size of every stage's output
   31 task08_billing.c
  565 stages/task08_billing.i
  165 stages/task08_billing.s
  761 total
2144 stages/task08_billing.o
16056 stages/task08_billing.out

--- what the preprocessor replaced or removed (source line  ->  line in the .i file)
4:#define FIXED_CHARGE_PAISE 5000L          /* Rs 50 fixed charge */
9:#define SQUARE_PAISE(x)    ((x) * 100L)   /* macro: replaced by the preprocessor */
13:    long paise = FIXED_CHARGE_PAISE;
28:               tests[i], p / 100, p % 100, SQUARE_PAISE(p / 100));
  becomes:
547:    long paise = 5000L;
562:               tests[i], p / 100, p % 100, ((p / 100) * 100L));
  comments in source: 4   comments in .i file: 0
  #include <stdio.h> pulled in 349 non-empty lines in total (source had 28)

--- start of the assembly (.s) for compute_bill
5:compute_bill:
6-.LFB0:
7-	.cfi_startproc
8-	endbr64
9-	pushq	%rbp
10-	.cfi_def_cfa_offset 16
11-	.cfi_offset 6, -16
12-	movq	%rsp, %rbp
13-	.cfi_def_cfa_register 6
14-	movl	%edi, -20(%rbp)
15-	movq	$5000, -8(%rbp)
16-	cmpl	$200, -20(%rbp)
17-	jle	.L2

--- symbols in the object file (U = undefined, resolved by the linker from libc)
                 U __stack_chk_fail
0000000000000000 T compute_bill
0000000000000060 T main
                 U printf

--- run the executable
  0 units -> Rs 50.00   (rupees to paise macro: 5000)
150 units -> Rs 162.50   (rupees to paise macro: 16200)
350 units -> Rs 950.00   (rupees to paise macro: 95000)
################ C. WARNINGS (-Wall -Wextra) AND THEIR FIX
$ gcc -std=c11 -Wall -Wextra -c warn_demo.c -o warn_demo.o
warn_demo.c: In function 'compute':
warn_demo.c:9:15: warning: comparison of integer expressions of different signedness: 'int' and 'unsigned int' [-Wsign-compare]
    9 |     if (units > limit)
      |               ^
warn_demo.c:11:14: warning: format '%d' expects argument of type 'int', but argument 2 has type 'long int' [-Wformat=]
   11 |     printf("%d\n", paise);
      |             ~^     ~~~~~
      |              |     |
      |              int   long int
      |             %ld
warn_demo.c:6:9: warning: unused variable 'never_used' [-Wunused-variable]
    6 |     int never_used;
      |         ^~~~~~~~~~
warn_demo.c:4:29: warning: unused parameter 'unused_param' [-Wunused-parameter]
    4 | long compute(int units, int unused_param)
      |                         ~~~~^~~~~~~~~~~~

$ gcc -std=c11 -Wall -Wextra -c warn_fixed.c -o warn_fixed.o
no warnings
$ gcc -std=c11 -Wall -Wextra -o billing.out main.c billing.c
$ gcc -std=c11 -Wall -Wextra -o test_billing.out test_billing.c billing.c

$ ./test_billing.out
CASE                               readings               EXPECTED       ACTUAL         RESULT
slab 1 normal (50 units)           100 -> 150             50 u, Rs 50.00 50 u, Rs 50.00 PASS
slab 2 normal (150 units)          3000 -> 3150           150 u, Rs 162.50 150 u, Rs 162.50 PASS
slab 3 normal (350 units)          10000 -> 10350         350 u, Rs 950.00 350 u, Rs 950.00 PASS
zero units                         500 -> 500             0 u, Rs 50.00  0 u, Rs 50.00  PASS
exactly 100 units                  1000 -> 1100           100 u, Rs 50.00 100 u, Rs 50.00 PASS
101 units                          1000 -> 1101           101 u, Rs 52.25 101 u, Rs 52.25 PASS
exactly 200 units                  0 -> 200               200 u, Rs 275.00 200 u, Rs 275.00 PASS
201 units                          0 -> 201               201 u, Rs 279.50 201 u, Rs 279.50 PASS
maximum plausible 5000 units       0 -> 5000              5000 u, Rs 21875.00 5000 u, Rs 21875.00 PASS
roll-over 65535 -> 0 (1 unit)      65535 -> 0             1 u, Rs 50.00  1 u, Rs 50.00  PASS
roll-over 65400 -> 120             65400 -> 120           256 u, Rs 527.00 256 u, Rs 527.00 PASS
roll-over 65535 -> 99 (100)        65535 -> 99            100 u, Rs 50.00 100 u, Rs 50.00 PASS
negative previous reading          -5 -> 100              reject (1)     reject (1)     PASS
negative current reading           100 -> -1              reject (1)     reject (1)     PASS
reading above 65535                70000 -> 10            reject (2)     reject (2)     PASS
current < previous, no roll-over   1530 -> 1200           reject (3)     reject (3)     PASS
5001 units (above the limit)       0 -> 5001              reject (3)     reject (3)     PASS
hand-calculated total of 5 bills   0,100,150,200,350      Rs 1487.50                    PASS
  (actual total printed below)
  total = Rs 1487.50

0 of 18 checks failed
(exit status 0)

$ ./billing.out < input_hand5.txt      # 5 bills, total calculated by hand = Rs 1487.50
Record 1: household 1 [D] previous=0 current=0 units=0 bill=Rs 50.00
Record 2: household 2 [D] previous=100 current=200 units=100 bill=Rs 50.00
Record 3: household 3 [D] previous=1000 current=1150 units=150 bill=Rs 162.50
Record 4: household 4 [D] previous=5000 current=5200 units=200 bill=Rs 275.00
Record 5: household 5 [D] previous=20000 current=20350 units=350 bill=Rs 950.00
Summary: 5 bills, 0 rejected, total collected Rs 1487.50

$ ./billing.out < input_all_cases.txt  # normal, boundary, roll-over and invalid input
Record 1: household 301 [D] previous=100 current=150 units=50 bill=Rs 50.00
Record 2: household 302 [D] previous=1000 current=1100 units=100 bill=Rs 50.00
Record 3: household 303 [D] previous=0 current=200 units=200 bill=Rs 275.00
Record 4: household 304 [D] previous=500 current=500 units=0 bill=Rs 50.00
Record 5: household 305 [D] previous=65535 current=0 units=1 bill=Rs 50.00
Record 6: household 306 [D] previous=65400 current=120 units=256 bill=Rs 527.00
Record 7: household 307 [D] previous=3000 current=3150 units=150 bill=Rs 162.50
Record 8: household 308 [D] previous=10000 current=10350 units=350 bill=Rs 950.00
Record 9: REJECTED - not in the form: household category previous current
Record 10: REJECTED - NEGATIVE READING (household 310, previous=-5, current=100)
Record 11: REJECTED - IMPLAUSIBLE CONSUMPTION (decrease without a real roll-over, or meter fault) (household 311, previous=1530, current=1200)
Record 12: REJECTED - READING ABOVE 65535 (household 312, previous=70000, current=10)
Record 13: REJECTED - category 'X' is not D or C
Record 14: REJECTED - not in the form: household category previous current
Record 15: REJECTED - not in the form: household category previous current
Summary: 8 bills, 7 rejected, total collected Rs 2114.50
$ gcc -std=c11 -Wall -Wextra -o alt_slab_array.out alt_slab_array.c billing.c
$ ./alt_slab_array.out   (unoptimised build)
units 0..5000 compared: 0 mismatches between loop version and if-version
fixed if-statements : 3.214 ns per bill (sum 4142187500000)
loop over 3 slabs   : 7.918 ns per bill (sum 4142187500000)
extra space (two arrays): 36 bytes

$ gcc -std=c11 -O2 -o alt_slab_array_O2.out alt_slab_array.c billing.c
$ ./alt_slab_array_O2.out
units 0..5000 compared: 0 mismatches between loop version and if-version
fixed if-statements : 1.695 ns per bill (sum 4142187500000)
loop over 3 slabs   : 3.229 ns per bill (sum 4142187500000)
extra space (two arrays): 36 bytes
$ gcc -std=c11 -Wall -Wextra  -o task10_expectation_vs_execution.out task10_expectation_vs_execution.c -lm
$ ./task10_expectation_vs_execution.out
A. totals of n bills: exact paise (long long) versus float and double rupees
       n        exact paise         float rupees        double rupees    float error   double error
    4000          162254900         1622549.0000       1622549.000000         0.0000     0.00000000
   60000         2486234325        24862312.0000      24862343.250000       -31.2500     0.00000000
  800000        33181111750       332100480.0000     331811117.500000    289362.5000     0.00000000
   (errors are in rupees; the paise total is exact by construction)

B. does the district total overflow? (800,000 bills, paise)
  exact district total      = 33181111750 paise = Rs 331811117.50
  int       (4 bytes, max 2147483647)          : OVERFLOWS
            first overflow at bill number 51717
  long      (8 bytes, max 9223372036854775807) : no overflow on this system
  long long (8 bytes, max 9223372036854775807) : no overflow
  NOTE: the C standard only guarantees long >= 32 bits. Where long is 32-bit (Windows) it
        behaves like int above and overflows. A long long total is safe everywhere.

C. this system versus the minimum guaranteed by the C standard
type          bytes  bits here   standard min   verdict
char              1          8         8 bits   equal to the minimum
short             2         16        16 bits   equal to the minimum
int               4         32        16 bits   larger than the minimum
long              8         64        32 bits   larger than the minimum
long long         8         64        64 bits   equal to the minimum
float             4          -       6 digits   FLT_DIG = 6  (meets the minimum)
double            8          -      10 digits   DBL_DIG = 15 (meets the minimum)
  USHRT_MAX = 65535 (standard guarantees at least 65535: the 16-bit meter register fits)
  INT_MAX = 2147483647 (standard guarantees at least 32767)
  LONG_MAX = 9223372036854775807 (standard guarantees at least 2147483647)
$ gcc -std=c11 -Wall -Wextra  -o task10_alt_double_total.out task10_alt_double_total.c -lm
$ ./task10_alt_double_total.out
800,000 bills
  long long paise total        : 33181111750
  double (whole paise) total   : 33181111750.0   difference 0.0 paise
  double (rupees) total x 100  : 33181111750.0000   difference 0.000000 paise

Where each type stops being exact (paise):
  int       overflows above 2147483647            = Rs 21474836
  long long overflows above 9223372036854775807 = Rs 9.2234e+16
  double    exact for whole numbers up to 2^53 = 9007199254740992 = Rs 9.0072e+13
  800,000 bills of the worst-case Rs 21,875 = Rs 1.750e+10: far below both limits
  proof: 2^53 + 1 in double = 9007199254740992 (the +1 is lost: precision loss, no overflow)
  proof: 2^53 + 2 in double = 9007199254740994

time per addition: double 2.761 ns, long long 0.634 ns
space per variable: double 8 bytes, long long 8 bytes
$ gcc -std=c11 -Wall -Wextra -o task11_config_tariff.out task11_config_tariff.c

$ ./task11_config_tariff.out tariff.cfg
tariff loaded from tariff.cfg: fixed 5000, slabs 100/200, rates 0/225/450 paise
  0 units -> Rs 50.00
100 units -> Rs 50.00
150 units -> Rs 162.50
200 units -> Rs 275.00
350 units -> Rs 950.00
start-up cost: 2.26 microseconds to read and validate the file (average of 20000 reads)
space for the six tariff values: 48 bytes (a #define occupies none)

$ ./task11_config_tariff.out tariff_revised.cfg      # NO recompile: only the text file differs
tariff loaded from tariff_revised.cfg: fixed 5000, slabs 100/200, rates 0/230/450 paise
  0 units -> Rs 50.00
100 units -> Rs 50.00
150 units -> Rs 165.00
200 units -> Rs 280.00
350 units -> Rs 955.00
start-up cost: 2.31 microseconds to read and validate the file (average of 20000 reads)
space for the six tariff values: 48 bytes (a #define occupies none)

--- invalid configuration is refused, not silently used
cannot use tariff_invalid.cfg (error -5)
$ gcc -std=c11 -Wall -Wextra -o task11_final_demo.out task11_final_demo.c
Tariff in force: fixed 5000, slab 2 rate 225 paise/unit
  0 units -> Rs 50.00
100 units -> Rs 50.00
150 units -> Rs 162.50
200 units -> Rs 275.00
350 units -> Rs 950.00
roll-over 65400 -> 120 : 256 units
district total (800,000 bills) = 33181111750 paise = Rs 331811117.50
sizeof(paise_t) = 8 bytes, sizeof(meter_t) = 2 bytes

=== TARIFF REVISION, compiled-in design: edit one line of final_design.h, recompile, redistribute ===
--- the only change:
20c20
< #define RATE2_PAISE         ((paise_t)225)
---
> #define RATE2_PAISE         ((paise_t)230)
Tariff in force: fixed 5000, slab 2 rate 230 paise/unit
  0 units -> Rs 50.00
100 units -> Rs 50.00
150 units -> Rs 165.00
200 units -> Rs 280.00
350 units -> Rs 955.00
recompile time: 44 ms (plus copying the new executable to every office computer)
File readings_house_A.txt
  readings               : 2880 (30.0 days)
  total energy           : 552000 Wh = 552.000 kWh
  peak (18:00-22:00) energy: 192000 Wh
  fixed charge               Rs 50.00
  energy charge (no peak rule) Rs 1809.00
  peak surcharge             Rs 125.84
  TOTAL BILL                 Rs 1984.84

File readings_house_B.txt
  readings               : 2880 (30.0 days)
  total energy           : 144000 Wh = 144.000 kWh
  peak (18:00-22:00) energy: 0 Wh
  fixed charge               Rs 50.00
  energy charge (no peak rule) Rs 99.00
  peak surcharge             Rs 0.00
  TOTAL BILL                 Rs 149.00

File readings_house_C.txt
  readings               : 2880 (30.0 days)
  total energy           : 1200000 Wh = 1200.000 kWh
  peak (18:00-22:00) energy: 1200000 Wh
  fixed charge               Rs 50.00
  energy charge (no peak rule) Rs 4725.00
  peak surcharge             Rs 945.00
  TOTAL BILL                 Rs 5720.00

--- revised tariff (no recompile)
File readings_house_A.txt
  readings               : 2880 (30.0 days)
  total energy           : 552000 Wh = 552.000 kWh
  peak (17:00-23:00) energy: 228000 Wh
  fixed charge               Rs 50.00
  energy charge (no peak rule) Rs 1809.00
  peak surcharge             Rs 186.80
  TOTAL BILL                 Rs 2045.80

--- invalid files
READINGS ERROR: line 100: not a whole number of Wh
READINGS ERROR: line 51: 6000 Wh in 15 minutes exceeds the 5000 Wh limit
READINGS ERROR: more than 2976 readings: a bill covers at most 31 days
