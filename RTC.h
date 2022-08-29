    /*!
    *   --------------------------------------------------------------------------
    *                       ///RTC initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 29/08/2022 - last update version RTC
    *
    *       @note [FIL:RTC] Configuration file RTC
    */
#pragma once
#include "FilConfig.h"

#if (FIL_RTC == 1)

/*!
*   @list DateTime calibration list
*/
#define FIL_YEARS       __configRTC_YEAR
#define FIL_MONTHS      __configRTC_MONTHS
#define FIL_WEEK        (__configRTC_DATE/7)
#define FIL_DATE        __configRTC_DATE
#define FIL_HOURS       __configRTC_HOURS
#define FIL_MINUTES     __configRTC_MINUTES
#define FIL_SECONDS     __configRTC_SECONDS

/*!
*   @brief RTC_Calibration - sets settings for Real Time Clock
*       @attention This function necessary calling one time, after using comment or delete applying
*/
#define RTC_Calibration                                 {\
        PWRUnlockWriteProtection;                        \
        RCC_RTCClockON;                                  \
        RCC_MKOutput1;                                   \
        LSE_ON;                                          \
        RTCUnlockProtection;                             \
        RTCInitModeON;                                   \
        RTCPassShadow;                                   \
        RTC_SetTime(FIL_HOURS,FIL_MINUTES,               \
                    FIL_SECONDS);                        \
        RTC_SetDate(FIL_YEARS,FIL_MONTHS,                \
                    FIL_WEEK,FIL_DATE);                  \
        RTCLockShadow;                                   \
        RTCInitModeOFF;                                  \
        RTCLockProtection;                               }

#ifndef __configRTC_ALARM_B_YEARS || __configRTC_ALARM_B_MONTHS || __configRTC_ALARM_B_DATE
#define RTC_Alarm_A_Set        {\
        SetRTCAlarmAInterrupt;  \
        SetRTCAlarmADateMask;   \

        SetRTCAlarmA;           \


//----------------------------High commands------------------------------------//
#define RTC_SetTime(HOURS,MINUTES,SECONDS)  {\
        RTC->TR = 0;                         \
        RTC->TR |= ((HOURS/10) << 20);       \
        RTC->TR |= ((HOURS%10) << 16);       \
        RTC->TR |= ((MINUTES/10) << 12);     \
        RTC->TR |= ((MINUTES%10) << 8);      \
        RTC->TR |= ((SECONDS/10) << 4);      \
        RTC->TR |= (SECONDS%10);             }

#define RTC_SetDate(YEARS,MONTHS,WEEK,DAYS)     {\
        RTC->DR = 0;                             \
        RTC->DR |= ((YEARS/10) << 20);           \
        RTC->DR |= ((YEARS%10) << 16);           \
        RTC->DR |= ((MONTHS/10) << 12);          \
        RTC->DR |= ((MONTHS%10) << 8);           \
        RTC->DR |= (WEEK << 13);                 \
        RTC->DR |= (DAYS/10 << 4);               \
        RTC->DR |= (DAYS%10);                    }

//----------------------------------------Set state----------------------------------------------------//
#define SetRTCAlarmA            (RTC->CR |= RTC_CR_ALRAE)
#define SetRTCAlarmB            (RTC->CR |= RTC_CR_ALRBE)
#define SetRTCAlarmAInterrupt   (RTC->CR |= RTC_CR_ALRAIE)
#define SetRTCAlarmBInterrupt   (RTC->CR |= RTC_CR_ALRBIE)
#define RTCPassShadow           (RTC->CR |= RTC_CR_BYPSHAD)
#define RTCInitModeON           (RTC->ISR |= RTC_ISR_INIT)
#define RTCUnlockProtection     {\
        RTC->WPR = 0xCA;         \
        RTC->WPR = 0x53;         }
#define SetRTCAlarmADateDontCare (RTC->ALRMAR |= RTC_ALRMAR_MSK4)
#define SetRTCAlarmADateMask(DATE)      ()
#define SetRTCAlarmAMonthMask(MONTH)
#define SetRTCAlarmADayMask(DAY)
#define SetRTCAlarmAHourMask(HOUR)
#define SetRTCAlarmAMinuteMask(MINUTE)
#define SetRTCAlarmASecondMask(SECOND)
#define SetRTCAlarmBDateMask    (RTC->ALRMBR |= RTC_ALRMBR_MSK4)
//---------------------------------------Reset state---------------------------------------------------//
#define RTCLockShadow           (RTC->CR &= ~RTC_CR_BYPSHAD)
#define RTCLockProtection       (RTC->WPR = 0xFF)
#define RTCInitModeOFF          (RTC->ISR &= ~RTC_ISR_INIT)
#define SetRTCAlarmADateMask    (RTC->ALRMAR &= ~RTC_ALRMAR_MSK4)
#define SetRTCAlarmBDateMask    (RTC->ALRMBR &= ~RTC_ALRMBR_MSK4)

struct {
    char Date[10];  //GOST P 7.0.97-2016
    char Time[8];   //ISO8601
    uint32_t Timestamp;
    uint32_t DR,TR,SSR;
}RTCStatus;

#define RTC_GetStatus                                                      {\
        RTC_GetTime;                                                        \
        RTCStatus.Time[0] = ((char)(((RTCStatus.TR >> 20) & 0x3) + 0x30));  \
        RTCStatus.Time[1] = ((char)(((RTCStatus.TR >> 16) & 0xF) + 0x30));  \
        RTCStatus.Time[2] = ':';                                            \
        RTCStatus.Time[3] = ((char)(((RTCStatus.TR >> 12) & 0x7) + 0x30));  \
        RTCStatus.Time[4] = ((char)(((RTCStatus.TR >> 8) & 0xF) + 0x30));   \
        RTCStatus.Time[5] = ':';                                            \
        RTCStatus.Time[6] = ((char)(((RTCStatus.TR >> 4) & 0x7) + 0x30));   \
        RTCStatus.Time[7] = ((char)(((RTCStatus.TR) & 0xF) + 0x30));        \
        RTCStatus.Date[0] = ((char)(((RTCStatus.DR >> 4) & 0x3) + 0x30));   \
        RTCStatus.Date[1] = ((char)(((RTCStatus.DR) & 0xF) + 0x30));        \
        RTCStatus.Date[2] = '.';                                            \
        RTCStatus.Date[3] = ((char)(((RTCStatus.DR >> 12) & 0x1) + 0x30));  \
        RTCStatus.Date[4] = ((char)(((RTCStatus.DR >> 8) & 0xF) + 0x30));   \
        RTCStatus.Date[5] = '.';                                            \
        RTCStatus.Date[6] = '2';                                            \
        RTCStatus.Date[7] = '0';                                            \
        RTCStatus.Date[8] = ((char)(((RTCStatus.DR >> 20) & 0xF) + 0x30));  \
        RTCStatus.Date[9] = ((char)(((RTCStatus.DR >> 16) & 0xF) + 0x30));  }

#define RTC_GetTime         {\
        RTCStatus.SSR = RTC->SSR;      \
        RTCStatus.TR = RTC->TR;        \
        RTCStatus.DR = RTC->DR;        }
#endif /*FIL_RTC*/
