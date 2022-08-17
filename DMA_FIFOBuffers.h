    /*!
    *   --------------------------------------------------------------------------
    *                       ///FIFO Buffers for DMA\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 14/07/2022 - last update version FIFO Buffers
    *
    *       @note [FIL:DMA] List FIFO Buffers for DMA
    */
#pragma once
#include "FilConfig.h"

#if(FIL_DMA == 1)
/*!
*   @note [FIL:DMA] This place configuration sizes of buffers
*
*/
#define ADC1_NUMB   1

#if defined(STM32F40_41xxx)
#define ADC2_NUMB   2
#define ADC3_NUMB   3
#endif /*STM32F40_41xxx*/

#define USART1RX_NUMB  8
#define USART1TX_NUMB  8
#define USART2RX_NUMB  8
#define USART2TX_NUMB  8

#if defined(STM32F40_41xxx)
#define USART3RX_NUMB  8
#define USART3TX_NUMB  8
#define UART4RX_NUMB   8
#define UART4TX_NUMB   8
#define UART5RX_NUMB   8
#define UART5TX_NUMB   8
#endif /*STM32F40_41xxx*/

#define USART6RX_NUMB  8
#define USART6TX_NUMB  8


/*!
*   @brief  ADC1_Data[ADC_NUMB] - buffer ADC1 Conversions
*   @list  ADC1_Data
*/
extern uint16_t ADC1_Data[ADC1_NUMB];

#if defined(STM32F40_41xxx)
/*!
*   @brief  ADC2_Data[ADC_NUMB] - buffer ADC2 Conversions
*   @list  ADC2_Data
*/
extern uint16_t ADC2_Data[ADC2_NUMB];

/*!
*   @brief  ADC3_Data[ADC_NUMB] - buffer ADC3 Conversions
*   @list  ADC3_Data
*/
extern uint16_t ADC3_Data[ADC3_NUMB];
#endif /*STM32F40_41xxx*/

/*!
*   @brief  USART1XX_Data[USART_NUMB] - UART/USART FIFO buffer RX/TX
*   @list  USART1XX_Data
*/
extern uint8_t USART1RX_Data[USART1RX_NUMB];
extern uint8_t USART1TX_Data[USART1TX_NUMB];

/*!
*   @brief  USART2XX_Data[USART_NUMB] - UART/USART FIFO buffer RX/TX
*   @list  USART2XX_Data
*/
extern uint8_t USART2RX_Data[USART2RX_NUMB];
extern uint8_t USART2TX_Data[USART2TX_NUMB];

#if defined(STM32F40_41xxx)
/*!
*   @brief  USART3XX_Data[USART_NUMB] - UART/USART FIFO buffer RX/TX
*   @list  USART3XX_Data
*/
extern uint8_t USART3RX_Data[USART3RX_NUMB];
extern uint8_t USART3TX_Data[USART3TX_NUMB];

/*!
*   @brief  UART4XX_Data[USART_NUMB] - UART/USART FIFO buffer RX/TX
*   @list  UART4XX_Data
*/
extern uint8_t UART4RX_Data[UART4RX_NUMB];
extern uint8_t UART4TX_Data[UART4TX_NUMB];

/*!
*   @brief  UART5XX_Data[USART_NUMB] - UART/USART FIFO buffer RX/TX
*   @list  UART5XX_Data
*/
extern uint8_t UART5RX_Data[UART5RX_NUMB];
extern uint8_t UART5TX_Data[UART5TX_NUMB];
#endif /*STM32F40_41xxx*/

/*!
*   @brief  USART6XX_Data[USART_NUMB] - UART/USART FIFO buffer RX/TX
*   @list  USART6XX_Data
*/
extern uint8_t USART6RX_Data[USART6RX_NUMB];
extern uint8_t USART6TX_Data[USART6TX_NUMB];

#endif /*FIL_DMA*/
