    /*!
    *   --------------------------------------------------------------------------
    *                       ///I2C initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska
    *   @date 15/08/2022 - last update version I2C
    *
    *       @note [FIL:I2C] Configuration file I2C
    */
#ifndef INCLUDED_I2C
#define INCLUDED_I2C

#pragma once
#include "FilConfig.h"

#if(FIL_I2C == 1)

    /*!
    *   @brief I2CSimpleConfigure(I2C,SPEED) - configuration I2C without adding addresses
    *       @arg I2C - number of I2C interface
    *       @arg SPEED - speed mode interface (SLOW or FAST)
    *           @list I2C_Slow - slow mode I2C
    *                 I2C_Fast - fast mode I2C
    */
    #define I2CSimpleConfigure(I2C, SPEED)                         {\
        SetI2CPeriphDisable(I2C);                                   \
        ConfI2CFreq(I2C,I2CDefaultFREQ);                            \
        ConfI2CCCR(I2C, SPEED);                                     \
        if(SPEED == I2C_Slow) ConfI2CTrise(I2C,RiseTimeDefaultSM);  \
        if(SPEED == I2C_Fast) ConfI2CTrise(I2C,RiseTimeDefaultFM);  \
        SetI2CPeriphEnable(I2C);                                    }

    /*!
    *   @brief I2CMasterConfigure(I2C,SPEED, ADDRESS) - configuration I2C in master mode
    *       @arg I2C - number of I2C interface
    *       @arg SPEED - speed mode interface (SLOW or FAST)
    *           @list I2C_Slow - slow mode I2C
    *                 I2C_Fast - fast mode I2C
    *       @arg ADDRESS - Own address on bus I2C
    */
    #define I2CMasterConfigure(I2C, SPEED, ADDRESS)                {\
        ConfI2CFreq(I2C,I2CDefaultFREQ);                            \
        ConfI2CCCR(I2C, SPEED);                                     \
        SetI2CPeriphDisable(I2C);                                   \
        if(SPEED == I2C_Slow) { SetI2CMasterModeSlow(I2C);          \
                               ConfI2CTrise(I2C,RiseTimeDefaultSM);}\
        if(SPEED == I2C_Fast) {ConfI2CTrise(I2C,RiseTimeDefaultFM); \
                              SetI2CMasterModeFast(I2C);}           \
        SetI2CPeriphEnable(I2C);                                    \
        ConfI2CAddress(I2C, ADDRESS);                               }

    /*!
    *   @brief I2CSlaveConfigure() -
    *       @arg
    *       @arg
    *       @arg
    *       @arg
    */
#define I2CSlaveConfigure(I2C, SPEED, ADDRESS)

//-----------------------Simple commands reset and set the state-------------------------------------------------------------------------------------------------------------//
#define I2CDefaultFREQ      ((uint16_t)(0x2A))  // 42MHz -> APB1 bus

#define ConfI2CFreq(I2C,FREQ)         { I2C->CR2 = ((uint32_t)(I2C->CR2 & ((uint32_t)(~I2C_CR2_FREQ))) | ((uint32_t)FREQ));}

#define RiseTimeDefaultSM   ((uint16_t)(0x34))
#define RiseTimeDefaultFM   ((uint16_t)(0x12))
#define ConfI2CTrise(I2C,vTRISE)       { I2C->TRISE = ((uint32_t)(I2C->TRISE & ((uint32_t)(~I2C_TRISE_TRISE))) | ((uint32_t)vTRISE));}

#define ConfI2CAddress(I2C, ADDRESS)  { I2C->OAR1 = ((uint32_t)(I2C->OAR1 & ((uint32_t)(~I2C_OAR1_ADD1_7))) | ((uint32_t)(ADDRESS << 1)));}

#define I2C_Slow            (420)
#define I2C_Fast            (105)
#define ConfI2CCCR(I2C,SPEED)           { I2C->CCR = ((uint32_t)(I2C->CCR & ((uint32_t)(~I2C_CCR_CCR))) | ((uint32_t)SPEED));}

//----------------------------------------Set state----------------------------------------------------//
#define SetI2CMasterModeFast(I2C) { I2C->CCR |= I2C_CCR_FS;}
#define SetI2CPeriphEnable(I2C)   { I2C->CR1 |= I2C_CR1_PE;}
#define I2CStart(I2C)             { I2C->CR1 |= I2C_CR1_START;}
#define I2CStop(I2C)              { I2C->CR1 |= I2C_CR1_STOP;}
#define SetI2CAsk(I2C)            { I2C->CR1 |= I2C_CR1_ACK;}
#define I2CSendData(I2C,DATA,DIR) (DIR == 1) ? (I2C->DR = ((DATA << 1) & ~I2C_OAR1_ADD0)) : (I2C->DR = ((DATA << 1) | I2C_OAR1_ADD0))
#define I2CSendCommand(I2C,DATA)  (I2C->DR = DATA)
#define I2C_Receive(I2C,Buf)      (Buf = I2C->DR)
//---------------------------------------Reset state---------------------------------------------------//
#define SetI2CMasterModeSlow(I2C) (I2C->CCR &= (~I2C_CCR_FS))
#define SetI2CPeriphDisable(I2C)  (I2C->CR1 &= (~I2C_CR1_PE))
#define ResetI2CAsk(I2C)          (I2C->CR1 &= ~I2C_CR1_ACK)
#define ResetI2CSR1(I2C)          ((void)(I2C->SR1))
#define ResetI2CSR2(I2C)          ((void)(I2C->SR2))
#define ResetI2CData(I2C)         (I2C->DR = 0)
#define ResetI2CCR1(I2C)          (I2C->CR1 = 0)
//---------------------------------------Status flags---------------------------------------------------//
#define I2CPeriphEnableEvent(I2C)      ((I2C->CR1 & I2C_CR1_PE) == 1)
#define I2CBusyEvent(I2C)              (((I2C->SR2 & I2C_SR2_BUSY) >> 1) == 1)
#define I2CStartBitEvent(I2C)          ((I2C->SR1 & I2C_SR1_SB) == 1)
#define I2CAddressSentEvent(I2C)       (((I2C->SR1 & I2C_SR1_ADDR) >> 1) == 1)
#define I2CMasterModeEvent(I2C)        ((I2C->SR2 & I2C_SR2_MSL) == 1)
#define I2CDataEmptyEvent(I2C)         (((I2C->SR1 & I2C_SR1_TXE) >> 7) == 1)
#define I2CDataNotEmptyEvent(I2C)      (((I2C->SR1 & I2C_SR1_RXNE) >> 6) == 1)
#define I2CByteTranferedEvent(I2C)     (((I2C->SR1 & I2C_SR1_BTF) >> 2) == 1)

#ifndef __configI2C_TIMEOUT
#define __configI2C_TIMEOUT					10000
#endif /*__configI2C_TIMEOUT*/

/*!
*   @brief I2C_ClearAllStats(I2C_TypeDef* I2Cx) - Clear all active flags and parameters
*       @arg I2Cx - number of target I2C
*           @note [FIL:I2C] Frequency and rise time current bus will not be cleared
*/
void I2C_ClearAllStats(I2C_TypeDef* I2Cx);

uint8_t I2C_MemoryWriteSingle(I2C_TypeDef* I2Cx, uint8_t address, uint8_t Register, uint8_t Value);
uint8_t I2C_MemoryReadSingle(I2C_TypeDef* I2Cx, uint8_t address, uint8_t Register);
uint8_t I2C_MemoryReadMultiple(I2C_TypeDef* I2Cx, uint8_t address, uint8_t Register, uint8_t* Bus, uint16_t length);
/*!
*   @brief I2C_SingleSend(I2C_TypeDef* I2Cx, uint8_t Byte, bool IsWrite) - Single Write on Bus IIC
*       @arg I2Cx - number of target I2C
*       @arg Byte - Sending value
*       @arg IsWrite - necessary Write/Read bytes on next transfer:
*                       0 - Reads next transfer
*                       1 - Write by slave on next transfer
*/
bool I2C_SingleSend(I2C_TypeDef* I2Cx, uint8_t Byte, bool IsWrite);

/*!
*   @brief I2C_MultipleSend(I2C_TypeDef* I2Cx, uint8_t *bufBytes) - Multiple Write on Bus IIC
*       @arg I2Cx - number of target I2C
*       @arg bufBytes - Sending buffer of values
*/
uint16_t I2C_MultipleSend(I2C_TypeDef* I2Cx, uint8_t *bufBytes);

/*!
*   @brief I2C_SingleRead(I2C_TypeDef* I2Cx) - Single read data from I2C bus
*       @arg I2Cx - number of I2C
*/
uint8_t I2C_SingleRead(I2C_TypeDef* I2Cx);

/*!
*   @brief I2C_MultipleRead(I2C_TypeDef* I2Cx, uint8_t *bufBytes) - Multiple Read on Bus IIC
*       @arg I2Cx - number of target I2C
*       @arg bufBytes - Sending buffer of values
*       @return success received bytes
*/
uint16_t I2C_MultipleRead(I2C_TypeDef* I2Cx, uint8_t *bufBytes);
#if(CALC_I2C_SCANNING == 1)
    #if(__configI2C_FindListSize > 0 )
    struct
    {
        uint16_t Devices[__configI2C_FindListSize];
    }I2CStatus;

    uint8_t I2CFindDevices(I2C_TypeDef* I2Cx);
    #endif /*__configI2C_FindListSize*/
#endif /*CALC_I2C_SCANNING*/
#endif /*FIL_I2C*/
#endif /*INCLUDED_I2C*/
