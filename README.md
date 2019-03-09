# MicroBenchmarking-KNL

[![Codacy Badge](https://api.codacy.com/project/badge/Grade/0d3d01af7621410ca41da05a1635286b)](https://app.codacy.com/app/rdtscp/MicroBenchmarking-KNL?utm_source=github.com&utm_medium=referral&utm_content=rdtscp/MicroBenchmarking-KNL&utm_campaign=Badge_Grade_Dashboard)

This repository was used to track my Informatics Honours Project and Dissertation.
The project involves evaluating the Latencies of core memory components, and the bandwidths of the MCDRAM and DRAM.

[Background info on KNL](https://github.com/acwilson96/MicroBenchmarking-KNL/blob/master/Docs/Background.md)

## Repository Structure
```
/
├── Benchmarks
│   ├── Coherence Miss
│   ├── Latencies
│   ├── Memory Bandwidth
│   └── Tools
└── Docs
    ├── Dissertation
    ├── References
    └── Results
```
## /Benchmarks/
Contains source-code and associated files for building and executing the different microbenchmarks.

### /Benchmarks/Coherence Miss/
Contains source-code for multi-threaded benchmark which evaluates latencies of accessing data across Cores.
#### Usage
```
make
./run.sh State1Core ( M | E ) State2Core
./run.sh State1Core State2Core S State3Core
```
The following state diagrams show what each Task represents for the different modes:
##### Modified Access
![[0] - KNL Overview](https://github.com/acwilson96/MicroBenchmarking-KNL/blob/master/Docs/Dissertation/ModifiedState.png)

##### Exclusive Access
![[0] - KNL Overview](https://github.com/acwilson96/MicroBenchmarking-KNL/blob/master/Docs/Dissertation/ExclusiveState.png)

##### Shared Access
![[0] - KNL Overview](https://github.com/acwilson96/MicroBenchmarking-KNL/blob/master/Docs/Dissertation/SharedState.png)

### /Benchmarks/Latencies/
Contains source-code for microbenchmark for evaluating L1 Cache, L2 Cache, and DRAM/MCDRAM access Latencies.
#### Usage
```
make
./run.sh $numa_region
```
Where $numa_region is the numa-region you wish to run your benchmarks on. In Quadrant/All-to-All and Flat Mode, 0 is DRAM, and 1 MCRAM.

### /Benchmarks/Memory Bandwidth/
Contains source-code for STREAM Benchmark purposed for Knights Landing. STREAM Courtesy of John McCalpin @ https://www.cs.virginia.edu/stream/
#### Usage
```
./run.sh $numa_region
```
Where $numa_region is the numa-region you wish to run your benchmarks on. In Quadrant/All-to-All and Flat Mode, 0 is DRAM, and 1 MCRAM.

### /Benchmarks/Tools/
Contains small utility application for converting Cycles to NanoSeconds 

## /Docs/
Contains source-control files for the dissertation and results associated with the dissertation.
