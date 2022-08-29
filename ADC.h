    /*!
    *   --------------------------------------------------------------------------
    *                       ///ADC initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 18/07/2022 - last update version ADC
    *
    *       @note [FIL:ADC] Configuration file ADC
    */
#pragma once
#include "FilConfig.h"

#if(FIL_ADC == 1)
//----------------------------------------ADC Length-------------------------------------------------------------//
#define ADC_3_CYCLES    0
#define ADC_15_CYCLES   1
#define ADC_28_CYCLES   2
#define ADC_56_CYCLES   3
#define ADC_84_CYCLES   4
#define ADC_112_CYCLES  5
#define ADC_144_CYCLES  6
#define ADC_480_CYCLES  7

#define ADC_IN_0    __configUSE_SENSOR_1
#define ADC_IN_1    __configUSE_SENSOR_2
#define ADC_IN_2    __configUSE_SENSOR_3
#define ADC_IN_3    __configUSE_SENSOR_4
#define ADC_IN_4    __configUSE_SENSOR_5
#define ADC_IN_5    __configUSE_SENSOR_6
#define ADC_IN_6    __configUSE_SENSOR_7
#define ADC_IN_7    __configUSE_SENSOR_8
#define ADC_IN_8    __configUSE_SENSOR_9
#define ADC_IN_9    __configUSE_SENSOR_10
#if defined (support_High)
#define ADC_IN_10   __configUSE_SENSOR_11
#define ADC_IN_11   __configUSE_SENSOR_12
#define ADC_IN_12   __configUSE_SENSOR_13
#define ADC_IN_13   __configUSE_SENSOR_14
#define ADC_IN_14   __configUSE_SENSOR_15
#define ADC_IN_15   __configUSE_SENSOR_16
#endif /*support_High*/

#if(__configADC_RESOLUTION == 10)
    #define K_RESOLUTION    1024.0
#elif(__configADC_RESOLUTION == 8)
    #define K_RESOLUTION    256.0
#elif(__configADC_RESOLUTION == 6)
    #define K_RESOLUTION    64.0
#else
    #define K_RESOLUTION    4096.0
#endif /*__configADC_RESOLUTION*/
//----------------------------------------ADC Functions----------------------------------------------------------//
    /*!
    *   @brief  ADCAllScanConfigure(ADC,LENGTH,
    *           CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8,CH9,CH10,CH11,CH12,CH13,CH14,CH15,CH16) -
    *           -   Configuration all channels ADC (Scan mode)
    *       @arg ADC - Number of ADC
    *       @arg LENGTH - Regular channel sequence length
    *       @arg CHx - Connect ADC_IN pins to conversion queue
    *       @arg NUMBER - NUMBER of ADC_IN active pins
    */
    #define ADCAllScanConfigure(ADC,LENGTH,                                         \
            CH1,CH2,CH3,CH4,CH5,CH6,CH7,CH8,CH9,CH10,CH11,CH12,CH13,CH14,CH15,CH16){\
        SetADCLength(ADC,LENGTH);                                                   \
        ConfADCSQ1(ADC,CH1,CH2,CH3,CH4);                                            \
        ConfADCSQ2(ADC,CH5,CH6,CH7,CH8,CH9,CH10);                                   \
        ConfADCSQ3(ADC,CH11,CH12,CH13,CH14,CH15,CH16);                              \
        SetADCScan(ADC);                                                            \
        SetADCDDS(ADC);                                                             \
        SetADCDMA(ADC);                                                             \
        SetADCCont(ADC);                                                            \
        SetADCAdon(ADC);                                                            \
        ADCStartRegular(ADC);                                                       }

    /*!
    *   @brief  ADCSimpleConfigure(ADC) - Configuration ADC simple
    *       @arg ADC - Number of ADC
    *
    */
    #define ADCSimpleConfigure(ADC)                                            {\
        SetADCAdon(ADC);                                                        \
        SetADCCont(ADC);                                                        \
        SetADCScan(ADC);                                                        \
        (__configADC_InterruptRequest == 1) ? SetADCRegularInterrupt(ADC) :     \
                                              ResetADCRegularInterrupt(ADC);    \
        (__configADC_InterruptRequest == 1) ? SetADCInjectedInterrupt(ADC) :    \
                                              ResetADCInjectedInterrupt(ADC);   \
        ADCStartRegular(ADC);                                                   \
        while(!(ADC->SR & ADC_SR_EOC)) {}                                       \
        if(CheckADCJStart(ADC) == 1) ADCStartInjected(ADC);                     \
        while(!(ADC->SR & ADC_SR_EOC)) {}                                       }

//----------------------------------------REGULAR----------------------------------------------------------------//
    /*!
    *   @brief  ADCAddRegularChannel(ADC,CHANNEL,CYCLES, RCH) - Adding new channel to conversions ADC
    *       @arg ADC - Number of ADC
    *       @arg CHANNEL - Number of target channel
    *       @arg CYCLES - Sample time selection
    *       @arg RCH
    */
    #define ADCAddRegularChannel(ADC,CHANNEL,CYCLES,RCH)                                   {\
                        ADC->SQR1 &= ~(0xF << 20);                                          \
                        ADC->SQR1 |= RCH << 20;                                             \
                        *(&ADC->SQR3 - (RCH / 6)) |= CHANNEL << ((RCH * 5) % 30);           \
                        *(&ADC->SMPR2 - ((RCH / 10)*0x4)) |= CYCLES << ((RCH * 3) % 30);    \
                        RCH++;                                                              }

    /*!
    *   @brief  AddADCSingleChannel(ADC,CHANNEL,CYCLES) - Adding single channel to conversions ADC
    *       @arg ADC - Number of ADC
    *       @arg CHANNEL - Number of target channel
    *       @arg CYCLES - Sample time selection
    *           @attention This function delete old channel from ADC list before writing new target channel
    */
    #define ADCAddSingleChannel(ADC,CHANNEL,CYCLES)                                        {\
                        ADC->CR2 &= ~ADC_CR2_ADON;                                          \
                        ADC->SQR3 &= ~(0x1F);                                               \
                        ADC->SMPR2 &= ~(0x7);                                               \
                        ADC->SQR3 |= CHANNEL;                                               \
                        ADC->SMPR2 |= CYCLES;                                               \
                        ADC->CR1 &= ~ADC_CR1_SCAN;                                          \
                        ADC->CR2 |= (ADC_CR2_ADON | ADC_CR2_CONT);                          }

//----------------------------------------INJECTED----------------------------------------------------------------//
    /*!
    *   @brief  ADCAddInjectedChannel(ADC,CHANNEL,CYCLES, JCH) - Adding new injected channel to conversions ADC
    *       @arg ADC - Number of ADC
    *       @arg CHANNEL - Number of target injected channel
    *       @arg CYCLES - Sample time selection
    *       @arg JCH
    */
    #define ADCAddInjectedChannel(ADCx,CHANNEL,CYCLES, JCH)                                        {\
                        ADCx->JSQR &= ~(0xF << 20);                                                 \
                        ADCx->JSQR |= (JCH << 20);                                                  \
                        ADCx->JSQR |= (CHANNEL << (((JCH + 3) * 5) % 30));                          \
                        *(&ADCx->SMPR2 - ((JCH / 10)*0x4)) |= (CYCLES << (JCH * 3) % 30);           \
                        if(JCH == 3) JCH = 0;                                                       \
                        JCH++;                                                                      }

    /*!
    *   @brief  ADCAddInjectedGroups(ADC,NUMBER,J1,J2,J3,J4) -
    *       @arg ADC - Number of ADC
    *       @arg NUMBER - Number of necessary channels
    *       @arg Jx - number of ADC_IN channel
    */
    #define ADCAddInjectedGroup(ADC,NUMBER,J1,J2,J3,J4)                                        {\
                        ADC->JSQR &= ~(0x3FFFFF);                                               \
                        ADC->JSQR |= (NUMBER << 20);                                            \
                        ADC->JSQR |= ((J1) | (J2 << 5) | (J3 << 10) | (J4 << 15));              \
                        SetADCContInjected(ADC);                                                }

//----------------------------------------Set state----------------------------------------------------------------------------------------------------------------------------//
    #define SetADCSMP1(ADC,CYCLES)          ((ADC->SMPR1) |= ADCSmpr1(CYCLES))
    #define SetADCSMP2(ADC,CYCLES)          ((ADC->SMPR2) |= ADCSmpr2(CYCLES))
    #define SetADCLength(ADC,LENGTH)        ((ADC->SQR1) |= (LENGTH << 20))
    #define SetADCSQ1(ADC,CH1,CH2,CH3,CH4)  ((ADC->SQR1) |= ADCSQ1(CH1,CH2,CH3,CH4))
    #define SetADCSQ2(ADC,CH5,CH6,CH7,CH8,CH9,CH10) ((ADC->SQR2) |= ADCSQ2(CH5,CH6,CH7,CH8,CH9,CH10))
    #define SetADCSQ3(ADC,CH11,CH12,CH13,CH14,CH15,CH16) ((ADC->SQR3) |= ADCSQ3(CH11,CH12,CH13,CH14,CH15,CH16))
    #define SetADCScan(ADC)                 ((ADC->CR1) |= (1 << 8))
    #define SetADCDMA(ADC)                  ((ADC->CR2) |= (ADC_CR2_DMA))
    #define SetADCCont(ADC)                 ((ADC->CR2) |= (ADC_CR2_CONT))
    #define SetADCDDS(ADC)                  ((ADC->CR2) |= (ADC_CR2_DDS))
    #define SetADCAdon(ADC)                 ((ADC->CR2) |= (ADC_CR2_ADON))
    #define ADCStartRegular(ADC)            ((ADC->CR2) |= (ADC_CR2_SWSTART))
    #define ADCStartInjected(ADC)           ((ADC->CR2) |= (ADC_CR2_JSWSTART))
    #define SetADCInjectedInterrupt(ADC)    ((ADC->CR1) |= (ADC_CR1_JEOCIE))
    #define SetADCRegularInterrupt(ADC)     ((ADC->CR1) |= (ADC_CR1_EOCIE))
    #define SetADCContInjected(ADC)         ((ADC->CR1) |= (ADC_CR1_JAUTO))
//----------------------------------------Reset state----------------------------------------------------------------------------------------------------------------------------//
    #define ResetADCCont(ADC)               ((ADC->CR2) &= (~ADC_CR2_CONT))
    #define ADCStopRegular(ADC)             ((ADC->CR2) &= (~ADC_CR2_SWSTART))
    #define ResetADCEOCEvent(ADC)           ((ADC->SR) &= (~ADC_SR_EOC))
    #define ResetADCJEOCEvent(ADC)          ((ADC->SR) &= (~ADC_SR_JEOC))
    #define ResetADCOVREvent(ADC)           ((ADC->SR) &= (~ADC_SR_OVR))
    #define ResetADCInjectedInterrupt(ADC)  ((ADC->CR1) &= (~ADC_CR1_JEOCIE))
    #define ResetADCRegularInterrupt(ADC)   ((ADC->CR1) &= (~ADC_CR1_EOCIE))
//----------------------------------------Status monitoring--------------------------------------------------------------------------------------------------------------------//
    #define ADCAnalogWatchdogEvent(ADC)     (((ADC->SR) & (ADC_SR_AWD)))
    #define ADCRegularEndEvent(ADC)         (((ADC->SR) & (ADC_SR_EOC)) >> 1)
    #define ADCInjectedEndEvent(ADC)        (((ADC->SR) & (ADC_SR_JEOC)) >> 2)
    #define ADCInjectedStartEvent(ADC)      (((ADC->SR) & (ADC_SR_JSTRT)) >> 3)
    #define ADCRegularStartEvent(ADC)       (((ADC->SR) & (ADC_SR_STRT)) >> 4)
    #define ADCOverrunEvent(ADC)            (((ADC->SR) & (ADC_SR_OVR)) >> 5)
    #define CheckADCJStart(ADC)             (((ADC->CR1) & (ADC_CR1_JAUTO)) >> 10)
//---------------------------Simple commands reset and set the state-------------------------------------------------------------------------------------------------------------//
    #define ConfADCResolution(ADC,RESOLUTION)               {ADC->CR1 = (((ADC->CR1)&(~(ADC_CR1_RES)))|ADCResolution(RESOLUTION));}
    #define ConfADCLength(ADC,LENGTH)                       {ADC->SQR1 = (((ADC->SQR1)&(~(ADC_SQR1_L)))|ADCLength(LENGTH));}
    #define ConfADCSQ1(ADC,CH1,CH2,CH3,CH4)                 {ADC->SQR1 = (((ADC->SQR1)&(~(0xFFFFF)))|ADCSQ1(CH1,CH2,CH3,CH4));}
    #define ConfADCSQ2(ADC,CH5,CH6,CH7,CH8,CH9,CH10)        {ADC->SQR2 = (((ADC->SQR2)&(~(0x3FFFFFFF)))|ADCSQ2(CH5,CH6,CH7,CH8,CH9,CH10));}
    #define ConfADCSQ3(ADC,CH11,CH12,CH13,CH14,CH15,CH16)   {ADC->SQR3 = (((ADC->SQR3)&(~(0x3FFFFFFF)))|ADCSQ3(CH11,CH12,CH13,CH14,CH15,CH16));}
    #define ConfADCSmpr1(ADC,CYCLES)                        {ADC->SMPR1 = (((ADC->SMPR1)&(~(0x7FFFFFF)))|ADCSmpr1(CYCLES));}
    #define ConfADCSmpr2(ADC,CYCLES)                        {ADC->SMPR2 = (((ADC->SMPR2)&(~(0x3FFFFFFF)))|ADCSmpr2(CYCLES));}
    #define ConfADCSmpr(ADC,NUMBER,CYCLES)         {\
        if(NUMBER > 0) ConfADCSmpr2(ADC,CYCLES);    \
        if(NUMBER > 10) ConfADCSmpr1(ADC,CYCLES);   }

    #define ADCSQ1(CH1,CH2,CH3,CH4)                             ((uint32_t)(CH1 << 15) | (CH2 << 10) | (CH3 << 5)  | (CH4))
    #define ADCSQ2(CH5,CH6,CH7,CH8,CH9,CH10)                    ((uint32_t)(CH5 << 25) | (CH6 << 20) | (CH7 << 15) | (CH8 << 10) | (CH9 << 5)  | (CH10))
    #define ADCSQ3(CH11,CH12,CH13,CH14,CH15,CH16)               ((uint32_t)(CH11 << 25) | (CH12 << 20) | (CH13 << 15) | (CH14 << 10) | (CH15 << 5)  | (CH16))
    #define ADCSmpr1(CYCLES)                                    ((uint32_t)(CYCLES << 24) | (CYCLES << 21) | (CYCLES << 18) | (CYCLES << 15) | (CYCLES << 12) | (CYCLES << 9) | (CYCLES << 6) | (CYCLES << 3) | (CYCLES))
    #define ADCSmpr2(CYCLES)                                    ((uint32_t)(CYCLES << 27) | (CYCLES << 24) | (CYCLES << 21) | (CYCLES << 18) | (CYCLES << 15) | (CYCLES << 12) | (CYCLES << 9) | (CYCLES << 6) | (CYCLES << 3) | (CYCLES))
    #define ADCResolution(RES)                                  ((uint32_t)(RES << 24))

#if(__configCONVERT_Volts == 1)
struct {
    unsigned char ADCSource[4];
    float BATTERY;
    float TEMPERATURE;
    float Multiplexer1[8];
    float Multiplexer2[8];
    float adc_data[5];
}ADCStatus;
#elif (__configCONVERT_Volts == 0)
struct {
    unsigned char ADCSource[4];
    uint16_t BATTERY;
    uint16_t TEMPERATURE;
    uint16_t Multiplexer1[8];
    uint16_t Multiplexer2[8];
    uint16_t adc_data[5];
}ADCStatus;
#endif /*__configCONVERT_Volts*/

#if (__configADC_Mode == 3 || __configADC_Mode == 4)

    /*!
    *   @brief ADC_Multiplexer_Get(ADC_TypeDef *ADCx) - Parsing ADC Data from multiplexor
    *       @arg ADCx - number of ADC
    */
    void ADC_Multiplexer_Get(ADC_TypeDef *ADCx);

#elif (__configADC_Mode == 1 || __configADC_Mode == 2)

    /*!
    *   @brief ADC_Simple_Get(ADC_TypeDef *ADCx) - Parsing ADC Data from regular channels
    *       @arg TIMx - number of timer
    *
    */
    void ADC_Simple_Get(ADC_TypeDef *ADCx);


#elif (__configADC_Mode == 5)

#else
#error Invalig argument __configADC_Mode
#endif /*__configADC_Mode*/
#endif /*__configADC_MODE*/

    /*!
    *   @brief ADC_Init(ADC_TypeDef *ADCx) - main initialization function for ADC
    *       @arg ADCx - number of ADC
    */
    void ADC_Init(ADC_TypeDef *ADCx);

    /*!
    *   @brief AnalogReadRegular(void) - parsing data from regular channel
    *
    */
    void AnalogReadRegular(void);

    /*!
    *   @brief AnalogReadInjected(void) - parsing data from injected channels
    *   @brief ADCx - number of ADC
    */
    void AnalogReadInjected(ADC_TypeDef *ADCx);
