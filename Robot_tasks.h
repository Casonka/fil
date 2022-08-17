#pragma once
#include "FilConfig.h"
#if (FIL_FREERTOS == 1)

/*!
*   @brief vBlinkTest(void *pvParameters) - тест нормальной работы операционной системы FreeRTOS
*       @arg nothing
*       @note [FIL:FreeRTOS] Перед запуском ознакомиться с документацией на ОСРВ https://www.freertos.org/features.html
*/
xTaskHandle xBlinkHandle;
void vBlinkTest(void *pvParameters);

#endif /*FIL_FREERTOS*/
