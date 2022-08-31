    /*!
    *   --------------------------------------------------------------------------
    *                       ///TIM initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska, Evgeny Garanin
    *   @date 13/07/2022 - last update version TIM
    *
    *       @note [FIL:TIM] Configuration file TIM
    */
#pragma once
#include "FilConfig.h"

#if (FIL_TIM == 1)
    /*!
    *   @brief TimPWMConfigure(TIM,prescaler,autoreset,ch1,ch2,ch3,ch4) - configuration timer in PWM mode
    *       @arg TIM - number of timer
    *       @arg prescaler - value for increase the input frequency
    *       @arg autoreset - value for set the period of timer
    *       @arg ch<n> - activate/deactivate the channels of timer
    */
    #define TimPWMConfigure(TIM,PSC,ARR,ch1,ch2,ch3,ch4)       {\
        ConfChannelsTim(TIM,6,6,ch1,ch2,ch3,ch4);               \
        ConfTimPSC(TIM,PSC);                                    \
        ConfTimARR(TIM,ARR);                                    \
        TimStart(TIM);                                          \
        SetTimMainOutput(TIM);                                  \
        ResetTimCCR1(TIM);                                      \
        ResetTimCCR2(TIM);                                      }

    /*!
    *   @brief TimPIDConfigure(TIM, PSC, ARR) - configuration timer in calculating mode
    *   (P-regulation, PI - regulation, PID - regulation and other regulations)
    *       @arg TIM - number of timer
    *       @arg PSC - Prescaler value timer
    *       @arg ARR - Autoreset value timer
    */
    #define TimPIDConfigure(TIM,PSC,ARR)               {\
        ResetTimCNT(TIM);                               \
        ConfTimPSC(TIM,PSC);                            \
        ConfTimARR(TIM,ARR);                            \
        SetTimUpdateInterrupt(TIM);                     \
        TimStart(TIM);                                  }
#if (FIL_CALC_TIM == 1)

    /*!
    *   @brief TimPWMConfigureAutomatic(TIM,FREQUENCY,ch1,ch2,ch3,ch4) - configuration timer in PWM mode (auto-mode)
    *       @arg TIM - number of timer
    *       @arg FREQUENCY - target frequency
    *       @arg ch<n> - activate/deactivate the channels of timer
    */
    #define TimPWMConfigureAutomatic(TIM,FREQUENCY,ch1,ch2,ch3,ch4)  {\
        ConfChannelsTim(TIM,6,6,ch1,ch2,ch3,ch4);                     \
        CalcTimFrequency(TIM,FREQUENCY);                              \
        TimStart(TIM);                                                \
        SetTimMainOutput(TIM);                                        \
        ResetTimCCR1(TIM);                                            \
        ResetTimCCR2(TIM);                                            }

    /*!
    *   @brief TimPIDConfigureAutomatic(TIM,frequency) - configuration timer in calculating mode (auto-mode)
    *   (P-regulation, PI - regulation, PID - regulation and other regulations)
    *       @arg TIM - number of timer
    *       @arg FREQUENCY - target frequency for calculating
    */
    #define TimPIDConfigureAutomatic(TIM,FREQUENCY)    {\
        ResetTimCNT(TIM);                               \
        CalcTimFrequency(TIM,FREQUENCY);                \
        SetTimUpdateInterrupt(TIM);                     \
        TimStart(TIM);                                  }
#endif
    /*!
    *   @brief TimEncoderConfigure(TIM) - configuration timer with encoder interface
    *       @arg TIM - number of timer
    */
    #define TimEncoderConfigure(TIM)    {\
        ResetTimPSC(TIM);                \
        ConfTimARR(TIM,0xFFFFFFFF);      \
        TimStart(TIM);                   \
        ConfTimSMS(TIM,0x3);             \
        ConfTimEtf(TIM,0xF);             }

    /*!
    *   @brief TimPWMInputCaptureConfigure(TIM) - configuration timer for check length of PWM
    *       @arg TIM - number of timer
    */
    #define TimPWMInputCaptureConfigure(TIM,PSC,ARR)                 {\
        ConfTimPSC(TIM,PSC);                                          \
        ConfTimARR(TIM,ARR);                                          \
        ConfTimCaptureSelection1(TIM,0x1,0x2,1);                      \
        ConfTimCaptureSelection2(TIM,0x1,0x2,1);                      \
        ConfTimCapturePolarity(TIM,0x0,0x0,0x0,0x0,1,1);              \
        ConfTimCaptureComplementaryPolarity(TIM,0x0,0x0,0x0,0x0,1,1); \
        ConfTimTriggerSelection(TIM,0x5);                             \
        ConfTimSMS(TIM,0x4);                                          \
        ConfTimCapture(TIM,0x1,0x1,0x1,0x1,1,1,1,1);                  \
        TimStart(TIM);                                                }

    /*!
    *   @brief TimPWMCentralAlignedModeConfigure(TIM,prescaler,autoreset,ch1,ch2,polarity1,ch3,ch4,polarity2) - configuration timer with central aligned mode
    *       @arg TIM - number of timer
    *       @arg prescaler - value for increase the input frequency
    *       @arg autoreset - value for set the period of timer
    *       @arg polarity<n> - set polarity level for PWM output
    *       @arg ch<n> - activate/deactivate the channels of timer
    */
    #define TimPWMCentralAlignedModeConfigure(TIM,PRESCALER,AUTORESET,ch1,ch2,polarity1,ch3,ch4,polarity2) {\
        ConfChannelsTim(TIM,polarity1,polarity2,ch1,ch2,ch3,ch4);                                          \
        ConfTimPSC(TIM,PRESCALER);                                                                         \
        ConfTimARR(TIM,AUTORESET);                                                                         \
        TimStart(TIM);                                                                                     \
        ResetTimCCR1(TIM);                                                                                 \
        ResetTimCCR2(TIM);                                                                                 }

//----------------------------High commands------------------------------------//

    #define ConfChannelsTim(TIM,mode1,mode2,ch1,ch2,ch3,ch4)             {\
        ConfTimOutputCompare1(TIM,mode1,mode2,ch1,ch2);                   \
        ConfTimOutputCompare2(TIM,mode1,mode2,ch3,ch4);                   \
        ConfTimCompareFast1(TIM,1,1,ch1,ch2);                             \
        ConfTimCompareFast2(TIM,1,1,ch3,ch4);                             \
        ConfTimCapture(TIM,1,1,1,1,ch1,ch2,ch3,ch4);                      }

//-----------------------Simple commands reset and set the state-------------------------------------------------------------------------------------------------------------//
    #define ConfTimPSC(TIM,PRESCALER)                               { TIM->PSC = ((uint32_t)(TIM->PSC & ((uint32_t)(~0xFFFFFFFF))) | ((uint32_t)PRESCALER));}

    #define ConfTimARR(TIM,AUTORESET)                               { TIM->ARR = ((uint32_t)(TIM->ARR & ((uint32_t)(~0x00000000))) & ((uint32_t)AUTORESET));}

    #define TimOutputCompare1(OC1M,OC2M,CH1,CH2)                    ((uint16_t)((((OC2M) << 12)*CH2) | (((OC1M) << 4)*CH1)))
    #define ConfTimOutputCompare1(TIM,OC1M,OC2M,CH1,CH2)            { TIM->CCMR1 = ((uint32_t)(TIM->CCMR1 & (~TimOutputCompare1(7,7,1,1))) | TimOutputCompare1(OC1M,OC2M,CH1,CH2));}

    #define TimOutputCompare2(OC3M,OC4M,CH3,CH4)                    ((uint16_t)((((OC4M) << 12)*CH4) | (((OC3M) << 4)*CH3)))
    #define ConfTimOutputCompare2(TIM,OC3M,OC4M,CH3,CH4)            { TIM->CCMR2 = ((uint32_t)(TIM->CCMR2 & (~TimOutputCompare2(7,7,1,1))) | TimOutputCompare2(OC3M,OC4M,CH3,CH4));}

    #define TimOutputCompareFast1(OC1FE,OC2FE,CH1,CH2)              ((uint16_t)((((OC2FE) << 10)*CH2) | (((OC1FE) << 2)*CH1)))
    #define ConfTimCompareFast1(TIM,OC1FE,OC2FE,CH1,CH2)            { TIM->CCMR1 = ((uint32_t)(TIM->CCMR1 & (~TimOutputCompareFast1(1,1,1,1))) | TimOutputCompareFast1(OC1FE,OC2FE,CH1,CH2));}

    #define TimOutputCompareFast2(OC3FE,OC4FE,CH3,CH4)              ((uint16_t)((((OC4FE) << 10)*CH4) | (((OC3FE) << 2)*CH3)))
    #define ConfTimCompareFast2(TIM,OC3FE,OC4FE,CH3,CH4)            { TIM->CCMR2 = ((uint32_t)(TIM->CCMR2 & (~TimOutputCompareFast2(1,1,1,1))) | TimOutputCompareFast2(OC3FE,OC4FE,CH3,CH4));}

    #define TimCapture(CC1E,CC2E,CC3E,CC4E,CH1,CH2,CH3,CH4)         ((uint16_t)((((CC4E) << 12)*CH4) | (((CC3E) << 8)*CH3)| (((CC2E) << 4)*CH2) | ((CC1E)*CH1)))
    #define ConfTimCapture(TIM,CC1E,CC2E,CC3E,CC4E,CH1,CH2,CH3,CH4) { TIM->CCER = ((uint32_t)(TIM->CCER & (~TimCapture(1,1,1,1,1,1,1,1))) | TimCapture(CC1E,CC2E,CC3E,CC4E,CH1,CH2,CH3,CH4));}

    #define ConfTimCCR1(TIM,CCR)         {TIM->CCR1 = ((uint32_t)((TIM->CCR1) & (~0xFFFFFFFF)) | ((uint32_t)(CCR)));}

    #define ConfTimCCR2(TIM,CCR)         {TIM->CCR2 = ((uint32_t)((TIM->CCR2) & (~0xFFFFFFFF)) | ((uint32_t)(CCR)));}

    #define ConfTimCCR3(TIM,CCR)         {TIM->CCR3 = ((uint32_t)((TIM->CCR3) & (~0xFFFFFFFF)) | ((uint32_t)(CCR)));}

    #define ConfTimCCR4(TIM,CCR)         {TIM->CCR4 = ((uint32_t)((TIM->CCR4) & (~0xFFFFFFFF)) | ((uint32_t)(CCR)));}

    #define ConfTimSMS(TIM,SMS)          {TIM->SMCR = ((uint32_t)((TIM->SMCR) & (~0x7)) | ((uint32_t)(SMS)));}

    #define TimETF(ETF)                  ((uint16_t)((ETF) << 8))
    #define ConfTimEtf(TIM,ETF)          {TIM->SMCR = ((uint32_t)((TIM->SMCR) & (~TimETF(0xF))) | TimETF(ETF));}

    #define TimCaptureSelection1(CC1S,CC2S,CH1)          ((uint16_t)((((CC2S) << 8)*CH1) | ((CC1S)*CH1)))
    #define ConfTimCaptureSelection1(TIM,CC1S,CC2S,CH1)   {TIM->CCER = ((uint32_t)((TIM->CCER) & (~TimCaptureSelection1(1,1,1))) | TimCaptureSelection1(CC1S,CC2S,CH1));}

    #define TimCaptureSelection2(CC3S,CC4S,CH2)          ((uint16_t)((((CC4S) << 8)*CH2) | ((CC3S)*CH2)))
    #define ConfTimCaptureSelection2(TIM,CC3S,CC4S,CH2)  {TIM->CCER = ((uint32_t)((TIM->CCER) & (~TimCaptureSelection2(1,1,1))) | TimCaptureSelection1(CC3S,CC4S,CH2));}

    #define TimCapturePolarity(CC1P,CC2P,CC3P,CC4P,CH1,CH2)          ((uint16_t)((((CC4P) << 13)*CH2) | (((CC3P) << 9)*CH2)| (((CC2P) << 5)*CH1) | (((CC1P) << 1)*CH1)))
    #define ConfTimCapturePolarity(TIM,CC1P,CC2P,CC3P,CC4P,CH1,CH2)  {TIM->CCER = ((uint32_t)((TIM->CCER) & (~TimCapturePolarity(1,1,1,1,1,1))) | TimCapturePolarity(CC1P,CC2P,CC3P,CC4P,CH1,CH2));}

    #define TimCaptureComplementaryPolarity(CC1NP,CC2NP,CC3NP,CC4NP,CH1,CH2) ((uint16_t)((((CC4NP) << 15)*CH2) | (((CC3NP) << 11)*CH2)| (((CC2NP) << 7)*CH1) | (((CC1NP) << 3)*CH1)))
    #define ConfTimCaptureComplementaryPolarity(TIM,CC1NP,CC2NP,CC3NP,CC4NP,CH1,CH2)    {TIM->CCER = ((uint32_t)((TIM->CCER) & (~TimCaptureComplementaryPolarity(1,1,1,1,1,1))) | TimCapturePolarity(CC1NP,CC2NP,CC3NP,CC4NP,CH1,CH2));}

    #define TimTriggerSelection(TS)          ((uint16_t)((TS) << 4))
    #define ConfTimTriggerSelection(TIM,TS)  {TIM->SMCR = ((uint32_t)((TIM->SMCR) & (~TimTriggerSelection(0x7))) | TimTriggerSelection(TS));}
//---------------------------------------Reset state---------------------------------------------------//
    #define TimStop(TIM)            ( TIM->CR1  &=   ((uint32_t)(~0x1)))
    #define ResetTimCNT(TIM)        ( TIM->CNT  =    ((uint32_t)(0x0)) )
    #define ResetTimPSC(TIM)        ( TIM->PSC  =    ((uint32_t)(0x0)) )
    #define ResetTimARR(TIM)        ( TIM->ARR  =    ((uint32_t)(~0x00000000)) )
    #define ResetTimCCR1(TIM)       ( TIM->CCR1 =    ((uint32_t)(0x0)) )
    #define ResetTimCCR2(TIM)       ( TIM->CCR2 =    ((uint32_t)(0x0)) )
    #define ResetTimCCR3(TIM)       ( TIM->CCR3 =    ((uint32_t)(0x0)) )
    #define ResetTimCCR4(TIM)       ( TIM->CCR4 =    ((uint32_t)(0x0)) )
    #define ResetTimSR(TIM)         ( TIM->SR   =    ((uint32_t)(0x0)) )
//----------------------------------------Get state----------------------------------------------------//
    #define GetTimCNT(TIM) ((uint32_t)(TIM->CNT))
    #define GetTimARR(TIM) ((uint32_t)(TIM->ARR))
    #define GetTimSR(TIM)  ((uint32_t)(TIM->SR))
//----------------------------------------Set state----------------------------------------------------//
    #define TimStart(TIM)                                   ( TIM->CR1 |= 1)
    #define SetTimUpdateDisable(TIM)                        ( TIM->CR1 |= ((uint32_t)(1 << 1)))
    #define SetTimUpdateRequest(TIM)                        ( TIM->CR1 |= ((uint32_t)(1 << 2)))
    #define SetTimOnePulseMode(TIM)                         ( TIM->CR1 |= ((uint32_t)(1 << 3)))
    #define SetTimDirection(TIM)                            ( TIM->CR1 |= ((uint32_t)(1 << 4)))
    #define SetTimPreloadARR(TIM,ARPE)                      ( TIM->CR1 |= ((uint32_t)(1 << 7)))
    #define SetTimPSC(TIM,PSC)                              ( TIM->PSC |= ((uint32_t)(PSC)))
    #define SetTimARR(TIM,ARR)                              ( TIM->PSC &= ((uint32_t)(ARR)))
    #define SetTimUpdateInterrupt(TIM)                      ( TIM->DIER |= 1)
    #define SetTimMainOutput(TIM)                           ( TIM->BDTR |= ((uint32_t)(1 << 15)))
    #define SetTimAutomaticOutput(TIM)                      ( TIM->BDTR |= ((uint32_t)(1 << 14)))
    #define SetTimUpdateGeneration(TIM)                     ( TIM->EGR |= 1)
#if (FIL_CALC_TIM == 1)
//---------------------------------------Calculating---------------------------------------------------//
struct {
    char Timer[5];
    uint32_t SourseClock;
    float DutyCH1;
    float DutyCH2;
    float DutyCH3;
    float DutyCH4;
    uint32_t Frequency;
}TIMStatus;

    /*!
    *   @brief CalcTimClockSourse(TIM_TypeDef *TIMx) - Calculating Timer Clock Sourse
    *       @arg TIMx - number of timer
    *
    */
void CalcTimClockSourse(TIM_TypeDef *TIMx);

    /*!
    *   @brief CalcTimStatus(TIM_TypeDef *TIMx) - Calculating Timer Status
    *       @arg TIMx - number of timer
    *
    */
void CalcTimStatus(TIM_TypeDef *TIMx);

    /*!
    *   @brief CalcTimFrequency(TIM_TypeDef *TIMx, uint16_t freq) - Calculating Timer frequency
    *       @arg TIMx - number of timer
    *       @arg freq - necessary frequency
    */
void CalcTimFrequency(TIM_TypeDef *TIMx, uint16_t freq);

bool SetPWM(uint32_t *CCR_Pin,float Duty);

bool delay_ms(uint32_t ticks);

uint32_t StartMeas(void);

uint32_t EndMeas(void);

#elif(FIL_CALC_TIM > 1)
#error Invalid argument FIL_CALC_TIM
#endif /*FIL_CALC_TIM*/
#endif /*FIL_TIM*/
