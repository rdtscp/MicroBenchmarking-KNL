# KNL Results

## Instruction Cycles

LAT | O/Head | L? Load | DIV(29-42) | PAUSE(25) | F2XM1(100-400)
--- | --- | --- | --- | --- | ---
39 | 929(92.90%) | 0 | 0 | 0 | 0
52 | 71(7.10%) | 13(1.30%) | 0 | 199(19.90%) | 0
65 | 0 | 64(6.40%) | 144(14.40%) | 800(80.00%) | 0
78 | 0 | 72(7.20%) | 852(85.20%) | 1 | 0
91 | 0 | 803(80.30%) | 3 | 0 | 0
104 | 0 | 27(2.70%) | 0 | 0 | 0
351 | 0 | 0 | 0 | 0 | 26(2.60%)
364 | 0 | 0 | 0 | 0 | 70(7.00%)
377 | 0 | 0 | 0 | 0 | 629(62.90%)
390 | 0 | 0 | 0 | 0 | 201(20.10%)
429 | 0 | 0 | 0 | 0 | 32(3.20%)
442 | 0 | 0 | 0 | 0 | 26(2.60%)

## Timing Methods

### BenchIT Approach


Cycles | Occurrences
--- | ---
52 | 821183 (82.12%)
65 | 178608 (17.86%)


### Intel Whitepaper - Gabriele Paoloni on "How to Benchmark Code ExecutionTimes on Intel® IA-32 and IA-64 Instruction Set Architectures"
####	https://www.intel.com/content/dam/www/public/us/en/documents/white-papers/ia-32-ia-64-benchmark-code-execution-paper.pdf
Cycles | Occurrences
--- | ---
26 | 158056 (15.81%)
39 | 841747 (84.17%)