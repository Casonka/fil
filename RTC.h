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
        while(!RTCInitFlagEvent) {}                      \
        RTCPassShadow;                                   \
        RTC_SetTime(FIL_HOURS,FIL_MINUTES,               \
                    FIL_SECONDS);                        \
        RTC_SetDate(FIL_YEARS,FIL_MONTHS,                \
                    FIL_WEEK,FIL_DATE);                  \
        RTCLockShadow;                                   \
        RTCInitModeOFF;                                  \
        RTCLockProtection;                               \
        PWRLockWriteProtection;                          }

#if (__configUSE_ALARM_A == 1)

/*!
*   Control definition time settings Alarm A
*/
#ifndef __configRTC_ALARM_A_DATE
#error Define __configRTC_ALARM_A_DATE parameter
#endif /*__configRTC_ALARM_A_DATE*/
#ifndef __configRTC_ALARM_A_HOURS
#error Define __configRTC_ALARM_A_HOURS parameter
#endif /*__configRTC_ALARM_A_HOURS*/
#ifndef __configRTC_ALARM_A_MINUTES
#error Define __configRTC_ALARM_A_MINUTES parameter
#endif /*__configRTC_ALARM_A_MINUTES*/
#ifndef __configRTC_ALARM_A_SECONDS
#error Define __configRTC_ALARM_A_SECONDS parameter
#endif /*__configRTC_ALARM_A_SECONDS*/

#define RTC_Alarm_A_Init                                                                           {\
        PWRUnlockWriteProtection;                                                                   \
        RTCUnlockProtection;                                                                        \
        StopAlarmA;                                                                                 \
        SetRTCAlarmAInterrupt;                                                                      \
        RTC->ALRMAR = 0;                                                                            \
        if(__configRTC_ALARM_A_DATE < 0) SetRTCAlarmADateDontCare;                                  \
        else SetRTCAlarmADateMask(__configRTC_ALARM_A_DATE);                                        \
        if(__configRTC_ALARM_A_HOURS < 0) SetRTCAlarmAHourDontCare;                                 \
        else SetRTCAlarmAHourMask(__configRTC_ALARM_A_HOURS);                                       \
        if(__configRTC_ALARM_A_MINUTES < 0) SetRTCAlarmAMinuteDontCare;                             \
        else SetRTCAlarmAMinuteMask(__configRTC_ALARM_A_MINUTES);                                   \
        if(__configRTC_ALARM_A_SECONDS > 0) SetRTCAlarmASecondMask(__configRTC_ALARM_A_SECONDS);    \
        else SetRTCAlarmASecondDontCare;                                                            \
        StartAlarmA;                                                                                \
        RTCLockProtection;                                                                          \
        PWRLockWriteProtection;                                                                     \
        if(((EXTI->IMR & EXTI_IMR_MR17) >> 17) == 0) {                                              \
        EXTI->IMR |= (1 << 17);                                                                     \
        EXTI->FTSR |= (1 << 17);  }                                                                 \
        NVIC_EnableIRQ(RTC_Alarm_IRQn);                                                             }

#define RTCAlarm_A_ChangeTime(DATE,HOUR,MINUTE,SECOND)                                             {\
        PWRUnlockWriteProtection;                                                                   \
        RTCUnlockProtection;                                                                        \
        StopAlarmA;                                                                                 \
        RTC->ALRMAR = 0;                                                                            \
        if(DATE <= 0 || DATE > 31)                                                                  \
        SetRTCAlarmADateDontCare;                                                                   \
        else SetRTCAlarmADateMask(DATE);                                                            \
        if(HOUR < 0 || HOUR > 23)                                                                   \
        SetRTCAlarmAHourDontCare;                                                                   \
        else SetRTCAlarmAHourMask(HOUR);                                                            \
        if(MINUTE < 0) SetRTCAlarmAMinuteDontCare;                                                  \
        else SetRTCAlarmAMinuteMask(MINUTE);                                                        \
        if(SECOND > 0) SetRTCAlarmASecondMask(SECOND);                                              \
        else SetRTCAlarmASecondDontCare;                                                            \
        StartAlarmA;                                                                                \
        RTCLockProtection;                                                                          \
        PWRLockWriteProtection;                                                                     }

#endif
#if(__configUSE_ALARM_B == 1)

/*!
*   Control definition time settings Alarm B
*/
#ifndef __configRTC_ALARM_B_DATE
#error Define __configRTC_ALARM_B_DATE parameter
#endif /*__configRTC_ALARM_B_DATE*/
#ifndef __configRTC_ALARM_B_HOURS
#error Define __configRTC_ALARM_B_HOURS parameter
#endif /*__configRTC_ALARM_B_HOURS*/
#ifndef __configRTC_ALARM_B_MINUTES
#error Define __configRTC_ALARM_B_MINUTES parameter
#endif /*__configRTC_ALARM_B_MINUTES*/
#ifndef __configRTC_ALARM_B_SECONDS
#error Define __configRTC_ALARM_B_SECONDS parameter
#endif /*__configRTC_ALARM_B_SECONDS*/

#define RTC_Alarm_B_Init                                                                           {\
        PWRUnlockWriteProtection;                                                                   \
        RTCUnlockProtection;                                                                        \
        StopAlarmB;                                                                                 \
        SetRTCAlarmBInterrupt;                                                                      \
        RTC->ALRMBR = 0;                                                                            \
        if(__configRTC_ALARM_B_DATE <= 0 || __configRTC_ALARM_B_DATE > 31)                          \
        SetRTCAlarmBDateDontCare;                                                                   \
        else SetRTCAlarmBDateMask(__configRTC_ALARM_B_DATE);                                        \
        if(__configRTC_ALARM_B_HOURS < 0 || __configRTC_ALARM_B_HOURS > 23)                         \
        SetRTCAlarmBHourDontCare;                                                                   \
        else SetRTCAlarmBHourMask(__configRTC_ALARM_B_HOURS);                                       \
        if(__configRTC_ALARM_B_MINUTES < 0) SetRTCAlarmBMinuteDontCare;                             \
        else SetRTCAlarmBMinuteMask(__configRTC_ALARM_B_MINUTES);                                   \
        if(__configRTC_ALARM_B_SECONDS > 0) SetRTCAlarmBSecondMask(__configRTC_ALARM_B_SECONDS);    \
        else SetRTCAlarmBSecondDontCare;                                                            \
        StartAlarmB;                                                                                \
        RTCLockProtection;                                                                          \
        PWRLockWriteProtection;                                                                     \
        if(((EXTI->IMR & EXTI_IMR_MR17) >> 17) == 0) {                                              \
        EXTI->IMR |= (1 << 17);                                                                     \
        EXTI->FTSR |= (1 << 17);  }                                                                 \
        NVIC_EnableIRQ(RTC_Alarm_IRQn);                                                             }

#define RTCAlarm_B_ChangeTime(DATE,HOUR,MINUTE,SECOND)                                             {\
        PWRUnlockWriteProtection;                                                                   \
        RTCUnlockProtection;                                                                        \
        StopAlarmB;                                                                                 \
        RTC->ALRMBR = 0;                                                                            \
        if(DATE <= 0 || DATE > 31)                                                                  \
        SetRTCAlarmBDateDontCare;                                                                   \
        else SetRTCAlarmBDateMask(DATE);                                                            \
        if(HOUR < 0 || HOUR > 23)                                                                   \
        SetRTCAlarmBHourDontCare;                                                                   \
        else SetRTCAlarmBHourMask(HOUR);                                                            \
        if(MINUTE < 0) SetRTCAlarmBMinuteDontCare;                                                  \
        else SetRTCAlarmBMinuteMask(MINUTE);                                                        \
        if(SECOND > 0) SetRTCAlarmBSecondMask(SECOND);                                              \
        else SetRTCAlarmBSecondDontCare;                                                            \
        StartAlarmB;                                                                                \
        RTCLockProtection;                                                                          \
        PWRLockWriteProtection;                                                                     }

#endif

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
#define StartAlarmA             (RTC->CR |= RTC_CR_ALRAE)
#define StartAlarmB             (RTC->CR |= RTC_CR_ALRBE)
#define SetRTCAlarmAInterrupt   (RTC->CR |= RTC_CR_ALRAIE)
#define SetRTCAlarmBInterrupt   (RTC->CR |= RTC_CR_ALRBIE)
#define RTCPassShadow           (RTC->CR |= RTC_CR_BYPSHAD)
#define RTCInitModeON           (RTC->ISR |= RTC_ISR_INIT)
#define RTCUnlockProtection     {\
        RTC->WPR = 0xCA;         \
        RTC->WPR = 0x53;         }
#define RTCAlarmAInitModeON     (RTC->ISR |= RTC_ISR_)
#define SetRTCAlarmADateDontCare        (RTC->ALRMAR |= RTC_ALRMAR_MSK4)
#define SetRTCAlarmAHourDontCare        (RTC->ALRMAR |= RTC_ALRMAR_MSK3)
#define SetRTCAlarmAMinuteDontCare      (RTC->ALRMAR |= RTC_ALRMAR_MSK2)
#define SetRTCAlarmASecondDontCare      (RTC->ALRMAR |= RTC_ALRMAR_MSK1)
#define SetRTCAlarmADateMask(DATE)      (RTC->ALRMAR |= ((DATE/10*16 + DATE%10) << 24))
#define SetRTCAlarmAHourMask(HOUR)      (RTC->ALRMAR |= ((HOUR/10*16 + HOUR%10) << 16))
#define SetRTCAlarmAMinuteMask(MINUTE)  (RTC->ALRMAR |= (((MINUTE/10*16) + MINUTE%10) << 8))
#define SetRTCAlarmASecondMask(SECOND)  (RTC->ALRMAR |= (SECOND/10*16 + SECOND%10))
#define SetRTCAlarmBDateMask            (RTC->ALRMBR |= RTC_ALRMBR_MSK4)
//---------------------------------------Reset state---------------------------------------------------//
#define StopAlarmA              (RTC->CR &= ~RTC_CR_ALRAE)
#define StopAlarmB              (RTC->CR &= ~RTC_CR_ALRBE)
#define RTCLockShadow           (RTC->CR &= ~RTC_CR_BYPSHAD)
#define RTCLockProtection       (RTC->WPR = 0xFF)
#define RTCInitModeOFF          (RTC->ISR &= ~RTC_ISR_INIT)
#define ResetRTCAlarmADateMask  (RTC->ALRMAR &= ~RTC_ALRMAR_MSK4)
#define ResetRTCAlarmBDateMask  (RTC->ALRMBR &= ~RTC_ALRMBR_MSK4)
#define ClearRTCAlarms                                    {\
        (RTC->ISR &= (~RTC_ISR_ALRAF | ~RTC_ISR_ALRBF));   \
        EXTI->PR = (1 << 17);                              }

#define AlarmAEvent         (((RTC->ISR & RTC_ISR_ALRAF) >> 8) == 1)
#define AlarmBEvent         (((RTC->ISR & RTC_ISR_ALRBF) >> 9) == 1)
#define RTCInitFlagEvent    (((RTC->ISR & RTC_ISR_INITF) >> 6) == 1)
struct {
    char Date[10];  //GOST P 7.0.97-2016
    char Time[8];   //ISO8601
    uint32_t Timestamp;
    char Alarm_A[20];
    char Alarm_B[20];
    uint32_t DR,TR,SSR;
}RTCStatus;

#define RTC_GetStatus                                                          {\
        RTC_GetTime;                                                            \
        RTCStatus.Time[0] = ((char)(((RTCStatus.TR >> 20) & 0x3) + 0x30));      \
        RTCStatus.Time[1] = ((char)(((RTCStatus.TR >> 16) & 0xF) + 0x30));      \
        RTCStatus.Time[2] = ':';                                                \
        RTCStatus.Time[3] = ((char)(((RTCStatus.TR >> 12) & 0x7) + 0x30));      \
        RTCStatus.Time[4] = ((char)(((RTCStatus.TR >> 8) & 0xF) + 0x30));       \
        RTCStatus.Time[5] = ':';                                                \
        RTCStatus.Time[6] = ((char)(((RTCStatus.TR >> 4) & 0x7) + 0x30));       \
        RTCStatus.Time[7] = ((char)(((RTCStatus.TR) & 0xF) + 0x30));            \
        RTCStatus.Date[0] = ((char)(((RTCStatus.DR >> 4) & 0x3) + 0x30));       \
        RTCStatus.Date[1] = ((char)(((RTCStatus.DR) & 0xF) + 0x30));            \
        RTCStatus.Date[2] = '.';                                                \
        RTCStatus.Date[3] = ((char)(((RTCStatus.DR >> 12) & 0x1) + 0x30));      \
        RTCStatus.Date[4] = ((char)(((RTCStatus.DR >> 8) & 0xF) + 0x30));       \
        RTCStatus.Date[5] = '.';                                                \
        RTCStatus.Date[6] = '2';                                                \
        RTCStatus.Date[7] = '0';                                                \
        RTCStatus.Date[8] = ((char)(((RTCStatus.DR >> 20) & 0xF) + 0x30));      \
        RTCStatus.Date[9] = ((char)(((RTCStatus.DR >> 16) & 0xF) + 0x30));      \
        RTCStatus.Alarm_A[0] = ((char)(((RTC->ALRMAR >> 20) & 0x3) + 0x30));    \
        RTCStatus.Alarm_A[1] = ((char)(((RTC->ALRMAR >> 16) & 0xF) + 0x30));    \
        RTCStatus.Alarm_A[2] = ':';                                             \
        RTCStatus.Alarm_A[3] = ((char)(((RTC->ALRMAR >> 12) & 0x7) + 0x30));    \
        RTCStatus.Alarm_A[4] = ((char)(((RTC->ALRMAR >> 8) & 0xF) + 0x30));     \
        RTCStatus.Alarm_A[5] = ':';                                             \
        RTCStatus.Alarm_A[6] = ((char)(((RTC->ALRMAR >> 4) & 0x7) + 0x30));     \
        RTCStatus.Alarm_A[7] = ((char)(((RTC->ALRMAR) & 0xF) + 0x30));          \
        RTCStatus.Alarm_A[8] = '/';                                             \
        RTCStatus.Alarm_A[9] = '/';                                             \
        RTCStatus.Alarm_A[10] = ((char)(((RTC->ALRMAR >> 28) & 0x3) + 0x30));   \
        RTCStatus.Alarm_A[11] = ((char)(((RTC->ALRMAR >> 24) & 0xF) + 0x30));   \
        RTCStatus.Alarm_A[12] = '.';                                            \
        RTCStatus.Alarm_A[13] = ((char)(((RTCStatus.DR >> 12) & 0x1) + 0x30));  \
        RTCStatus.Alarm_A[14] = ((char)(((RTCStatus.DR >> 8) & 0xF) + 0x30));   \
        RTCStatus.Alarm_A[15] = '.';                                            \
        RTCStatus.Alarm_A[16] = '2';                                            \
        RTCStatus.Alarm_A[17] = '0';                                            \
        RTCStatus.Alarm_A[18] = ((char)(((RTCStatus.DR >> 20) & 0xF) + 0x30));  \
        RTCStatus.Alarm_A[19] = ((char)(((RTCStatus.DR >> 16) & 0xF) + 0x30));  \
        RTCStatus.Alarm_B[0] = ((char)(((RTC->ALRMBR >> 20) & 0x3) + 0x30));    \
        RTCStatus.Alarm_B[1] = ((char)(((RTC->ALRMBR >> 16) & 0xF) + 0x30));    \
        RTCStatus.Alarm_B[2] = ':';                                             \
        RTCStatus.Alarm_B[3] = ((char)(((RTC->ALRMBR >> 12) & 0x7) + 0x30));    \
        RTCStatus.Alarm_B[4] = ((char)(((RTC->ALRMBR >> 8) & 0xF) + 0x30));     \
        RTCStatus.Alarm_B[5] = ':';                                             \
        RTCStatus.Alarm_B[6] = ((char)(((RTC->ALRMBR >> 4) & 0x7) + 0x30));     \
        RTCStatus.Alarm_B[7] = ((char)(((RTC->ALRMBR) & 0xF) + 0x30));          \
        RTCStatus.Alarm_B[8] = '/';                                             \
        RTCStatus.Alarm_B[9] = '/';                                             \
        RTCStatus.Alarm_B[10] = ((char)(((RTC->ALRMBR >> 28) & 0x3) + 0x30));   \
        RTCStatus.Alarm_B[11] = ((char)(((RTC->ALRMBR >> 24) & 0xF) + 0x30));   \
        RTCStatus.Alarm_B[12] = '.';                                            \
        RTCStatus.Alarm_B[13] = ((char)(((RTCStatus.DR >> 12) & 0x1) + 0x30));  \
        RTCStatus.Alarm_B[14] = ((char)(((RTCStatus.DR >> 8) & 0xF) + 0x30));   \
        RTCStatus.Alarm_B[15] = '.';                                            \
        RTCStatus.Alarm_B[16] = '2';                                            \
        RTCStatus.Alarm_B[17] = '0';                                            \
        RTCStatus.Alarm_B[18] = ((char)(((RTCStatus.DR >> 20) & 0xF) + 0x30));  \
        RTCStatus.Alarm_B[19] = ((char)(((RTCStatus.DR >> 16) & 0xF) + 0x30));  }

#define RTC_GetTime         {\
        RTCStatus.SSR = RTC->SSR;      \
        RTCStatus.TR = RTC->TR;        \
        RTCStatus.DR = RTC->DR;        }
#endif /*FIL_RTC*/
