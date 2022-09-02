    /*!
    *   --------------------------------------------------------------------------
    *                       ///RCC initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 13/07/2022 - last update version RCC
    *
    *       @note [FIL:RCC] Configuration file RCC
    */
#pragma once
#include "FilConfig.h"
#if (FIL_RCC == 1)
    /*!
    *   @list Dma
    */
    #define SetDMA1         (RCC->AHB1ENR |= ((uint32_t)(1 << 21)))
    #define SetDMA2         (RCC->AHB1ENR |= ((uint32_t)(1 << 22)))
    /*!
    *   @list GPIO
    */
    #define SetGPIOA        (RCC->AHB1ENR |= ((uint32_t)(1)))
    #define SetGPIOB        (RCC->AHB1ENR |= ((uint32_t)(1 << 1)))
    #define SetGPIOC        (RCC->AHB1ENR |= ((uint32_t)(1 << 2)))
    #define SetGPIOD        (RCC->AHB1ENR |= ((uint32_t)(1 << 3)))
    #define SetGPIOE        (RCC->AHB1ENR |= ((uint32_t)(1 << 4)))
    #define SetGPIOH        (RCC->AHB1ENR |= ((uint32_t)(1 << 7)))

    #define ResetGPIOB      (RCC->AHB1RSTR |= (1 << 1))
#if defined(STM32F40_41xxx) /*--------------STM32F407------------------*/
    #define SetGPIOF        (RCC->AHB1ENR |= ((uint32_t)(1 << 5)))
    #define SetGPIOG        (RCC->AHB1ENR |= ((uint32_t)(1 << 6)))
    #define SetGPIOI        (RCC->AHB1ENR |= ((uint32_t)(1 << 8)))
#endif
    /*!
    *   @list TIM
    */
    #define SetTIM1         (RCC->APB2ENR |= ((uint32_t)(1)))
    #define SetTIM2         (RCC->APB1ENR |= ((uint32_t)(1)))
    #define SetTIM3         (RCC->APB1ENR |= ((uint32_t)(1 << 1)))
    #define SetTIM4         (RCC->APB1ENR |= ((uint32_t)(1 << 2)))
    #define SetTIM5         (RCC->APB1ENR |= ((uint32_t)(1 << 3)))
    #define SetTIM9         (RCC->APB2ENR |= ((uint32_t)(1 << 16)))
    #define SetTIM10        (RCC->APB2ENR |= ((uint32_t)(1 << 17)))
    #define SetTIM11        (RCC->APB2ENR |= ((uint32_t)(1 << 18)))

#if defined(STM32F40_41xxx) /*--------------STM32F407------------------*/
    #define SetTIM6         (RCC->APB1ENR |= ((uint32_t)(1 << 4)))
    #define SetTIM7         (RCC->APB1ENR |= ((uint32_t)(1 << 5)))
    #define SetTIM8         (RCC->APB2ENR |= ((uint32_t)(1 << 4)))
    #define SetTIM12        (RCC->APB1ENR |= ((uint32_t)(1 << 6)))
    #define SetTIM13        (RCC->APB1ENR |= ((uint32_t)(1 << 7)))
    #define SetTIM14        (RCC->APB1ENR |= ((uint32_t)(1 << 8)))
#endif
    /*!
    *   @list UART/USART
    */
    #define SetUSART1       (RCC->APB2ENR |= ((uint32_t)(1 << 4)))
    #define SetUSART6       (RCC->APB2ENR |= ((uint32_t)(1 << 5)))
    #define SetUSART2       (RCC->APB1ENR |= ((uint32_t)(1 << 17)))

#if defined(STM32F40_41xxx) /*--------------STM32F407------------------*/
    #define SetUSART3       (RCC->APB1ENR |= ((uint32_t)(1 << 18)))
    #define SetUSART4       (RCC->APB1ENR |= ((uint32_t)(1 << 19)))
    #define SetUSART5       (RCC->APB1ENR |= ((uint32_t)(1 << 20)))
#endif
    /*!
    *   @list I2C
    */
    #define SetI2C1         (RCC->APB1ENR |= ((uint32_t)(1 << 21)))
    #define SetI2C2         (RCC->APB1ENR |= ((uint32_t)(1 << 22)))
    #define SetI2C3         (RCC->APB1ENR |= ((uint32_t)(1 << 23)))

    #define ResetI2C1       (RCC->APB1RSTR |= ((uint32_t)(1 << 21)))
    #define ResetI2C2       (RCC->APB1RSTR |= ((uint32_t)(1 << 22)))
    #define ResetI2C3       (RCC->APB1RSTR |= ((uint32_t)(1 << 23)))
    /*!
    *   @list ADC
    */
    #define SetADC1         (RCC->APB2ENR |= ((uint32_t)(1 << 8)))
#if defined(STM32F40_41xxx) /*--------------STM32F407------------------*/
    #define SetADC2         (RCC->APB2ENR |= ((uint32_t)(1 << 9)))
    #define SetADC3         (RCC->APB2ENR |= ((uint32_t)(1 << 10)))
#endif

#if defined(STM32F40_41xxx) /*--------------STM32F407------------------*/
    /*!
    *   @list DAC
    */
    #define SetDAC          (RCC->APB1ENR |= ((uint32_t)(1 << 29)))
    /*!
    *   @list CAN
    */
    #define SetCAN1         (RCC->APB1ENR |= ((uint32_t)(1 << 25)))
    #define SetCAN2         (RCC->APB1ENR |= ((uint32_t)(1 << 26)))
#endif
    /*!
    *   @list PWR
    */
    #define SetPWR          (RCC->APB1ENR |= ((uint32_t)(1 << 28)))
    /*!
    *   @list SPI
    */
    #define SetSPI2         (RCC->APB1ENR |= ((uint32_t)(1 << 14)))
    #define SetSPI3         (RCC->APB1ENR |= ((uint32_t)(1 << 15)))
    #define SetSPI1         (RCC->APB2ENR |= ((uint32_t)(1 << 12)))
    /*!
    *   @list SDIO
    */
    #define SetSDIO         (RCC->APB2ENR |= ((uint32_t)(1 << 11)))
    /*!
    *   @list SYSCFG
    */
    #define SetSYSCFG       (RCC->APB2ENR |= ((uint32_t)(1 << 14)))

    /*!
    *   @note [FIL:RCC] Prepare for RTC
    */
    #define LSE             (RCC_CFGR_MCO1_0 | RCC_CFGR_RTCPRE_3)

    #ifdef __configMAP_MK1
    #define FIL_MKSOURSE1   __configMAP_MK1
    #else
    #define FIL_MKSOURSE1   LSE
    #endif /*__configMAP_MK1*/

    #define RCC_MKOutput1   (RCC->CFGR |= FIL_MKSOURSE1)
    #define RCC_RTCClockON  (RCC->BDCR |= (RCC_BDCR_RTCEN | RCC_BDCR_RTCSEL_0))
    #define LSE_ON          (RCC->BDCR |= RCC_BDCR_LSEON)

    #define PWRUnlockWriteProtection        (PWR->CR |= PWR_CR_DBP)
    #define PWRLockWriteProtection          (PWR->CR &= ~PWR_CR_DBP)

#if (FIL_CALC_RCC == 1)
    /*!
     *   @brief Get{name} - get clock part of the peripheral
     *
     *       @arg name - the part name of the peripheral
     */
    #define GetSWS     ((uint32_t)((RCC->CFGR & RCC_CFGR_SWS) >> 2))
    #define GetPLLSRC  ((uint32_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLSRC) >> 22))
    #define GetPLLM    ((uint32_t)(RCC->PLLCFGR & RCC_PLLCFGR_PLLM))
    #define GetPLLN    ((uint32_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLN) >> 6))
    #define GetPLLP    ((uint32_t)((RCC->PLLCFGR & RCC_PLLCFGR_PLLP) >> 16))
    #define GetHPRE    ((uint32_t)((RCC->CFGR & RCC_CFGR_HPRE) >> 4))
    #define GetPPRE1   ((uint32_t)((RCC->CFGR & RCC_CFGR_PPRE1) >> 10))
    #define GetPPRE2   ((uint32_t)((RCC->CFGR & RCC_CFGR_PPRE2) >> 13))

    __attribute__((unused)) static uint8_t PrescalerTable[16] =   {0, 0, 0, 0, 1, 2, 3, 4, 1, 2, 3, 4, 6, 7, 8, 9};
    /*!
     *   @brief CurrentSYSTICK - get system clock frequency
     *
     *   @brief CurrentAHB - get AHB bus frequency
     *
     *   @brief CurrentAPB1 - get APB1 bus frequency
     *
     *   @brief CurrentAPB2 - get APB2 bus frequency
     */
    struct
    {
        uint32_t PLLVCO;
        uint32_t CurrentSYSTICK;
        uint32_t CurrentAHB;
        uint32_t CurrentAPB1;
        uint32_t CurrentAPB2;
    }Clocks;

    void CalcRCCClocks(void);
#endif /*FIL_CALC_RCC*/
#endif /*FIL_RCC*/
