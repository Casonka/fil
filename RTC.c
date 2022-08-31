#include "RTC.h"

#if (FIL_RTC == 1)
void TAMP_STAMP_IRQHandler(void)
{

}

void RTC_WKUP_IRQHandler(void)
{

}

void RTC_Alarm_IRQHandler(void)
{
    if(AlarmAEvent)
    {
    /*!
    *   @note [FIL:RTC] This sector will complete when RTC Alarm A triggered
    */
    }
    if(AlarmBEvent)
    {
    /*!
    *   @note [FIL:RTC] This sector will complete when RTC Alarm B triggered
    */
    }

ClearRTCAlarms;
}

#endif /*FIL_RTC*/
