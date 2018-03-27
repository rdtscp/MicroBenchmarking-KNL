
# [Presentation](http://slides.com/acwilson96/microbenchmarking-intel-xeon-knights-landing/fullscreen)

# Background Info on Intel Knights Landing.

## Architecture Overview
![[0] - KNL Overview](https://github.com/acwilson96/MicroBenchmarking-KNL/blob/master/Docs/KNL_Overview.png "[0] - KNL Overview")

_Figure 1: Pictorial overview of a KNL Chip_

## Tile
A single __Tile__ has:
* __2 x CPU Cores:__
  * 32KB L1 Instruction Cache
  * 32KB L1 Data Cache
  * 64B Cache Line
* __1 x L2 Cache:__
  * __1MB__ __=>__ _Configurable as_ __Private 512KB/Core__ _or_ __Shared 1MB__
  * __16-Way__ __=>-__ _i.e. 1MB split into_ __16 x 64B blocks/sets.__
  * 1 Line Read and ½ Line Write per cycle. _=> i.e. Takes 2 cycles to write a line, and 1 cycle to read a line._
  * __Coherent__ across all Tiles
  * Connected by _2D Mesh_

* __1 x Caching/Home Agent__ - Distributed Tag Directory to keep L2 Cache Coherent - MESIF Protocol
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
###### Sources
Figure 1 - Avinash Sodani CGO PPoPP HPCA Keynote 2016

---
###### Reading
* [ARCHER Overview](http://www.archer.ac.uk/training/course-material/2016/11/161101_KNL_EPCC/Slides/L01-IntroductionToKNL.pdf)
* [Memory Modes Overview](https://www.alcf.anl.gov/files/HC27.25.710-Knights-Landing-Sodani-Intel.pdf)
