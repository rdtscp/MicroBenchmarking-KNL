# Background Info on Intel Knights Landing.

## Architecture Overview
![[0] - KNL Overview](https://github.com/acwilson96/MicroBenchmarking-KNL/blob/master/KNL_Overview.png "[0] - KNL Overview")

_Figure 1: Pictorial overview of a KNL Chip_

## Tile
A single __Tile__ has:
* __2 x CPU Cores:__
  * 32KB L1 Instruction Cache
  * 32KB L1 Data Cache
  * 512B/64B Cache Line
* __1 x L2 Cache:__
  * __1MB__ __=>__ _Configurable as_ __Private 512KB/Core__ _or_ __Shared 1MB__
  * __16-Way__ __=>-__ _i.e. 1MB split into_ __16 x 64B blocks/sets.__
  * 1 Line Read and ½ Line Write per cycle. _=> i.e. Takes 2 cycles to write a line, and 1 cycle to read a line._
  * __Coherent__ across all Tiles
  * Connected by _2D Mesh_

* __1 x Caching/Home Agent__ - Distributed Tag Directory to keep L2 Cache Coherent
* 2 VPU Cores

## L2 Cache Mesh

* Addressed on a Y,X basis:
  * Go in Y
  * Turn
  * Go in X

3 Modes:
  * __All-to-All__:
    * All L2 Address space uniformly distributed across all distributed directories (i.e. Caches)
    * General mode, relatively lower performance
    * No affinity between tile, directory and memory
    * Typical Read Miss:
      * Miss in Tile L2 Cache
      * Send request to distributed directory
      * Miss in the directory, forward to DRAM
  * __Quadrant__:
    * Chip divided into four virtual quadrants
    * Addresses hashed to a directory in the same quadrant
    * Lower latency and higher bandwidth than __All-to-All_
    * Affinity between directory and memory
    * Typical Read Miss:
      * Miss in Quadrant L2 Cache
      * Send request to quadrant directory
      * Miss in the directory, forward to DRAM
  * __Sub-NUMA Clustering__:
    * Four quadrants exposed as a seperate NUMA domain to OS => Looks analogous to 4 socket Xeon.
    * Lowest latency, local communication
    * Affinity between tile, directory and memory
    * Typical Read Miss:
      * Miss in Quadrant L2 Cachce
      * Send request to quadrant directory
      * Miss in the directory, forward to DRAM

## MCDRAM

* __High Bandwidth Memory__
* __16GB__
* __Higher Latency__ relative to main memory.
* 3 Configurable Modes:
  * __Cache Mode__:
    * Acts as a "cache" for main memory
    * Only MCDRAM Addressable
    * Misses expensive as you must access DRAM and MCDRAM
    * Done in hardware => No software changes required
  * __Flat Mode__:
    * Acts as an "extension" for main memory
    * Same address space
    * Must be managed in software
  * __Hybrid Mode__:
    * Part Cache, Part Memory
    * 25% or 50% Cache

---

# Objectives

## What to Benchmark

I am interested in measuring the bandwith and latency of data transfer between caches and memory in different configurations. Also the cost of a cache misses in the different configurations of the L2 Cache, and MCDRAM.

## Project Plan

A week by week layout of my plan (i.e. by the end of week n).
Semester 1:
  1. _(23<sup>rd</sup> Sep)_ - Meet with Supervisor and find out how to start.
  2. _(30<sup>th</sup> Sep)_ - Read into the KNL architecture, get an account with ARCHER, and a profile with ARCHER's KNL node.
  3. _(06<sup>th</sup> Oct)_ - Finish reading into KNL architecture, come up with objectives on what to study in this project.
  4. _(13<sup>th</sup> Oct)_ - Understand how to __compile for KNL on ARCHER__, try to write some basic tests to verify my understanding.
  5. _(20<sup>th</sup> Oct)_ - Have an understanding of how to __program for KNL__, and read into detail/__start writing benchmarking applications.__
  6. _(27<sup>th</sup> Oct)_ - Work on benchmarking the 3 cache modes: __All-to-All, Quadrant, and Sub-NUMA Clustering__ for the next 4 weeks.
  7. _(03<sup>rd</sup> Nov)_ - Work on benchmarking the 3 cache modes: __All-to-All, Quadrant, and Sub-NUMA Clustering__.
  8. _(10<sup>th</sup> Nov)_ - Work on benchmarking the 3 cache modes: __All-to-All, Quadrant, and Sub-NUMA Clustering__.
  9. _(17<sup>th</sup> Nov)_ - Finish up benchmarking __All-to-All, Quadrant, and Sub-NUMA Clustering__.
  10. _(24<sup>th</sup> Nov)_ - Work on benchmarking the 3 MCDRAM modes: __Cache Mode, Flat Mode, and Hybrid Mode__ for the next 3 to 4 weeks.
  11. _(01<sup>st</sup> Dec)_ - Work on benchmarking the 3 MCDRAM modes: __Cache Mode, Flat Mode, and Hybrid Mode__.
  12. _(08<sup>th</sup> Dec)_ - Work on benchmarking the 3 MCDRAM modes: __Cache Mode, Flat Mode, and Hybrid Mode__.
  13. _(15<sup>th</sup> Dec)_ - Finish work on benchmarking the 3 MCDRAM modes.
  14. _(21<sup>st</sup> Dec)_ - __Headroom__ for first semester work.
  
* __Winter Holidays__ - Work more on either formalising results, or complete unfinished work.

Semester 2 _(TBC)_:
  1. _(19<sup>th</sup> Jan)_ - Meet with Supervisor to discuss progress, and report.
  2. _(26<sup>th</sup> Jan)_ - __Headroom__ for further work.
  3. _(02<sup>th</sup> Feb)_ - __Headroom__ for further work.
  4. _(09<sup>th</sup> Feb)_ - Work on __report__.
  5. _(16<sup>th</sup> Feb)_ - Work on __report__.
  6. _(23<sup>rd</sup> Feb)_ - Work on __report__.
  7. _(02<sup>nd</sup> Mar)_ - Work on __report__.
  6. _(07<sup>th</sup> Mar)_ - Finish work on __report__, __Headroom__ for both semesters.
  6. _(14<sup>th</sup> Mar)_ - __Headroom__ for both semesters.
  6. _(21<sup>st</sup> Mar)_ - __Headroom__ for both semesters.
  6. _(28<sup>th</sup> Mar)_ - __Headroom__ for both semesters.
  


---
###### Sources
Figure 1 - Avinash Sodani CGO PPoPP HPCA Keynote 2016

---
###### Reading
* [ARCHER Overview](http://www.archer.ac.uk/training/course-material/2016/11/161101_KNL_EPCC/Slides/L01-IntroductionToKNL.pdf)
* [Memory Modes Overview](https://www.alcf.anl.gov/files/HC27.25.710-Knights-Landing-Sodani-Intel.pdf)
