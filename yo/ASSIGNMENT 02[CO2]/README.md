# CSA02-1921260245-Assignment2

| | |
|---|---|
| **Student name** | T.R Sangeet |
| **Register number** | 1921260245 |
| **Course** | CSA02 – C Programming (Saveetha Institute of Medical and Technical Sciences) |
| **Assignment** | Assignment 2 – CO2 (operators, decision-making, looping), 50 marks |
| **Compiler / version** | GCC 13.3.0 (Ubuntu 13.3.0-6ubuntu2~24.04.1), C default standard (gnu17) |
| **GitHub repository link** | `https://github.com/<your-username>/CSA02-1921260245-Assignment2`  ← fill in after pushing |

## Compile command (exact)

Every program is compiled the same way (only the `-lm` / `-O0` differ where noted in the table):

```bash
gcc -Wall -Wextra -o <exe> <file>.c            # Q6 additionally needs: -lm
```

## Repository layout

```
Task01/  q1_precedence.c            Q1  precedence, associativity, discount bug, count++ UB
Task02/  q2_shortcircuit.c          Q2  short-circuit evaluation, call counting, audit-log change
Task03/  q3_register.c              Q3  Complete the Code (TODO 1-4) – bit register
         q3_inquiry.c               Q3  precedence / signed-char inquiry + array alternative
Task04/  q4_grade.c                 Q4  Complete the Code (TODO 1) – switch grade()
         q4_compare.c               Q4  ladder vs switch vs table, boundary tests, fallthrough
Task05/  q5_is_prime.c              Q5  Complete the Code (TODO 1) – i*i <= n
         q5_variants.c              Q5  for / while / do-while, overflow, sieve alternative
Task06/  q6_loan.c                  Q6  loan schedule, termination, growth, safety limit
Task07/  q7_redesign.c              Q7  Day-4: diagnose, redesign (6k±1), validate
tools/   screenshot.py, make_charts.py, build_results.py   (regenerate screenshots / charts / BUILD_RESULTS.md)
BUILD_RESULTS.md                    raw output of every program
REPORT_DRAFT.md                     evidence for Q1–Q7 (predictions, analysis, tables, defences)
```

Each `TaskNN/` folder holds the C source, the output screenshots (`output_*.png`) and, where the
question asks for graphs, a chart (`*_chart.png`). No input files are needed – every program is self-contained.

## How to run

```bash
cd Task01 && gcc -Wall -Wextra -o q1 q1_precedence.c && ./q1
cd ../Task02 && gcc -Wall -Wextra -o q2 q2_shortcircuit.c && ./q2
cd ../Task03 && gcc -Wall -Wextra -o q3 q3_register.c && ./q3
             && gcc -Wall -Wextra -o q3i q3_inquiry.c && ./q3i
cd ../Task04 && gcc -Wall -Wextra -o q4 q4_grade.c && ./q4
             && gcc -Wall -Wextra -o q4c q4_compare.c && ./q4c
cd ../Task05 && gcc -Wall -Wextra -o q5 q5_is_prime.c && ./q5
             && gcc -Wall -Wextra -o q5v q5_variants.c && ./q5v
cd ../Task06 && gcc -Wall -Wextra -o q6 q6_loan.c -lm && ./q6
cd ../Task07 && gcc -Wall -Wextra -o q7 q7_redesign.c && ./q7
```

## Result of each task

| Task | Result |
|---|---|
| **Q1** | The three predicted bills match the observed buggy output exactly (1080/1030, 330/330, 899/899). Intended amounts are 1021.00, 330.75, 891.61. Two real bugs found: GST is charged on the *undiscounted* amount, and integer division truncates paise. `count = count++ + 1;` is undefined behaviour; `-Wall` reports `-Wsequence-point`. Corrected version uses intermediate variables (`gross, discount, taxable, gst`). |
| **Q2** | For 1000 passengers: `(senior&&elig)\|\|verify` = 887 slow calls, `verify\|\|(senior&&elig)` = 1000, nested-if = 887, non-short-circuit `&`/`\|` = 1000. All four grant the same 185 passengers. With the audit log, the short-circuit order logs only 887 passengers, the others log all 1000. |
| **Q3** | TODO 1-4 completed with bitwise operators only; output `00000101`, `00000110`, `AC is ON, PUMP is OFF` equals the expected output. Register values predicted before running all matched. `reg & 1 << dev` ≠ `(reg & 1) << dev` demonstrated (4 vs 0); signed `char` 0x80 promotes to -128. Array alternative: 8 MB vs 1 MB for 1,000,000 homes. |
| **Q4** | TODO 1 completed (`100:S 95:S 83:A 50:D 49:F -5:?` matches). Ladder, switch and table agree on all 141 values tested (-20..120). Switch without range check gets 40 of them wrong (-1 → F, 101 → S). Removing one `break` turns every mark 80–89 into `B`. Scholarship rule uses a 2-D lookup table. |
| **Q5** | TODO 1 completed; divisions 8 / 1 / 87 / 999 match expected. Changing to `i < n` gives 95 / 1 / 7917 / 1000001. `for`, `while`, guarded `do-while` all agree; unguarded `do-while` wrongly reports 2 as not prime. Sieve: 2,122,051 marking ops for N = 1,000,003 vs 67,741,504 trial divisions for all n ≤ N. |
| **Q6** | Rs 10,000 at 2 %/month, repay Rs 2,000 → 6 months, total interest Rs 645.38; hand calculation matches all 6 rows. Repayment ≤ Rs 200 is refused (never terminates); a 360-month limit stops near-miss cases. Closed formula agrees with the loop for every repayable case. |
| **Q7** | Chosen program: Q5 prime test. Redesign tests 2, 3, then only 6k±1. 1000003: 999 → 334 divisions (ratio 0.334); all n ≤ 1,000,003: 67,741,504 → 23,739,568 (65 % fewer); 0 answer mismatches. Slightly worse only for tiny primes 5 and 7. |

## Notes

* Output screenshots are terminal transcripts rendered by `tools/screenshot.py`, which compiles and runs the
  program in the task folder and draws the real `$ command` + output. You can re-take them in your own terminal.
* Commit progressively (one commit per task) – see `commit_progressively.sh`.
