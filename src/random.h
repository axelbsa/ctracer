#ifndef RANDOM_H
#define RANDOM_H

#include <stdlib.h>
#include <time.h>


double random_double() {
    //return (double)rand() / (double)((unsigned)RAND_MAX + 1.0);
    return rand() / (RAND_MAX + 1.0);
}

#endif
