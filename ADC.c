    /*!
    *   --------------------------------------------------------------------------
    *                       ///ADC Source file\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 05/08/2022 - last update version ADC
    *
    *       @note [FIL:ADC] ADC Source file.
    */
#include "ADC.h"
//--------------------------------------------------------------------------------//
//---------------------------ADC Interrupts---------------------------------------//
//--------------------------------------------------------------------------------//
/*!
*   @brief ADC_IRQHandler(void)
*/
void ADC_IRQHandler(void)
{

}
#if(FIL_ADC == 1)
    __attribute__((unused)) static uint8_t ADC_CurrentTabs[10] =   {ADC_IN_0,
                                                                    ADC_IN_1,
                                                                    ADC_IN_2,
                                                                    ADC_IN_3,
                                                                    ADC_IN_4,
                                                                    ADC_IN_5,
                                                                    ADC_IN_6,
                                                                    ADC_IN_7,
                                                                    ADC_IN_8,
                                                                    ADC_IN_9};
//------------------------------------------------------------------------------------//
/*!
*   @info Main initializing function
*/
//------------------------------------------------------------------------------------//
__attribute__((unused)) static char RCH = 0;
__attribute__((unused)) static char JCH = 0;
void ADC_Init(ADC_TypeDef *ADCx)
{
    //prescaler divided by 8
    ADC->CCR |= (__configADC_Divider << 16);
////////////////////////////////////////////
#if(__configADC_RESOLUTION == 12)
    ConfADCResolution(ADCx,0);
#elif(__configADC_RESOLUTION == 10)
    ConfADCResolution(ADCx,1);
#elif(__configADC_RESOLUTION == 8)
    ConfADCResolution(ADCx,2);
#elif(__configADC_RESOLUTION == 6)
    ConfADCResolution(ADCx,3);
#endif /*__configADC_RESOLUTION*/
///////////////////////////////////////////
#ifdef STM32F401xx
    // String tag the target ADC
    if( ADCx == ADC1)
    {
        unsigned char Buf[4] = {'A','D','C','1'};
        for(int i = 0; i <= 3; i++)
        {
            ADCStatus.ADCSource[i] = Buf[i];
        }
    }
    else
    {
        unsigned char Buf[4] = {'A','D','C','2'};
        for(int i = 0; i <= 3; i++)
        {
            ADCStatus.ADCSource[i] = Buf[i];
        }
    }
#endif /*STM32F401xx*/
///////////////////////////////////////////
#if(__configADC_Mode == 1)
    if(ADC_IN_0 >= 0)
    {
        ADCAddRegularChannel(ADCx,ADC_IN_0,ADC_480_CYCLES,RCH);
        #if(__configUSE_Battery_Charging == 1)
        #undef __configUSE_Temperature_Sensor
        ADCAddInjectedGroup(ADCx,1,18,0,0,0);
        ADC->CCR |= (0x1 << 22);
        #endif /*__configUSE_Battery_Charging*/
        #if(__configUSE_Temperature_Sensor == 1)
        ADCAddInjectedGroup(ADCx,1,18,0,0,0);
        ADC->CCR |= (0x1 << 23);
        #endif /*__configUSE_Temperature_Sensor*/
        ADCSimpleConfigure(ADCx);
    }
///////////////////////////////////////////
#elif(__configADC_Mode == 2)

///////////////////////////////////////////
#elif(__configADC_Mode == 3 || __configADC_Mode == 4)
    ADCAddSingleChannel(ADCx,ADC_IN_0,ADC_480_CYCLES);
    if(ADC_CurrentTabs[1] >= 0)
    {
        ADCAddInjectedChannel(ADCx,ADC_IN_1,ADC_480_CYCLES,JCH);
        #if(__configADC_Mode == 4)
        if(ADC_CurrentTabs[2] <= 16)
        {
            ADCAddInjectedChannel(ADCx,ADC_IN_2,ADC_480_CYCLES,JCH);
            if(ADC_CurrentTabs[3] <= 16)
            {
                ADCAddInjectedChannel(ADCx,ADC_IN_3,ADC_480_CYCLES,JCH);
                if(ADC_CurrentTabs[4] <= 16)
                {
                    ADCAddInjectedChannel(ADCx,ADC_IN_4,ADC_480_CYCLES,JCH);
                }
            }
        }
        #endif /*__configADC_Mode*/
    }
    #if(__configUSE_Battery_Charging == 1)
    #undef __configUSE_Temperature_Sensor
    ADCAddInjectedChannel(ADCx,18,ADC_480_CYCLES,JCH);
    ADC->CCR |= (1 << 22);
    #endif /*__configUSE_Battery_Charging*/
    #if(__configUSE_Temperature_Sensor == 1)
    ADCAddInjectedChannel(ADCx,18,ADC_480_CYCLES,JCH);
    ADC->CCR |= ADC_CCR_VBATE;
    #endif /*__configUSE_Temperature_Sensor*/
    SetADCContInjected(ADCx);
    ADCSimpleConfigure(ADCx);
#endif /*__configADC_Mode*/
}
//////////////////////////////////////////////////////////////////////////
/**
*   This Functions necessary for parsing Multiplexer outputs
*/
//------------------------------------------------------------------------------------//
#if(__configADC_Mode == 3 || __configADC_Mode == 4)

static void SetMulriplexer_State(uint16_t State)
{
    switch(State)
    {
        case 0:
            ResetPin(MULPLXA_PIN);
            ResetPin(MULPLXB_PIN);
            ResetPin(MULPLXC_PIN);
            break;
        case 1:
            SetPin(MULPLXA_PIN);
            ResetPin(MULPLXB_PIN);
            ResetPin(MULPLXC_PIN);
            break;
        case 2:
            ResetPin(MULPLXA_PIN);
            SetPin(MULPLXB_PIN);
            ResetPin(MULPLXC_PIN);
            break;
        case 3:
            SetPin(MULPLXA_PIN);
            SetPin(MULPLXB_PIN);
            ResetPin(MULPLXC_PIN);
            break;
        case 4:
            ResetPin(MULPLXA_PIN);
            ResetPin(MULPLXB_PIN);
            SetPin(MULPLXC_PIN);
            break;
        case 5:
            SetPin(MULPLXA_PIN);
            ResetPin(MULPLXB_PIN);
            SetPin(MULPLXC_PIN);
            break;
        case 6:
            ResetPin(MULPLXA_PIN);
            SetPin(MULPLXB_PIN);
            SetPin(MULPLXC_PIN);
            break;
        case 7:
            SetPin(MULPLXA_PIN);
            SetPin(MULPLXB_PIN);
            SetPin(MULPLXC_PIN);
            break;
    }
}
/*!
*   @brief ADC_Multiplexer_Get() - get data from multiplexer
*
*/
#define Single_Test     (0)
int NumPort = 0;
void ADC_Multiplexer_Get(ADC_TypeDef *ADCx)
{
#if(Single_Test == 1)
SetMulriplexer_State(0);
ADCStatus.Multiplexer1[0] = ADCx->JDR1;
#else /*Single_Test*/
    while(true)
    {
        SetMulriplexer_State(NumPort);
        if( delay_ms(4) == false) return;
        if(NumPort == 8)
            {
                NumPort = 0;
                break;
            }
        #if(__configCONVERT_Volts == 1)
        ADCStatus.Multiplexer1[NumPort] = ((float)ADCx->JDR1) * 3.3 / K_RESOLUTION;
        #else
        ADCStatus.Multiplexer1[NumPort] = ADCx->JDR1;
        #endif/*__configCONVERT_Volts*/
        NumPort++;
    }
#endif /*Single_Test*/
}
#endif /*__configADC_Mode*/
////////////////////////////////////////////////////////////////////////////
void AnalogReadRegular(void)
{
// Convert in Volts
#if(__configCONVERT_Volts == 1)
#if(__configADC_Mode != 2 || __configADC_Mode != 5)
    ADCStatus.adc_data[0] = ((float)ADC1->DR) * 3.3 / K_RESOLUTION;
#endif /*__configADC_Mode*/
//////////////////////////////////////////////////////////////////////////
// Non convert Volts
#elif(__configCONVERT_Volts == 0)
#if(__configADC_Mode != 2 || __configADC_Mode != 5)
    ADCStatus.adc_data[0] = ADC1->DR;
#endif /*__configADC_Mode*/
#endif /*__configCONVERT_Volts*/
}

void AnalogReadInjected(ADC_TypeDef *ADCx)
{
    ADC_Multiplexer_Get(ADCx);
}
#endif /*FIL_ADC*/
