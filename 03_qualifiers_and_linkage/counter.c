// counter.c
#include "counter.h"

static uint32_t count = 0;

void counter_increment(void)
{
    count++;
}

uint32_t counter_get(void)
{
    return count;
}