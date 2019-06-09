#ifndef DISABLE_CRC_SEED
# include <util/crc16.h>
#endif /* DISABLE_CRC_SEED */
#include <util/atomic.h>
#include <stdint.h>

volatile static uint16_t seed = 0;

extern int *__brkval;
//void _init_seed(void) __attribute__((naked)) __attribute__((section(".init3")));
void _init_seed(void) {
    uint8_t *ptr = (uint8_t *)(SP) - (((uint8_t *)(SP) - (uint8_t *)(__brkval)) / 2); // Start in the middle between the heap and the stack
    while (!(*ptr)) {
        ptr++; // Look for first non-zero byte
        if (ptr >= ((uint8_t *)(SP) - 2)) {
            return; // Means we went into the stack
        }
    }
    seed |= *(ptr++); // Take the first SRAM byte
    seed <<= 8;
    seed |= *ptr; // Take the second SRAM byte
#ifndef DISABLE_CRC_SEED
    uint16_t crc;
    crc = _crc16_update(crc, seed >> 8);
    crc = _crc16_update(crc, seed);
    seed = crc;
#endif /* DISABLE_CRC_SEED */
    ATOMIC_BLOCK(ATOMIC_RESTORESTATE) {
        srand(seed);
        *(ptr--) = rand();
        *ptr = rand();
    }
}