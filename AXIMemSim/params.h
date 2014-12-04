#ifndef PARAMS_H
#define PARAMS_H

#include <types.h>


#define CLOCK_CYCLE             sc_time(10, SC_NS)

#define MEMORY_SIZE_WORDS       (256*1024*1024)/sizeof(MemWord)
#define MEMORY_MAX_REQS         32
#define MEMORY_LATENCY          (10*CLOCK_CYCLE)

#endif // PARAMS_H
