#ifndef STROBE_H
#define STROBE_H

#include <stdint.h>

void strobe(volatile uint32_t *port, uint32_t mask);

#endif
