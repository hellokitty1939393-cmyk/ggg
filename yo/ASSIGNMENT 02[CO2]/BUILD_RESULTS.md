# BUILD_RESULTS

Student: T.R Sangeet | Register number: 1921260245 | Course: CSA02 C Programming | Assignment 2 (CO2)

Compiler: `gcc (Ubuntu 13.3.0-6ubuntu2~24.04.1) 13.3.0` on Linux x86_64

Every program was compiled with `-Wall -Wextra` and executed. Output below is the raw output of that run
(timing lines such as `CPU time` differ from run to run; all operation counts are deterministic).

## Task01/q1_precedence.c

- compile: `gcc -Wall -Wextra -o q1 q1_precedence.c`
- compiler warnings: 1 (intentional - see report)
- exit status: 0

```text
Bill   price qty sen | BUGGY total/net (pred)   | BUGGY total/net (observed)  | INTENDED total / net
A        120  10   1 | pred 1080 / 1030          | obs 1080 / 1030 [MATCH]      |  1071.00 /  1021.00
       gross=1200.00 discount=180.00 taxable=1020.00 gst=51.00 | error of buggy total = +9.00
B         45   7   0 | pred  330 / 330           | obs  330 / 330  [MATCH]      |   330.75 /   330.75
       gross=315.00 discount=0.00 taxable=315.00 gst=15.75 | error of buggy total = -0.75
C        333   3   1 | pred  899 / 899           | obs  899 / 899  [MATCH]      |   891.61 /   891.61
       gross=999.00 discount=149.85 taxable=849.15 gst=42.46 | error of buggy total = +7.39

count = 5; count = count++ + 1;  ->  count = 6   (UB: any value is allowed;
this compiler happens to give 6, a different compiler could give 7 or crash)
```

compiler diagnostics:

```text
q1_precedence.c: In function ‘main’:
q1_precedence.c:62:11: warning: operation on ‘count’ may be undefined [-Wsequence-point]
   62 |     count = count++ + 1;      /* modifies 'count' twice without a sequence point */
      |     ~~~~~~^~~~~~~~~~~~~
```

## Task02/q2_shortcircuit.c

- compile: `gcc -Wall -Wextra -o q2 q2_shortcircuit.c`
- compiler warnings: 0
- exit status: 0

```text
=== Experiment 1: is the second operand evaluated? ===
  0 && f():
    A evaluated -> 0
    result=0 (B skipped)
  1 && f():
    A evaluated -> 1
    B evaluated -> 1
    result=1 (B evaluated)
  1 || f():
    A evaluated -> 1
    result=1 (B skipped)
  0 || f():
    A evaluated -> 0
    B evaluated -> 0
    result=0 (B evaluated)
  0 & f()  (bitwise, NO short-circuit):
    A evaluated -> 0
    B evaluated -> 1
    result=0 (B evaluated even though A is 0)
  Value difference on non-boolean operands: 1 && 2 = 1 , 1 & 2 = 0

=== Experiment 2: slow-function calls for 1000 passengers ===
  population: 20% senior, 50% eligible class, 10% card holders
  V1 (senior&&elig)||verify : calls= 887  granted=185
  V2 verify||(senior&&elig) : calls=1000  granted=185
  V3 nested if (V1 order)   : calls= 887  granted=185
  V4 (senior&elig)|verify    : calls=1000  granted=185

=== Experiment 3: effect of how often the cheap test is true ===
  %senior %elig | P(cheap true) | calls V1 | calls V2 | saved by order
       5    50 |         2.50% |      964 |     1000 | 36
      20    50 |        10.00% |      887 |     1000 | 113
      50    50 |        25.00% |      738 |     1000 | 262
      90    90 |        81.00% |      189 |     1000 | 811

=== Changed condition: verify_card() now writes an audit log ===
  V1 audit-log entries = 887 of 1000 passengers (short-circuit skips the rest)
  V2 audit-log entries = 1000 of 1000 passengers (every passenger logged)
  V4 audit-log entries = 1000 of 1000 passengers (every passenger logged)
```

## Task03/q3_register.c

- compile: `gcc -Wall -Wextra -o q3 q3_register.c`
- compiler warnings: 0
- exit status: 0

```text
00000101
00000110
AC is ON, PUMP is OFF
```

## Task03/q3_inquiry.c

- compile: `gcc -Wall -Wextra -O0 -o q3i q3_inquiry.c`
- compiler warnings: 1 (intentional - see report)
- exit status: 0

```text
=== Counting devices ON (bitwise only: reg &= reg - 1) ===
  register 00000110 (value 6) -> 2 devices ON ; register 11111111 -> 8 ; register 0 -> 0

=== Inquiry 1: reg & 1 << dev   vs   (reg & 1) << dev ===
Precedence: << binds tighter than &, so  reg & 1 << dev  ==  reg & (1 << dev)
reg=6 (00000110), dev=2
  reg & 1 << dev     = 4   (mask test: bit 2 of reg -> value 4 = ON, but not 1!)
  (reg & 1) << dev   = 0   (tests bit 0 (LIGHT) then shifts it -> WRONG device)
  (reg >> dev) & 1   = 1   (correct, returns exactly 0 or 1)

=== Inquiry 2: signed char with bit 7 set ===
  signed char  sc = 0x80 -> value -128 ; sc promoted to int = 0xFFFFFF80
  unsigned char uc = 0x80 -> value 128 ; uc promoted to int = 0x00000080
  sc >> 1 = -64  (sign extension: arithmetic shift, implementation-defined)
  uc >> 1 = 64  (logical: 01000000)
  (sc >> 7) & 1 = 1, but sc >> 7 = -1 (all ones) if the '& 1' is forgotten
  sc == 0x80 ? false   uc == 0x80 ? true   (-128 != 128 after promotion)

=== Alternative: char state[8] (1 byte/device) vs 1 byte register ===
  memory for 1000000 homes : bit-register = 1000000 bytes (1.0 MB), array = 8000000 bytes (8.0 MB)
  count devices ON (all homes): bit-register = 3998064 ON, 3998064 loop iterations, 0.0175 s
                                array        = 3998064 ON, 8000000 loop iterations, 0.0198 s
  single set/clear/toggle/test: O(1) in both; counting ON devices: O(k) (k=ON bits <= 8) vs O(8)
```

compiler diagnostics:

```text
q3_inquiry.c: In function ‘main’:
q3_inquiry.c:42:15: warning: comparison is always false due to limited range of data type [-Wtype-limits]
   42 |            sc == 0x80 ? "true" : "false", uc == 0x80 ? "true" : "false");
      |               ^~
```

## Task04/q4_grade.c

- compile: `gcc -Wall -Wextra -o q4 q4_grade.c`
- compiler warnings: 0
- exit status: 0

```text
100:S 95:S 83:A 50:D 49:F -5:?
```

## Task04/q4_compare.c

- compile: `gcc -Wall -Wextra -o q4c q4_compare.c`
- compiler warnings: 1 (intentional - see report)
- exit status: 0

```text
=== Required test values ===
marks | ladder switch table | switch(no range check) | comparisons in ladder
  100 |   S      S      S   |           S            | 3
   90 |   S      S      S   |           S            | 3
   89 |   A      A      A   |           A            | 4
    0 |   F      F      F   |           F            | 7
   -1 |   ?      ?      ?   |           F            | 2
  101 |   ?      ?      ?   |           S            | 2

=== Boundary-exposing test set (every grade edge +-1, both ends) ===
marks:   -1   0   1  49  50  51  59  60  61  69  70  71  79  80  81  89  90  91  99 100 101
ladder:   ?   F   F   F   D   D   D   C   C   C   B   B   B   A   A   A   S   S   S   S   ?
switch:   ?   F   F   F   D   D   D   C   C   C   B   B   B   A   A   A   S   S   S   S   ?
table :   ?   F   F   F   D   D   D   C   C   C   B   B   B   A   A   A   S   S   S   S   ?
nochk :   F   F   F   F   D   D   D   C   C   C   B   B   B   A   A   A   S   S   S   S   S
nobrk :   ?   F   F   F   D   D   D   C   C   C   B   B   B   B   B   B   S   S   S   S   ?

=== Exhaustive check: marks -20..120 (141 values), ladder is the reference ===
  switch mismatches: 0 | table mismatches: 0
  no-range-check switch mismatches: 40 of 141 (the values -20..-1 and 101..120)
  missing-break switch mismatches: 10 (marks 80..89 return 'B', first at 80)

=== Missing-break demo (the TODO program with 'case 8' break removed) ===
  expected      : 100:S 95:S 83:A 50:D 49:F -5:?
  without break : 100:S 95:S 83:B 50:D 49:F -5:? 
  -> 83 is now 'B' (A falls through into case 7)

=== Scholarship (grade x income band) via 2-D lookup table: % fee waiver ===
  grade | <2.5L  2.5-5L  >5L
    S   |  100%     75%    50%
    A   |   50%     25%     0%
    B   |   25%      0%     0%
    C   |    0%      0%     0%
    D   |    0%      0%     0%
    F   |    0%      0%     0%
  e.g. marks 83, income band 1 -> grade A -> 25% waiver
```

compiler diagnostics:

```text
q4_compare.c: In function ‘grade_switch_nobreak’:
q4_compare.c:63:19: warning: this statement may fall through [-Wimplicit-fallthrough=]
   63 |         case 8: g = 'A';                  /* <-- break removed: falls into case 7 */
      |                 ~~^~~~~
q4_compare.c:64:9: note: here
   64 |         case 7: g = 'B'; break;
      |         ^~~~
```

## Task05/q5_is_prime.c

- compile: `gcc -Wall -Wextra -o q5 q5_is_prime.c`
- compiler warnings: 0
- exit status: 0

```text
      97 prime     divisions = 8
     100 not prime divisions = 1
    7919 prime     divisions = 87
 1000003 prime     divisions = 999
```

## Task05/q5_variants.c

- compile: `gcc -Wall -Wextra -O0 -o q5v q5_variants.c`
- compiler warnings: 0
- exit status: 0

```text
=== Division counts (checks) for each version ===
        n result    | for 2..n-1  for i*i    while  do-while do-w (bad)
        2 prime     |          0        0        0         0          1
            ^ unguarded do-while says not prime for 2 : WRONG
        3 prime     |          1        0        0         0          1
       97 prime     |         95        8        8         8          8
      100 not prime |          1        1        1         1          1
     7919 prime     |       7917       87       87        87         87
  1000003 prime     |    1000001      999      999       999        999
   999983 prime     |     999981      998      998       998        998
  1000001 not prime |        100      100      100       100        100

=== Why do-while needs care for n = 2 and n = 3 ===
  n=2 unguarded: tests 2 % 2 == 0 first -> result NOT prime (WRONG, 2 is prime), checks=1
  n=3 unguarded: result prime but performs 1 useless division(s) although 2*2 > 3

=== Why i * i <= n can overflow ===
  32-bit: i=65535  i*i computed = 4294836225  (true 4294836225)  loop test computed=1 correct=1
  32-bit: i=65536  i*i computed = 0  (true 4294967296)  loop test computed=1 correct=0   <-- WRONG: loop would not stop
  32-bit: i=65537  i*i computed = 131073  (true 4295098369)  loop test computed=1 correct=0   <-- WRONG: loop would not stop
  64-bit: i=2^32 -> i*i = 0 (wraps to 0) so i*i <= n is true again for any n
  safe form: while (i <= n / i)   (no multiplication, cannot overflow)

=== Changing the condition to i < n (naive) -- tickets from the TODO program ===
      97 prime     divisions = 95
     100 not prime divisions = 1
    7919 prime     divisions = 7917
 1000003 prime     divisions = 1000001

=== Alternative: Sieve of Eratosthenes up to N = 1,000,003 ===
  trial division (i*i<=n), all n <= N : 67741504 divisions, primes found = 78499
  naive 2..n-1 for all n <= 20000 only: 21267570 divisions
  sieve, one pass                      : 2122051 marking operations, primes found = 78499, extra memory = 1000004 bytes
  per query afterwards: sieve = 1 array lookup, trial = up to 999 divisions
```

## Task06/q6_loan.c

- compile: `gcc -Wall -Wextra -o q6 q6_loan.c -lm`
- compiler warnings: 0
- exit status: 0

```text
=== Correctness check: Rs 10000 @ 2%/month, repay Rs 2000 ===
month   interest      bal+int       paid    closing
    1     200.00     10200.00    2000.00    8200.00
    2     164.00      8364.00    2000.00    6364.00
    3     127.28      6491.28    2000.00    4491.28
    4      89.83      4581.11    2000.00    2581.11
    5      51.62      2632.73    2000.00     632.73
    6      12.65       645.38     645.38       0.00
months = 6, total interest = 645.38, total paid = 10645.38
hand-calculated schedule vs program (6 rows, tolerance 0.006): ALL MATCH; hand total interest 645.38 vs 645.38

=== Why balance != 0 is dangerous (floating point) ===
1.0 minus 0.1 repeated: after exactly 10 subtractions balance = 1.3877787807814457e-16 (not 0)
so 'while (bal != 0)' keeps going: 12 iterations ran (stopped only by the k<12 guard), bal = -0.2

=== Growth investigation: months vs repayment (P=10000, r=2%, monthly interest at start = 200) ===
  repay E | predicted n=ceil(-ln(1-rP/E)/ln(1+r)) | measured months | total interest
  5000.00 |     2.06 -> 3                        | 3               |     310.08
  2000.00 |     5.32 -> 6                        | 6               |     645.38
  1000.00 |    11.27 -> 12                       | 12              |    1270.33
   500.00 |    25.80 -> 26                       | 26              |    2898.73
   300.00 |    55.48 -> 56                       | 56              |    6644.17
   250.00 |    81.27 -> 82                       | 82              |   10318.98
   210.00 |   153.74 -> 154                      | 154             |   22286.50
   205.00 |   187.53 -> 188                      | 188             |   28444.00
   201.00 |   267.81 -> 268                      | 268             |   43829.75
   200.50 |   302.69 -> 303                      | 303             |   50688.80
   200.01 |   500.11 -> 501                      | 501             |   90027.66
   200.00 | never (rP/E >= 1)                     | limit 5000 hit  | grows without bound
   190.00 | never (rP/E >= 1)                     | limit 5000 hit  | grows without bound

=== Deployment decision: safety limit of 360 months via break ===
  repay 2000.000 : repaid in 6 months, interest Rs 645.38
  repay 190.000 : REFUSED - repayment must exceed the first month's interest Rs 200.00
  repay 200.001 : STOPPED at 360 months, Rs 9937.67 still owed - show 'increase EMI / extend tenure, manual review'
```

## Task07/q7_redesign.c

- compile: `gcc -Wall -Wextra -o q7 q7_redesign.c`
- compiler warnings: 0
- exit status: 0

```text
=== A. Diagnosis (original program, evidence from Q5) ===
  large prime 1000003: 999 divisions, every one of them 'n % i' with i = 2..1000
  - the count grows as sqrt(n)  (97 -> 8, 7919 -> 87, 1000003 -> 999)
  - repeated work: every even i > 2 is tried although n % 2 already proved n odd;
    every multiple of 3 is tried although n % 3 was already tested
    => about 2/3 of the divisions can never find a divisor

=== E. Same inputs, same counts: Original -> Redesigned ===
        n result    |  original  redesign predicted | ratio
        5 prime     |         1         2         2 | 2.000
        7 prime     |         1         2         2 | 2.000
       25 not prime |         4         3         3 | 0.750
       97 prime     |         8         4         4 | 0.500
      100 not prime |         1         1         1 | 1.000
     7919 prime     |        87        30        30 | 0.345
   999983 prime     |       998       334       334 | 0.335
  1000001 not prime |       100        35        35 | 0.350
  1000003 prime     |       999       334       334 | 0.334

=== E. Batch validation: every n in 0 .. 1,000,003 ===
  answers that differ between the two programs : 0  (primes found: 78499)
  total divisions  original = 67741504 , redesign = 23739568 , ratio = 0.350 (65.0% fewer)
  CPU time (this run, varies)  original = 0.231 s , redesign = 0.082 s
  per-n comparison: redesign cheaper for 333328 values, equal for 666674, MORE expensive for 2

=== F. Where the original is still preferable (small n) ===
  n <= 100 : redesign needs MORE divisions for 2 values;  n <= 1000 : 2 values
  first such n: 5 7 (small primes: the two fixed tests 2 and 3 cost more than the loop saves)
```
