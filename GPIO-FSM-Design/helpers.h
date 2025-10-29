#ifndef __HELPERS_H__
#define __HELPERS_H__

#include <stdint.h>

#define BIT(n) (1U << (n))

// Port identifiers (used as labels only, not memory addresses)
#define J 'J'
#define F 'F'
#define N 'N'

// Generic GPIO register access macros (return lvalues)
#define GPIODIR(port) \
    (*((volatile uint32_t *)((port) == J ? 0x40060400 : (port) == F ? 0x4005D400 : 0x40064400)))

#define GPIODEN(port) \
    (*((volatile uint32_t *)((port) == J ? 0x4006051C : (port) == F ? 0x4005D51C : 0x4006451C)))

#define GPIOPUR(port) \
    (*((volatile uint32_t *)((port) == J ? 0x40060510 : 0)))  // Only for Port J

// Still okay to use value-returning macro for data
#define GPIODATA(port, offset) \
    (*((volatile uint32_t *)((port) == J ? 0x400603FC : \
                             (port) == F ? 0x4005D3FC : \
                                           0x400643FC)))


// Optional macro to help with masked access (alternative to `GPIODATA`)
#define GPIODATA_ADDR_MASKED(base_addr, mask) \
    ((volatile uint32_t *)((uintptr_t)(base_addr) + ((mask) << 2)))

#endif // __HELPERS_H__
