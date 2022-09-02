    /*!
    *   --------------------------------------------------------------------------
    *                       ///I2C Source file\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 15/08/2022 - last update version I2C
    *
    *       @note [FIL:I2C] I2C Source file.
    */
#include "I2C.h"
//---------------------------------------------------------//
//----------------------I2C Interrupts---------------------//
//---------------------------------------------------------//
#if(FIL_I2C == 1)
void I2C1_EV_IRQHandler(void)
{

}

void I2C2_EV_IRQHandler(void)
{

}

void I2C3_EV_IRQHandler(void)
{

}

void I2C1_ER_IRQHandler(void)
{

}

void I2C2_ER_IRQHandler(void)
{

}

void I2C3_ER_IRQHandler(void)
{

}

static uint32_t I2C_timeout;
#ifndef __configI2C_TIMEOUT
    #define __configI2C_TIMEOUT         (5000)
#endif/*__configI2C_TIMEOUT*/
/*!
*   @brief I2C_ClearAllStats(I2C_TypeDef* I2Cx) - Clear all status flags and parameters
*       @arg I2Cx - number of target I2C
*           @note [FIL:I2C] Frequency and rise time current bus will not be cleared
*/
void I2C_ClearAllStats(I2C_TypeDef* I2Cx)
{
    (void)I2Cx->SR1;
    I2Cx->SR1 = 0;
    (void)I2Cx->SR2;
    I2Cx->SR2 = 0;
}

/*!
*   @brief I2C_MemoryWriteSingle(I2C_TypeDef* I2Cx, uint8_t address, uint8_t Register, uint8_t Value)
*               Write Value to Slave's Register which have address
*   @arg address - Device address
*   @arg Register - Slave's internal register
*   @arg Value - writing value to Register
*
*/
uint8_t I2C_MemoryWriteSingle(I2C_TypeDef* I2Cx, uint8_t address, uint8_t Register, uint8_t Value)
{
    I2C_ClearAllStats(I2Cx);

    I2CStart(I2Cx);
    SetI2CAsk(I2Cx);
//-------------------Wait SB-------------------------//
    I2C_timeout = __configI2C_TIMEOUT;
    while(!I2CStartBitEvent(I2Cx))
    {
        if(--I2C_timeout == 0x00)
        {
            return 0x00;
        }
    }
//---------------------------------------------------//
    I2CSendData(I2Cx,address,1);
//-------------------Wait TXe&ADDR-------------------//
    I2C_timeout = __configI2C_TIMEOUT;
    while(!I2CAddressSentEvent(I2Cx) || !I2CDataEmptyEvent(I2Cx))
    {
        if(--I2C_timeout == 0x00)
        {
            return 0x00;
        }
    }
//---------------------------------------------------//
    I2C_ClearAllStats(I2Cx);
    I2CSendCommand(I2Cx,Register);
//----------------Wait TXe---------------------------//
    I2C_timeout = __configI2C_TIMEOUT;
    while(!I2CDataEmptyEvent(I2Cx))
    {
        if (--I2C_timeout == 0x00)
        {
            return 0x00;
        }
    }
//---------------------------------------------------//
    I2CSendCommand(I2Cx,Value);
//----------------Wait TXe&BTF-----------------------//
    I2C_timeout = __configI2C_TIMEOUT;
    while(!I2CDataEmptyEvent(I2Cx) || !I2CByteTranferedEvent(I2Cx))
    {
        if (--I2C_timeout == 0x00)
        {
            return 0x00;
        }
    }
//---------------------------------------------------//
    I2CStop(I2Cx);
    ResetI2CAsk(I2Cx);
    return Value;
}

/*!
*   @brief I2C_MemoryReadMultiple(I2C_TypeDef* I2Cx, uint8_t address, uint8_t Register, uint8_t* Bus, uint16_t length)
*               Read some values from slave and puts in Bus buffer
*   @arg I2Cx - number of I2C interface
*   @arg address - Device address
*   @arg Register - Slave's internal register
*   @arg Bus - Storage buffer pointer
*   @arg length - number of parsing values
*       @attention Bus buffer pointer necessary puts with saving value type
*           Example: uint8_t buffer need to put like as I2C_MemoryWriteSingle(I2Cx,address,Register,(uint8_t *)buffer,length);
*   @return Number of success transfered to STM32 bytes
*/
uint8_t I2C_MemoryReadMultiple(I2C_TypeDef* I2Cx, uint8_t address, uint8_t Register, uint8_t* Bus, uint16_t length)
{
    I2C_ClearAllStats(I2Cx);

    I2CStart(I2Cx);
    SetI2CAsk(I2Cx);
//-------------------Wait SB-------------------------//
    I2C_timeout = __configI2C_TIMEOUT;
    while(!I2CStartBitEvent(I2Cx))
    {
        if(--I2C_timeout == 0x00)
        {
            return 0x00;
        }
    }
//---------------------------------------------------//
    I2CSendData(I2Cx,address,1);
//-------------------Wait TXe&ADDR-------------------//
    I2C_timeout = __configI2C_TIMEOUT;
    while(!I2CAddressSentEvent(I2Cx) || !I2CDataEmptyEvent(I2Cx))
    {
        if(--I2C_timeout == 0x00)
        {
            return 0x00;
        }
    }
//---------------------------------------------------//
    I2C_ClearAllStats(I2Cx);

    I2CSendCommand(I2Cx,Register);

    I2CStart(I2Cx);
//-------------------Wait SB-------------------------//
    I2C_timeout = __configI2C_TIMEOUT;
    while(!I2CStartBitEvent(I2Cx))
    {
        if(--I2C_timeout == 0x00)
        {
            return 0x00;
        }
    }
//---------------------------------------------------//
    I2CSendData(I2Cx,address,0);
//-------------------Wait RXNe&ADDR------------------//
    I2C_timeout = __configI2C_TIMEOUT;
    I2C_ClearAllStats(I2Cx);
    while(!I2CAddressSentEvent(I2Cx))
    {
        if(--I2C_timeout == 0x00)
        {
            return 0x00;
        }
    }
    (void)I2Cx->SR1;
    (void)I2Cx->SR2;

    uint16_t SuccessRead = 0;
    for(int i = 0; i <= length; i++)
    {

        if(i == (length - 1)) ResetI2CAsk(I2Cx);
        I2C_timeout = __configI2C_TIMEOUT;
        while(!I2CDataNotEmptyEvent(I2Cx))
        {
            if(--I2C_timeout == 0x00)
            {
                break;
            }
        }
        if(!I2CDataNotEmptyEvent(I2Cx)) continue;
        *Bus++ = I2Cx->DR;
        SuccessRead++;
    }
    I2CStop(I2Cx);
//---------------------------------------------------//
    return SuccessRead;
}

/*!
*   @brief I2C_MemoryReadSingle(I2C_TypeDef* I2Cx, uint8_t address, uint8_t Register)
*               Read one byte and return this value
*   @arg I2Cx - number of I2C interface
*   @arg address - Device address
*   @arg Register - Slave's internal register
*   @return Value that stored in register
*/
uint8_t I2C_MemoryReadSingle(I2C_TypeDef* I2Cx, uint8_t address, uint8_t Register)
{
    uint8_t Bus;
    I2C_ClearAllStats(I2Cx);

    I2CStart(I2Cx);
    SetI2CAsk(I2Cx);
//-------------------Wait SB-------------------------//
    I2C_timeout = __configI2C_TIMEOUT;
    while(!I2CStartBitEvent(I2Cx))
    {
        if(--I2C_timeout == 0x00)
        {
            return 0x00;
        }
    }
//---------------------------------------------------//
    I2CSendData(I2Cx,address,1);
//-------------------Wait TXe&ADDR-------------------//
    I2C_timeout = __configI2C_TIMEOUT;
    while(!I2CAddressSentEvent(I2Cx) || !I2CDataEmptyEvent(I2Cx))
    {
        if(--I2C_timeout == 0x00)
        {
            return 0x00;
        }
    }
//---------------------------------------------------//
    I2C_ClearAllStats(I2Cx);

    I2CSendCommand(I2Cx,Register);

    I2CStart(I2Cx);
//-------------------Wait SB-------------------------//
    I2C_timeout = __configI2C_TIMEOUT;
    while(!I2CStartBitEvent(I2Cx))
    {
        if(--I2C_timeout == 0x00)
        {
            return 0x00;
        }
    }
//---------------------------------------------------//
    I2CSendData(I2Cx,address,0);
//-------------------Wait RXNe&ADDR------------------//
    I2C_timeout = __configI2C_TIMEOUT;
    I2C_ClearAllStats(I2Cx);
    while(!I2CAddressSentEvent(I2Cx))
    {
        if(--I2C_timeout == 0x00)
        {
            return 0x00;
        }
    }
    (void)I2Cx->SR1;
    (void)I2Cx->SR2;
    I2C_timeout = __configI2C_TIMEOUT;
    while(!I2CDataNotEmptyEvent(I2Cx))
    {
        if(--I2C_timeout == 0x00)
        {
            return 0x00;
        }
    }
//---------------------------------------------------//

    ResetI2CAsk(I2Cx);
    I2CStop(I2Cx);
    Bus = I2Cx->DR;

    return Bus;
}

/*!
*   @brief I2C_SingleSend(I2C_TypeDef* I2Cx, uint8_t Byte, bool IsWrite) - Single Write on Bus IIC
*       @arg I2Cx - number of target I2C
*       @arg Byte - Sending value
*       @arg IsWrite - necessary Write/Read bytes on next transfer:
*                       0 - Reads next transfer
*                       1 - Write by slave on next transfer
*/
bool I2C_SingleSend(I2C_TypeDef* I2Cx, uint8_t Byte, bool IsWrite)
{
    I2C_timeout = __configI2C_TIMEOUT;
//----------------Wait TXe-----------------------//
    while(!I2CDataEmptyEvent(I2Cx))
    {
        if (--I2C_timeout == 0x00)
        {
            return false;
        }
    }
//------------------------------------------------//
    int direction = (IsWrite) ? 1 : 0;
    I2CSendData(I2Cx,Byte,direction);
return true;
}

/*!
*   @brief I2C_SingleSend(I2C_TypeDef* I2Cx, uint8_t *bufBytes) - Multiple Write on Bus IIC
*       @arg I2Cx - number of target I2C
*       @arg bufBytes - Sending buffer of values
*/
uint16_t I2C_MultipleSend(I2C_TypeDef* I2Cx, uint8_t *bufBytes)
{
    uint16_t SuccessTransfer = 0;
    for(int i = 0; i < sizeof(bufBytes); i++)
    {
        if(i == (sizeof(bufBytes) - 1)) ResetI2CAsk(I2Cx);
        I2C_timeout = __configI2C_TIMEOUT;
        //----------------Wait TXNe-----------------------//
        while(!I2CDataEmptyEvent(I2Cx))
        {
            if (--I2C_timeout == 0x00)
            {
                return false;
            }
        }
        //------------------------------------------------//
        I2CSendData(I2Cx,bufBytes[i],1);
        SuccessTransfer++;
    }

return SuccessTransfer;
}

uint8_t I2C_SingleRead(I2C_TypeDef* I2Cx)
{
    uint8_t SuccessRead = 0;

    while(!I2CDataNotEmptyEvent(I2Cx)) {}
    SuccessRead = I2Cx->DR;

    I2CStop(I2Cx);
return SuccessRead;
}

uint16_t I2C_MultipleRead(I2C_TypeDef* I2Cx, uint8_t *bufBytes)
{
    uint16_t SuccessRead = sizeof(bufBytes);

    for(int i = 0; i < 14; i++)
    {
        if(i == (sizeof(bufBytes) - 1)) ResetI2CAsk(I2Cx);
        while(!I2CDataNotEmptyEvent(I2Cx))  {}
        bufBytes[i] = I2Cx->DR;
        SuccessRead++;
    }
    I2CStop(I2Cx);
return SuccessRead;
}

/*!
*   @brief I2C_RestoreConnection(I2C_TypeDef* I2Cx)
*               Restore and reset connection for selected bus I2C
*   @arg I2Cx - number of I2C interface
*       @attention Function will generate STOP bit manually for safe reset
*                       without power reset STM32
*   @return NONE
*/
void I2C_RestoreConnection(I2C_TypeDef* I2Cx)
{
    RCC->APB1ENR &= ~RCC_APB1ENR_I2C1EN;
    __ASM volatile ("dsb 0xF":::"memory");
    RCC->APB1RSTR |= RCC_APB1RSTR_I2C1RST;
    RCC->APB1RSTR &= ~RCC_APB1RSTR_I2C1RST;
    __ASM volatile ("dsb 0xF":::"memory");
    GPIOConfPin(I2C_SDA_PIN, GENERAL, OPEN_DRAIN, LOW_S, NO_PULL_UP);
    GPIOConfPin(I2C_SCL_PIN, GENERAL, OPEN_DRAIN, LOW_S, NO_PULL_UP);
    SetPin(I2C_SCL_PIN);
    SetPin(I2C_SDA_PIN);
    for(int i = 0; i < 20; i++)
    {
        delay_ms(3);
        if(PinVal(I2C_SDA_PIN)) break;
        ResetPin(I2C_SCL_PIN);
        delay_ms(3);
        SetPin(I2C_SCL_PIN);
    }
    ResetPin(I2C_SDA_PIN);
    delay_ms(2);
    SetPin(I2C_SCL_PIN);
    delay_ms(1);
    SetPin(I2C_SDA_PIN);
    delay_ms(3);

    GPIOConfPin(I2C_SDA_PIN, ALTERNATE, OPEN_DRAIN, FAST_S, NO_PULL_UP);
    GPIOConfPin(I2C_SCL_PIN, ALTERNATE, OPEN_DRAIN, FAST_S, NO_PULL_UP);
    SetI2C1;
}

#if(CALC_I2C_SCANNING == 1)
uint8_t I2CFindDevices(I2C_TypeDef* I2Cx)
{
    uint8_t IsFind = 0;
    uint8_t address = 0x01;
    uint8_t devices = 0;
    while(address <= 0x7F)
    {
        SetI2CPeriphDisable(I2Cx);

        I2Cx->CR1 = 0;
        I2Cx->DR = 0;
        (void)I2Cx->SR1;
        I2Cx->SR1 = 0;
        (void)I2Cx->SR2;
        I2Cx->SR2 = 0;

        SetI2CPeriphEnable(I2Cx);

        I2CStart(I2Cx);

        I2C_timeout = __configI2C_TIMEOUT;
        while (!I2CStartBitEvent(I2Cx)) {
            if (--I2C_timeout == 0x00)
            {
                address++;
                break;
            }
        }
        if(!(I2Cx->SR1 & I2C_SR1_SB)) continue;


        if ((I2Cx->CR1 & I2C_CR1_ACK) == 0) SetI2CAsk(I2Cx);

        I2Cx->DR = (address << 1) & ~I2C_OAR1_ADD0;

        I2C_timeout = __configI2C_TIMEOUT;
        while(!I2CAddressSentEvent(I2Cx))
        {
            if(--I2C_timeout == 0x00) {
                address++;
                break;
            }
        }
        if(!(I2Cx->SR1 & I2C_SR1_ADDR)) continue;

        if(devices > sizeof(I2CStatus.Devices)) break;
        I2CStatus.Devices[devices++] = address;
        IsFind++;
        address++;
    }
return IsFind;
}
#endif /*CALC_I2C_SCANNING*/
#endif /*FIL_I2C*/
