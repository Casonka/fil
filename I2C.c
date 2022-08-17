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

/*!
*   @brief I2C_ClearAllStats(I2C_TypeDef* I2Cx) - Clear all active flags and parameters
*       @arg I2Cx - number of target I2C
*           @note [FIL:I2C] Frequency and rise time current bus will not be cleared
*/
void I2C_ClearAllStats(I2C_TypeDef* I2Cx)
{
    I2Cx->CR1 = 0;
    I2Cx->DR = 0;
    (void)I2Cx->SR1;
    I2Cx->SR1 = 0;
    (void)I2Cx->SR2;
    I2Cx->SR2 = 0;
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
//----------------Wait TXNe-----------------------//
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
    uint16_t SuccessRead = 0;


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
