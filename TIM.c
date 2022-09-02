    /*!
    *   --------------------------------------------------------------------------
    *                       ///TIM Source file\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska, Evgeny Garanin
    *   @date 13/07/2022 - last update version TIM
    *
    *       @note [FIL:TIM] TIM Source file.
    */
#include "TIM.h"
uint32_t globalTime = 0;

/*!
*    @brief void SysTick_Handler(void) - System 24-bit timer, increment the time value in 1Hz to 1000
*       @note [FIL:TIM] Можно использовать для отчета времени, 1000 единиц соответствуют 1 секунде
*/

void SysTick_Handler(void)
{

    globalTime++;
}
#if (FIL_CALC_TIM == 1)
//---------------------------------------------------------//
//----------------------Timer Interrupts-------------------//
//---------------------------------------------------------//
void TIM1_IRQHandler(void)
{

ResetTimSR(TIM1);
}

void TIM2_IRQHandler(void)
{

ResetTimSR(TIM2);
}

void TIM3_IRQHandler(void)
{

ResetTimSR(TIM3);
}

void TIM4_IRQHandler(void)
{

ResetTimSR(TIM4);
}

void TIM5_IRQHandler(void)
{
    //SetVoltage(EnginePWM);
    //PID_Low_Level();
ResetTimSR(TIM5);
}

#if defined(STM32F40_41xxx) /*--------------STM32F407------------------*/
void TIM6_DAC_IRQHandler(void)
{

ResetTimSR(TIM6);
}


void TIM7_IRQHandler(void)
{

ResetTimSR(TIM7);
}

void TIM8_UP_TIM13_IRQHandler(void)
{

ResetTimSR(TIM13);
}
#endif /*STM32F40_41xxx*/
static uint32_t startTick;
void delay_ms(uint32_t ticks)
{
    if(ticks == 0) return;
    startTick = globalTime;
    while((globalTime - startTick) < ticks) {}
}

    /*!
    *   @brief CalcTimStatus(TIM_TypeDef *TIMx) - Calculating Timer Status
    *       @arg TIMx - number of timer
    *           @note [FIL:TIM] Функция позволяет получить текущий статус таймера, заполнения ШИМ и частоту работы
    */
void CalcTimStatus(TIM_TypeDef *TIMx)
{
    TIMStatus.Timer[0] = 'T';
    TIMStatus.Timer[1] = 'I';
    TIMStatus.Timer[2] = 'M';
    CalcTimClockSourse(TIMx);

    TIMStatus.DutyCH1 = ((uint32_t)(((float)TIMx->CCR1) / TIMx->ARR * 100));
    TIMStatus.DutyCH2 = ((uint32_t)(((float)TIMx->CCR2) / TIMx->ARR * 100));
    TIMStatus.DutyCH3 = ((uint32_t)(((float)TIMx->CCR3) / TIMx->ARR * 100));
    TIMStatus.DutyCH4 = ((uint32_t)(((float)TIMx->CCR4) / TIMx->ARR * 100));
    TIMStatus.Frequency = (TIMStatus.SourseClock / ((TIMx->PSC + 1) * TIMx->ARR));
}
    /*!
    *   @brief CalcTimFrequency(TIM_TypeDef *TIMx, uint16_t freq) - Calculating Timer frequency
    *       @arg TIMx - number of timer
    *       @arg freq - necessary frequency
    *           @note [FIL:TIM] Функция для расчета частоты работы таймераы
    */
void CalcTimFrequency(TIM_TypeDef *TIMx, uint16_t freq)
{
    CalcTimClockSourse(TIMx);

    TIMx->PSC = (freq >= 100) ? ((uint32_t)(TIMStatus.SourseClock / 1000000)) :
                (freq >= 10000) ? ((uint32_t)(TIMStatus.SourseClock / 10000)) : ((uint32_t)(TIMStatus.SourseClock / 100000));
    TIMx->ARR = ((uint32_t)(TIMStatus.SourseClock / ((TIMx->PSC)* freq)));
    TIMx->PSC -= 1;
}

    /*!
    *   @brief CalcTimClockSourse(TIM_TypeDef *TIMx) - Calculating Timer Clock Sourse
    *       @arg TIMx - number of timer
    *       @note [FIL:TIM] Функция вычисляет ресурс, используемый таймером, базовый расчет.
    */
void CalcTimClockSourse(TIM_TypeDef *TIMx)
{
    CalcRCCClocks();
    TIMStatus.Timer[3] = (TIMx == TIM1) ? 0x31 :
                         (TIMx == TIM2) ? 0x32 :
                         (TIMx == TIM3) ? 0x33 :
                         (TIMx == TIM4) ? 0x34 :
                         (TIMx == TIM5) ? 0x35 :
                         (TIMx == TIM6) ? 0x36 :
                         (TIMx == TIM7) ? 0x37 :
                         (TIMx == TIM8) ? 0x38 :
                         (TIMx == TIM9) ? 0x39 : 0x31 ;
    TIMStatus.Timer[4] = (TIMx == TIM10) ? 0x30 :
                         (TIMx == TIM11) ? 0x31 :
                         (TIMx == TIM12) ? 0x32 :
                         (TIMx == TIM13) ? 0x33 :
                         (TIMx == TIM14) ? 0x34 : ' ';
    #if defined(STM32F401xx)
    if(TIMx == TIM1 || TIMx == TIM9 || TIMx == TIM10 || TIMx == TIM11)
    {
        TIMStatus.SourseClock = Clocks.CurrentAPB2;
    }
    else if(TIMx == TIM2 || TIMx == TIM3 || TIMx == TIM4 || TIMx == TIM5)
    {
        TIMStatus.SourseClock = Clocks.CurrentAPB1;
    }
#elif defined(STM32F40_41xxx)
    if(TIMx == TIM1 || TIMx == TIM8 || TIMx == TIM9 || TIMx == TIM10 || TIMx == TIM11)
    {
        TIMStatus.SourseClock = Clocks.CurrentAPB2;
    }
    else if(TIMx == TIM2 || TIMx == TIM3 || TIMx == TIM4 || TIMx == TIM5 || TIMx == TIM6 || TIMx == TIM7 || TIMx == TIM12 || TIMx == TIM13 || TIMx == TIM14)
    {
        TIMStatus.SourseClock = Clocks.CurrentAPB1;
    }
#endif
}

    /*!
    *   @brief SetPWM(CCR_Pin,Duty) - Установить напряжение на двигатель
    *       @arg CCR_Pin - selecting channel of timer
    *       @arg Duty - duty value
    *       @note [FIL:TIM] Функция предназначена для установления заполнения ШИМ.
    */
    bool SetPWM(uint32_t *CCR_Pin,float Duty)
    {
        if(Duty > 1.0) Duty = 1.0;
        if(Duty < -1.0) Duty = -1.0;
        if(Duty >= 0)
        {
            *CCR_Pin = ((int32_t) (Duty * MAX_PWM));
            return true;
        }
        else
        {
            *CCR_Pin = ((int32_t)(MAX_PWM +  (Duty * MAX_PWM)));
            return true;
        }
        return false;
    }

static uint32_t startInterval;
static uint32_t endInterval;
    uint32_t StartMeas(void)
    {
        SetPin(LED_PIN);
        return startInterval = globalTime;
    }

    uint32_t EndMeas(void)
    {
        ResetPin(LED_PIN);
        return endInterval = (globalTime - startInterval);
    }
#endif /*FIL_CALC_TIM*/
