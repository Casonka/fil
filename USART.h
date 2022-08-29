    /*!
    *   --------------------------------------------------------------------------
    *                       ///UART&USART initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 13/07/2022 - last update version UART/USART
    *
    *       @note [FIL:UART/USART] Configuration file UART/USART
    */
#pragma once
#include "FilConfig.h"

#if (FIL_USART == 1)

    /*!
    *   @brief USARTReceiverConfigure(USART,BAUD,RXInterrupt) - receiver config
    *       @arg USART - number of UART/USART interface
    *       @arg BAUD - speed of transmission in bauds
    *       @arg RXInterrupt - interrupt when RxE = 1
    */
    #define USARTReceiverConfigure(USART,BAUD,RXInterrupt){\
        ConfUSARTBaud(USART,BAUD);                         \
        SetUSARTReceiver(USART);                           \
        if(RXInterrupt == 1) SetUSARTRXInterrupt(USART);   \
        USARTStart(USART);                                 }

    /*!
    *   @brief USARTTransmitterConfigure(USART,BAUD,TXInterrupt) - transmitter config
    *       @arg USART - number of UART/USART interface
    *       @arg BAUD - speed of transmission in bauds
    *       @arg TXInterrupt - interrupt when TxE = 1
    */
    #define USARTTransmitterConfigure(USART,BAUD,TXInterrupt){\
        ConfUSARTBaud(USART,BAUD);                            \
        SetUSARTTransmitter(USART);                           \
        if(TXInterrupt == 1) SetUSARTRXInterrupt(USART);      \
        USARTStart(USART);                                    }

    /*!
    *   @brief USARTBothConfigure(USART,BAUD,TXInterrupt, RXInterrupt) - both config
    *       @arg USART - number of UART/USART interface
    *       @arg BAUD - speed of transmission in bauds
    *       @arg RXInterrupt - interrupt when RxE = 1
    *       @arg TXInterrupt - interrupt when TxE = 1
    */
    #define USARTBothConfigure(USART,BAUD,TXInterrupt, RXInterrupt){\
        ConfUSARTBaud(USART,BAUD);                                  \
        SetUSARTTransmitter(USART);                                 \
        SetUSARTReceiver(USART);                                    \
        if(RXInterrupt == 1) SetUSARTRXInterrupt(USART);            \
        if(TXInterrupt == 1) SetUSARTRXInterrupt(USART);            \
        USARTStart(USART);                                          }
//----------------------------------------Set state-------------------------------------------------------------------------------------------//
    #define USARTStart(USART)                   (USART->CR1 |= USART_CR1_UE)
    #define SetUSARTMbit(USART)                 (USART->CR1 |= USART_CR1_M)
    #define SetUSARTDMATransmitter(USART)       (USART->CR3 |= USART_CR3_DMAT)
    #define SetUSARTDMAReceiver(USART)          (USART->CR3 |= USART_CR3_DMAR)
    #define SetUSARTTransmitter(USART)          (USART->CR1 |= USART_CR1_TE)
    #define SetUSARTReceiver(USART)             (USART->CR1 |= USART_CR1_RE)
    #define SetUSARTRXInterrupt(USART)          (USART->CR1 |= USART_CR1_RXNEIE)
    #define SetUSARTTXInterrupt(USART)          (USART->CR1 |= USART_CR1_TCIE)
    #define SetUSARTOver8(USART)                (USART->CR1 |= USART_CR1_OVER8)
    #define SetUSART_DR(USART,Data)             (USART->DR = ((uint8_t)(Data)))
//-----------------------Simple commands reset and set the state------------------------------------------------------------------------------//
#if (FIL_CALC_USART == 0)
    #define ConfUSARTBaud(USART,BAUD)           {USART->BRR = ((uint32_t)((USART->BRR)&(~0xFFFF))|((uint16_t)(BAUD)));}
#elif (FIL_CALC_USART == 1)
    #define ConfUSARTBaud(USART,BAUD)           {USART->BRR = ((uint32_t)CalcUSARTBaudrate(USART, BAUD));}
#else
#error [FIL:UART/USART] Invalid arg Calc USART
#endif
    #define ConfUSARTStop(USART,STOP)           {USART->CR2 = ((uint32_t)((USART->CR2)&(~USART_CR2_STOP))|((uint16_t)(STOP)));}
//----------------------------------------Get state----------------------------------------------------//
    #define GetUSARTSR(USART)                        ((uint16_t)(USART->SR))
    #define CheckUSARTReceiver(USART)                (USART->SR & USART_SR_RXNE)
    #define CheckUSARTTransmiter(USART)              (USART->SR & USART_SR_TXE)
    #define CheckUSARTCompleteTransmission(USART)    (USART->SR & USART_SR_TC)
    #define GetUSARTData(USART)                      ((uint8_t)(USART->DR))
    #define CheckUSARTFramingError(USART)            (USART->SR & USART_SR_FE)
    #define CheckUSARTParityError(USART)             (USART->SR & USART_SR_PE)
#if (FIL_CALC_USART == 1)
//---------------------------------------Calculating---------------------------------------------------//

/*!
*   @brief CalcUSARTBaudrate(USART_TypeDef *USARTx, uint32_t BaudRate) - automatic calculating bauds
*       @arg USARTx - number of UART/USART
*       @arg BauRate - necessary baudrate
*       @return uint16_t baudrate
*/
uint16_t CalcUSARTBaudrate(USART_TypeDef *USARTx, uint32_t BaudRate);

#endif /*FIL_CALC_USART*/
#endif /*FIL_USART*/
