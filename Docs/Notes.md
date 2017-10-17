## Benchmarking Memory Latency Ideas
"Repeated pointer indirections"
i.e. A linked list without any content, just a pointer to the next cell.
```C++
struct cell { struct cell *next };

struct cell *ptr = ...;
for (i = 0; i < count; i++) {
    ptr = ptr->next;
    ptr = ptr->next;
    // ... 100 of these, unrolled ...
    ptr = ptr->next;
    ptr = ptr->next;
}
```
[source](https://stackoverflow.com/questions/13603995/measuring-latencies-of-memory)