#include "USART.h"

#if(FIL_USART == 1)
uint16_t CalcUSARTBaudrate(USART_TypeDef *USARTx, uint32_t BaudRate)
{
    uint32_t BAUD, REGISTER = 0;
    CalcRCCClocks();
#if defined(STM32F40_41xxx) /*--------------STM32F407------------------*/
    if( USARTx == USART2 || USARTx == USART3 || USARTx == USART4 || USARTx == USART5)
    {
        BAUD = Clocks.CurrentAPB1;
    }
    else if(USARTx == USART1 || USARTx == USART6)
    {
        BAUD = Clocks.CurrentAPB2;
    }
    else return 0;
#elif defined (STM32F401xx)
    if( USARTx == USART2)
    {
        BAUD = Clocks.CurrentAPB1;
    }
    else if(USARTx == USART1 || USARTx == USART6)
    {
        BAUD = Clocks.CurrentAPB2;
    }
    else return 0;
#else
#error Invalid model STM32
#endif
    REGISTER = ((uint32_t)(BAUD + (BaudRate >> 1)));
    REGISTER /= BaudRate;
    return REGISTER;
}
#endif /*FIL_USART*/
