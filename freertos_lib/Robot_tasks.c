#include "Robot_tasks.h"

void vApplicationTickHook(void)
{
    /*!
    *   @brief vApplicationIdleHook(void) - функция выполняется после каждого завершения любой задачи
    *   @arg nothing - функция ничего не получает и ничего не возвращает
    */

}

void vApplicationIdleHook(void)
{
    /*!
    *   @brief vApplicationTickHook(void) - функция бездействия, выполняется когда процессорное время ничем не занято
    *   @arg nothing - функция ничего не получает и ничего не возвращает
    */
}

void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{
/*!
*   @brief vApplicationIdleHook(void) - функция переполнения, выполняется когда стек задачи переполнился
*   @arg xTask - дескриптор задачи, pcTaskName - название задачи
*
*/
}
void vApplicationMallocFailedHook( void )
{

}



void vBlinkTest(void *pvParameters)
{

    for(;;)
    {

    }
vTaskDelete(NULL);
}

#endif /*FIL_FREERTOS*/
