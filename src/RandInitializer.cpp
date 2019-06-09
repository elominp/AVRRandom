#include "AVRRandom.h"
#include <util/atomic.h>
#include <stdint.h>
#ifdef ARDUINO
#include <Arduino.h>
#endif /* ARDUINO */

extern "C" {
    volatile static unsigned long seed = 0;

    void initSeed(void) {
        uint8_t *ptr = (uint8_t *)(SP) - (((uint8_t *)(SP) - (uint8_t *)(__brkval)) / 2); // Start in the middle between the heap and the stack
        while (!(*ptr)) {
            ptr++; // Look for first non-zero byte
            if (ptr >= ((uint8_t *)(SP) - 2)) {
                return; // Means we went into the stack
            }
        }
        for (size_t i = 0; i < sizeof(unsigned long); i++) {
            seed <<= 8;
            seed |= *(ptr++);
        }
        ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
            srand(seed);
#ifdef ARDUINO
            randomSeed(seed);
#endif /* ARDUINO */
            for (size_t i = 0; i < sizeof(unsigned long); i++) {
                *(--ptr) = rand();
            }
        }
    }

    unsigned long getSeed(void) {
        return seed;
    }
}
