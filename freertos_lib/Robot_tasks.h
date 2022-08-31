#pragma once
#include "BoardSelection.h"
#include "FilConfig.h"

#if (FIL_FREERTOS == 1)
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
/*!
*   @brief vBlinkTest(void *pvParameters) - тест нормальной работы операционной системы FreeRTOS
*       @arg nothing
*       @note [FIL:FreeRTOS] Перед запуском ознакомиться с документацией на ОСРВ https://www.freertos.org/features.html
*/
xTaskHandle xBlinkHandle;
void vBlinkTest(void *pvParameters);

#endif /*FIL_FREERTOS*/
