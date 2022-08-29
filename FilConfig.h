    /*!
    *   --------------------------------------------------------------------------
    *                ///Fast Initialization Library Configuration File\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska.
    *   @date 28/06/2022 - last update version FIL STM32
    *
    */

/*!
*   FIL STM32 Driver
*   @file <FilConfig.h>
*   @note [FIL:Configuration] This file include driver Fast Initialization Library(FIL) for STM32 controllers
*/

#pragma once
#include "main.h"
#include <stdbool.h>
#include "BoardSelection.h"

#define FIL_RCC                   __configUSE_RCC
#define FIL_GPIO                  __configUSE_GPIO
#define FIL_TIM                   __configUSE_TIM
#define FIL_USART                 __configUSE_USART
#define FIL_DMA                   __configUSE_DMA
#define FIL_I2C                   __configUSE_I2C
#define FIL_ADC                   __configUSE_ADC
#define FIL_EXTI                  __configUSE_EXTI
#define FIL_RTC                   __configUSE_RTC
#define FIL_Deprecated            __configUSE_DeprecatedFunctions   // !Deprecated

#define FIL_CALC_RCC              __configCALC_RCC
#define FIL_CALC_TIM              __configCALC_TIM
#define FIL_CALC_USART            __configCALC_USART
#define CALC_REGULATOR            __configCALC_Regulators
#define CALC_MATRIX               __configCALC_Matrix
#define CALC_KINEMATICS           __configCALC_Kinematics
#define CALC_I2C_SCANNING         __configCALC_I2C_SCANNING

/*!
*   OS Configuration
*/
#define FIL_FREERTOS              __configUSE_FREERTOS
#define FIL_FreeRTOS_Source       __configOS_SOURCE
/*!
*   Version control
*
*/
#define Allsupport     (STM32F401xx || STM32F40_41xxx || STM32F411xE)
#define support_High   (STM32F40_41xxx || STM32F411xE)
#if  !defined(Allsupport)
    #error Not supported on another devices
    #pragma message "Supported devices:"
    #pragma message "STM32F407VGT6, STM32F407VET6"
    #pragma message "STM32F401CCU6, STM32F411VET6"
#endif /*Supporting device securing end*/
/*!
*   @note [FIL:FreeRTOS] Include FreeRTOS in project
*/
#if(FIL_FREERTOS == 1)
    /*!
    *   @note [FIL:FreeRTOS] Настройка отвечает за подключение операционной системы в проект
    *   Содержит все файлы необходимые для работы многопоточного приложения
    *   Только для опытных пользователей
    */
    #include "FreeRTOS.h"       // main FreeRTOS kernel file
    #include "FreeRTOSConfig.h" // main configuration file
    #include "task.h"           //file for initialization tasks
    #include "queue.h"  /// работа с очередями
    #include "semphr.h" /// работа с отложенным прерыванием(семафорами)
    #include "croutine.h" /// работа с сопрограммами
    #include "timers.h" /// работа с программными таймерами
    #include "event_groups.h" // работа с группами событий
    #include "stream_buffer.h" // работа с потоками сообщений
    //-----------------------------------------------------------------
    // custom files
    #include "Robot_tasks.h"    // tasks list
    //-----------------------------------------------------------------
#endif /*FIL_FREERTOS*/

#if(FIL_RCC == 1)
    #include "RCC.h"
#elif(FIL_RCC > 1 || FIL_RCC < 0)
#error Invalid argument FIL_RCC
#endif /*FIL_RCC*/
#if(FIL_GPIO == 1)
    #include "GPIO.h"
#elif(FIL_GPIO > 1 || FIL_GPIO < 0)
#error Invalid argument FIL_GPIO
#endif /*FIL_GPIO*/
#if(FIL_TIM == 1)
    #include "TIM.h"
#elif(FIL_TIM > 1 || FIL_TIM < 0)
#error Invalid argument FIL_TIM
#endif /*FIL_TIM*/
#if(FIL_USART == 1)
    #include "USART.h"
#elif(FIL_USART > 1 || FIL_USART < 0)
#error Invalid argument FIL_USART
#endif /*FIL_USART*/
#if(FIL_DMA == 1)
    #include "DMA.h"
    #include "DMA_FIFOBuffers.h"
#elif(FIL_DMA > 1 || FIL_DMA < 0)
#error Invalid argument FIL_DMA
#endif /*FIL_DMA*/
#if(FIL_ADC == 1)
    #include "ADC.h"
#elif(FIL_ADC > 1 || FIL_ADC < 0)
#error Invalid argument FIL_ADC
#endif /*FIL_ADC*/
#if(FIL_I2C == 1)
    #include "I2C.h"
#elif(FIL_I2C > 1 || FIL_I2C < 0)
#error Invalid argument FIL_I2C
#endif /*FIL_I2C*/
#if(FIL_EXTI == 1)
    #include "EXTI.h"
#elif(FIL_EXTI > 1 || FIL_EXTI < 0)
#error Invalid argument FIL_EXTI
#endif /*FIL_EXTI*/
#if(CALC_MATRIX == 1)
    #include "Matrix.h"
#elif(CALC_MATRIX > 1 || CALC_MATRIX < 0)
#error Invalid argument CALC_MATRIX
#endif /*CALC_MATRIX*/
#if(CALC_REGULATOR == 1)
    #include "Regulators.h"
#elif(CALC_REGULATOR > 1 || CALC_REGULATOR < 0)
#error Invalid argument CALC_REGULATOR
#endif /*CALC_REGULATOR*/
#if(CALC_KINEMATICS == 1)
    #include "KINEMATICS.h"
#elif(CALC_KINEMATICS > 1 || CALC_KINEMATICS < 0)
#error Invalid argument CALC_KINEMATICS
#endif/*CALC_KINEMATICS*/
#if(FIL_RTC == 1)
    #include "RTC.h"
#elif(FIL_RTC > 1 || FIL_RTC < 0)
#error Invalid argument FIL_RTC
#endif/*FIL_RTC*/
