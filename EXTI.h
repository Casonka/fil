    /*!
    *   --------------------------------------------------------------------------
    *                       ///EXTI initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Evgeny Garanin
    *   @date 18/07/2022 - last update version EXTI
    *
    *       @note [FIL:EXTI] Configuration file EXTI
    */
#include "FilConfig.h"

#if(FIL_EXTI == 1)

//----------------------------EXTI edges------------------------------------//
#define EXTI_RISING_EDGE    1
#define EXTI_FALLING_EDGE   2
#define EXTI_BOTH_EDGES     3
//----------------------------EXTI functions--------------------------------------------//
    /*!
    *   @brief AddEXTIInterrupt(PIN, EDGE) - Configuration pin for external interrupt
    *       @arg PIN - Number of pin
    *       @arg EDGE - Trigger edge for selected pin
    */
    #define AddEXTIInterrupt(PIN, EDGE)                                                {\
    SYSCFG->EXTICR [((PIN)&0xF) >> 0x02] |= (PIN>>4) << ((((PIN)&0xF) % 4) << 0x02);    \
     EXTI->IMR |= (1<<((PIN)&0xF));                                                     \
     switch (EDGE)                                                                      \
        {                                                                               \
            case EXTI_FALLING_EDGE:                                                     \
              {                                                                         \
                 EXTI->FTSR |= (1<<((PIN)&0xF));                                        \
                 EXTI->RTSR &= ~(1<<((PIN)&0xF));                                       \
            break;                                                                      \
              }                                                                         \
            case EXTI_RISING_EDGE:                                                      \
              {                                                                         \
                 EXTI->FTSR &= ~(1<<((PIN)&0xF));                                       \
                 EXTI->RTSR |= (1<<((PIN)&0xF));                                        \
                 break;                                                                 \
              }                                                                         \
            case EXTI_BOTH_EDGES:                                                       \
              {                                                                         \
                 EXTI->RTSR |= (1<<((PIN)&0xF));                                        \
                 EXTI->FTSR |= (1<<((PIN)&0xF));                                        \
                 break;                                                                 \
              }                                                                         \
        }                                                                               }

#endif /*FIL_EXTI*/
