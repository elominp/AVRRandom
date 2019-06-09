#ifndef AVRRANDOM_H
#define AVRRANDOM_H

#include <stdlib.h>

extern int *__brkval;
#ifdef AUTO_SEED_AVRRANDOM
void initSeed(void) __attribute__((naked)) __attribute__((section(".init3")));
#endif /* AUTO_SEED_AVRRANDOM */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */
void initSeed(void);
unsigned long getSeed(void);
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* AVRRANDOM_H */
