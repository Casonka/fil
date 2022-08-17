    /*!
    *   --------------------------------------------------------------------------
    *                       ///DMA initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Caska, Evgeny Garanin
    *   @date 15/07/2022 - last update version DMA
    *
    *       @note [FIL:DMA] Configuration file DMA
    */
#pragma once
#include "FilConfig.h"

#if (FIL_DMA == 1)

//----------------------------------------DMA Priority---------------------------------------------------//
    #define LOW_P       0
    #define MEDIUM_P    1
    #define HIGH_P      2
    #define VeryHigh_P  3
//----------------------------------------DMA Memory&Peripheral Size-------------------------------------//
    #define BYTE        0   //uint8_t
    #define HALFWORD    1   //uint16_t
    #define WORD        2   //uint32_t
//----------------------------------------DMA Transfer direction-----------------------------------------//
    #define PeripheralToMemory  0
    #define MemoryToPeripheral  1
    #define MemoryToMemory      2
//----------------------------------------DMA Functions--------------------------------------------------//
#if defined(STM32F40_41xxx)

        /*!
        *   @brief DMAConnectTOADC(EVENT,PRIORITY, MEMORY, TXINTERRUPT) -> Connect DMA to ADC
        *       @arg EVENT - ADC Event
        *       @arg PRIORITY - Priority of target channel
        *       @arg MEMORY - Buffer address for storing values
        *       @arg TXINTERRUPT - Interrupt selection mode: 0.5 - half transferred interrupt
        *                                                    1 - transferred complete interrupt
        *                                                    2 - transferred error interrupt
        *       @version STM32F40_41xxx
        */
    #define ConnectADCTODMA(EVENT,PRIORITY, MEMORY, TXINTERRUPT)             {\
                    SetDMAChannel(DMA2,EVENT);                                \
                    if(EVENT == ADC1Req) SetDMAPAR(DMA2,ADC1Req,(&ADC1->DR)); \
                    if(EVENT == ADC2Req) SetDMAPAR(DMA2,ADC2Req,(&ADC2->DR)); \
                    if(EVENT == ADC3Req) SetDMAPAR(DMA2,ADC3Req,(&ADC3->DR)); \
                    SetDMAMEMORY0(DMA2,EVENT,(&MEMORY));                      \
                    ClearDMADir(DMA2,EVENT);                                  \
                    SetDMANDTR(DMA2,EVENT,ADC1_NUMB);                         \
                    ClearDMAPinc(DMA2,EVENT);                                 \
                    SetDMAMinc(DMA2,EVENT);                                   \
                    SetDMACirc(DMA2,EVENT);                                   \
                    SetDMAPsize(DMA2,EVENT,HALFWORD);                         \
                    SetDMAMsize(DMA2,EVENT,HALFWORD);                         \
                    SetDMAPriority(DMA2,EVENT,PRIORITY);                      \
                    if(TXINTERRUPT == 1)   SetDMATransferIT(DMA2,EVENT);      \
                    if(TXINTERRUPT == 0.5) SetDMAHFTransferIT(DMA2,EVENT);    \
                    if(TXINTERRUPT == 2)   SetDMATransferErrIT(DMA2,EVENT);   \
                    DMAStart(DMA2,EVENT);                                     }

        /*!
        *   @brief DMAConnectTOUSART(EVENT, PRIORITY, MEMORY, TXINTERRUPT) -> Connect DMA to UART/USART
        *       @arg DMA - Number of DMA
        *       @arg EVENT - UART/USART Event
        *       @arg PRIORITY - Priority of target channel
        *       @arg MEMORY - Buffer address for storing values
        *       @arg TXINTERRUPT - Interrupt selection mode: 0.5 - half transferred interrupt
        *                                                    1 - transferred complete interrupt
        *                                                    2 - transferred error interrupt
        *       @version STM32F40_41xxx
        */
    #define ConnectUSARTTODMA(DMA,EVENT, PRIORITY, MEMORY, TXINTERRUPT)                                            {\
                    SetDMAChannel(DMA,EVENT);                                                                       \
                    if(EVENT == USART1RXReq || EVENT == USART1TXReq) SetDMAPAR(DMA,EVENT,(&USART1->DR));            \
                    if(EVENT == USART2RXReq || EVENT == USART2TXReq) SetDMAPAR(DMA,EVENT,(&USART2->DR));            \
                    if(EVENT == USART3RXReq || EVENT == USART3TXReq) SetDMAPAR(DMA,EVENT,(&USART3->DR));            \
                    if(EVENT == UART4RXReq  || EVENT == UART4TXReq) SetDMAPAR(DMA,EVENT,(&UART4->DR));              \
                    if(EVENT == UART5RXReq  || EVENT == UART5TXReq) SetDMAPAR(DMA,EVENT,(&UART5->DR));              \
                    if(EVENT == USART6RXReq || EVENT == USART6TXReq) SetDMAPAR(DMA,EVENT,(&USART6->DR));            \
                    SetDMAMEMORY0(DMA,EVENT,(&MEMORY));                                                             \
                    if(EVENT == USART1RXReq || EVENT == USART2RXReq || EVENT == USART3RXReq ||                      \
                       EVENT == UART4RXReq  || EVENT == UART5RXReq  || EVENT == USART6RXReq) ClearDMADir(DMA,EVENT);\
                    else SetDMADir(DMA,EVENT,MemoryToPeripheral);                                                   \
                    SetDMANDTR(DMA,EVENT,sizeof(MEMORY));                                                           \
                    ClearDMAPinc(DMA,EVENT);                                                                        \
                    SetDMAMinc(DMA,EVENT);                                                                          \
                    SetDMACirc(DMA,EVENT);                                                                          \
                    SetDMAPsize(DMA,EVENT,BYTE);                                                                    \
                    SetDMAMsize(DMA,EVENT,BYTE);                                                                    \
                    SetDMAPriority(DMA,EVENT,PRIORITY);                                                             \
                    if(TXINTERRUPT == 1)   SetDMATransferIT(DMA,EVENT);                                             \
                    if(TXINTERRUPT == 0.5) SetDMAHFTransferIT(DMA,EVENT);                                           \
                    if(TXINTERRUPT == 2)   SetDMATransferErrIT(DMA,EVENT);                                          \
                    DMAStart(DMA,EVENT);                                                                            }

#elif defined(STM32F401xx)

        /*!
        *   @brief DMAConnectTOADC(PRIORITY, MEMORY, TXINTERRUPT) -> Connect DMA to ADC
        *       @arg PRIORITY - Priority of target channel
        *       @arg MEMORY - Buffer address for storing values
        *       @arg TXINTERRUPT - Interrupt selection mode: 0.5 - half transferred interrupt
        *                                                    1 - transferred complete interrupt
        *                                                    2 - transferred error interrupt
        *       @version STM32F401xx
        */
    #define ConnectADCTODMA(PRIORITY, MEMORY, TXINTERRUPT)                     {\
                    SetDMAChannel(DMA2,ADC1Req);                                \
                    SetDMAPAR(DMA2,ADC1Req,(&ADC1->DR));                        \
                    SetDMAMEMORY0(DMA2,ADC1Req,(&MEMORY));                      \
                    ClearDMADir(DMA2,ADC1Req);                                  \
                    SetDMANDTR(DMA2,ADC1Req,ADC1_NUMB);                         \
                    ClearDMAPinc(DMA2,ADC1Req);                                 \
                    SetDMAMinc(DMA2,ADC1Req);                                   \
                    SetDMACirc(DMA2,ADC1Req);                                   \
                    SetDMAPsize(DMA2,ADC1Req,HALFWORD);                         \
                    SetDMAMsize(DMA2,ADC1Req,HALFWORD);                         \
                    SetDMAPriority(DMA2,ADC1Req,PRIORITY);                      \
                    if(TXINTERRUPT == 1)   SetDMATransferIT(DMA2,ADC1Req);      \
                    if(TXINTERRUPT == 0.5) SetDMAHFTransferIT(DMA2,ADC1Req);    \
                    if(TXINTERRUPT == 2)   SetDMATransferErrIT(DMA2,ADC1Req);   \
                    DMAStart(DMA2,ADC1Req);                                     }

        /*!
        *   @brief DMAConnectTOUSART(EVENT, PRIORITY, MEMORY, TXINTERRUPT) -> Connect DMA to UART/USART
        *       @arg DMA - Number of DMA
        *       @arg EVENT - UART/USART Event
        *       @arg PRIORITY - Priority of target channel
        *       @arg MEMORY - Buffer address for storing values
        *       @arg TXINTERRUPT - Interrupt selection mode: 0.5 - half transferred interrupt
        *                                                    1 - transferred complete interrupt
        *                                                    2 - transferred error interrupt
        *       @version STM32F401xx
        */
    #define ConnectUSARTTODMA(DMA,EVENT, PRIORITY, MEMORY, TXINTERRUPT)                                            {\
                    SetDMAChannel(DMA,EVENT);                                                                       \
                    if(EVENT == USART1RXReq || EVENT == USART1TXReq) SetDMAPAR(DMA,EVENT,(&USART1->DR));            \
                    if(EVENT == USART2RXReq || EVENT == USART2TXReq) SetDMAPAR(DMA,EVENT,(&USART2->DR));            \
                    if(EVENT == USART6RXReq || EVENT == USART6TXReq) SetDMAPAR(DMA,EVENT,(&USART6->DR));            \
                    SetDMAMEMORY0(DMA,EVENT,(&MEMORY));                                                             \
                    if(EVENT == USART1RXReq || EVENT == USART2RXReq || EVENT == USART6RXReq) ClearDMADir(DMA,EVENT);\
                    else SetDMADir(DMA,EVENT,MemoryToPeripheral);                                                   \
                    SetDMANDTR(DMA,EVENT,sizeof(MEMORY));                                                           \
                    ClearDMAPinc(DMA,EVENT);                                                                        \
                    SetDMAMinc(DMA,EVENT);                                                                          \
                    SetDMACirc(DMA,EVENT);                                                                          \
                    SetDMAPsize(DMA,EVENT,BYTE);                                                                    \
                    SetDMAMsize(DMA,EVENT,BYTE);                                                                    \
                    SetDMAPriority(DMA,EVENT,PRIORITY);                                                             \
                    if(TXINTERRUPT == 1)   SetDMATransferIT(DMA,EVENT);                                             \
                    if(TXINTERRUPT == 0.5) SetDMAHFTransferIT(DMA,EVENT);                                           \
                    if(TXINTERRUPT == 2)   SetDMATransferErrIT(DMA,EVENT);                                          \
                    DMAStart(DMA,EVENT);                                                                            }

#endif /*STM32F401xx, STM32F40_41xxx*/



//----------------------------------------DMA Events list-------------------------------------------//
        /*!
        *   @list DMA Events list TIM
        */
        #define TIM1CH1Req        0xE
        #define TIM1CH2Req        0x30
        #define TIM1CH3Req        0x30
        #define TIM1CH4Req        0x30
        #define TIM1TRIGReq       0x26
        #define TIM1UPReq         0x2E
        #define TIM1COMReq        0x26
        #define TIM2CH1Req        0x2B
        #define TIM2CH2Req        0x33
        #define TIM2CH3Req        0xB
        #define TIM2CH4Req        0x33
        #define TIM2UPReq         0xB
        #define TIM3CH1Req        0x25
        #define TIM3CH2Req        0x2D
        #define TIM3CH3Req        0x3D
        #define TIM3CH4Req        0x15
        #define TIM3TRIGReq       0x25
        #define TIM3UPReq         0x15
        #define TIM4CH1Req        0x2
        #define TIM4CH2Req        0x1A
        #define TIM4CH3Req        0x3A
        #define TIM4UPReq         0x32
        #define TIM5CH1Req        0x16
        #define TIM5CH2Req        0x26
        #define TIM5CH3Req        0x6
        #define TIM5CH4Req        0xE
        #define TIM5TRIGReq       0xE
        #define TIM5UPReq         0x6
#if defined(STM32F40_41xxx) /*--------------STM32F407------------------*/
        #define TIM6UPReq         0xF
        #define TIM7UPReq         0x21
        #define TIM8CH1Req        0x10
        #define TIM8CH2Req        0x10
        #define TIM8CH3Req        0x10
        #define TIM8CH4Req        0x3F
        #define TIM8TRIGReq       0x3F
        #define TIM8UPReq         0xF
        #define TIM8COMReq        0x3F
#endif /*STM32F40_41xxx*/

        /*!
        *   @list DMA Events list SPI
        */
        #define SPI1RXReq         0x13
        #define SPI1TXReq         0x1B
        #define SPI2RXReq         0x18
        #define SPI2TXReq         0x20
        #define SPI3RXReq         0x10
        #define SPI3TXReq         0x28

        /*!
        *   @list DMA Events list ADC
        */
        #define ADC1Req           0x0
#if defined(STM32F40_41xxx) /*--------------STM32F407------------------*/
        #define ADC2Req           0x19
        #define ADC3Req           0x2

        /*!
        *   @list DMA Events list DAC
        */
        #define DAC1Req           0x2F
        #define DAC2Req           0x37
#endif /*STM32F40_41xxx*/

        /*!
        *   @list DMA Events list SDIO
        */
        #define SDIOReq           0x1C

#if defined(STM32F40_41xxx) /*--------------STM32F407------------------*/
        /*!
        *   @list DMA Events list DCMI
        */
        #define DCMIReq           0x39

        /*!
        *   @list DMA Events list CRYP
        */
        #define CRYPINReq         0x2A
        #define CRYPOUTReq        0x32

        /*!
        *   @list DMA Events list HASH
        */
        #define HASHINReq         0x3A
#endif /*STM32F40_41xxx*/

        /*!
        *   @list DMA Events list UART/USART
        */
        #define USART1RXReq       0x14
        #define USART1TXReq       0x3C
        #define USART2RXReq       0x2C
        #define USART2TXReq       0x34

#if defined(STM32F40_41xxx) /*--------------STM32F407------------------*/
        #define USART3RXReq       0xC
        #define USART3TXReq       0x1C
        #define UART4RXReq       0x14
        #define UART4TXReq       0x24
        #define UART5RXReq       0x4
        #define UART5TXReq       0x3C
#endif /*STM32F40_41xxx*/

        #define USART6RXReq       0x15
        #define USART6TXReq       0x3D

        /*!
        *   @list DMA Events list I2C
        */
        #define I2C1RXReq         0x1
        #define I2C1TXReq         0x39
        #define I2C2RXReq         0x17
        #define I2C2TXReq         0x3F
        #define I2C3RXReq         0x13
        #define I2C3TXReq         0x23

        /*!
        *   @list DMA Events list I2S
        */
        #define I2S2RXReq         0x1B
        #define I2S3RXReq         0x12
        #define I2S3TXReq         0x22

//----------------------------------------DMA ID----------------------------------------------------//
    #define DMAID(DMA)    {(DMA == DMA1) ? DMA1_BASE : (DMA == DMA2) ? DMA2_BASE : 0x00;}
//----------------------------------------DMA Step mode---------------------------------------------//
    #define DMADEFAULT  1
    #define DMAFIFO     2
//----------------------------------------DMA Stream&Channel check-----------------------------------------------------------------------------------------------//
    #define DMACHECKSTREAM(various,event)    ((uint32_t)(( (various&0x1)*( 0x18 * ( (event&0x38) >> 3) ) ) + (((various&0x2)>>1)*(0x24 * ((event&0x38) >> 3)))))
    #define DMACHECKCHANNEL(event)           ((uint32_t)((event&0x7) << 25))
//----------------------------------------Set state----------------------------------------------------------------------------------------------------------------------------//
    #define DMAStart(DMA,EVENT)                               (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= (1))
    #define SetDMADirectModeIT(DMA,EVENT)                     (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= (1 << 1))
    #define SetDMATransferErrIT(DMA,EVENT)                    (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= (1 << 2))
    #define SetDMAHFTransferIT(DMA,EVENT)                     (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= (1 << 3))
    #define SetDMATransferIT(DMA,EVENT)                       (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= (1 << 4))
    #define SetDMApfctrl(DMA,EVENT)                           (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= (1 << 5))
    #define SetDMADir(DMA,EVENT,DIR)                          (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= (DIR << 6))
    #define SetDMACirc(DMA,EVENT)                             (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= (1 << 8))
    #define SetDMAPinc(DMA,EVENT)                             (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= (1 << 9))
    #define SetDMAMinc(DMA,EVENT)                             (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= (1 << 10))
    #define SetDMAPsize(DMA,EVENT,PSIZE)                      (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= (PSIZE << 11))
    #define SetDMAMsize(DMA,EVENT,MSIZE)                      (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= (MSIZE << 13))
    #define SetDMAPincos(DMA,EVENT)                           (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= (1 << 15))
    #define SetDMAPriority(DMA,EVENT,PL)                      (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= (PL << 16))
    #define SetDMADBM(DMA,EVENT)                              (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= (1 << 18))
    #define SetDMACT(DMA,EVENT)                               (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= (1 << 19))
    #define SetDMAChannel(DMA,EVENT)                          (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= DMACHECKCHANNEL(EVENT))
    #define SetDMANDTR(DMA,EVENT,NDTR)                        (* (uint32_t *)((DMAID(DMA)) + (0x14 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= ((uint16_t)(NDTR)))
    #define SetDMAPAR(DMA,EVENT,PAR)                          (* (uint32_t *)((DMAID(DMA)) + (0x18 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= ((uint32_t)(PAR)))
    #define SetDMAMEMORY0(DMA,EVENT,M0A)                      (* (uint32_t *)((DMAID(DMA)) + (0x1C + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= ((uint32_t)(M0A)))
    #define SetDMAMEMORY1(DMA,EVENT,M1A)                      (* (uint32_t *)((DMAID(DMA)) + (0x20 + DMACHECKSTREAM(DMADEFAULT,EVENT))) |= ((uint32_t)(M1A)))
    #define SetDMADirectMDIS(DMA,EVENT)                       (* (uint32_t *)((DMAID(DMA)) + (0x24 + DMACHECKSTREAM(DMAFIFO,EVENT))) |= (1 << 2))
    #define SetDMAFIFOTreshold(DMA,EVENT,FTH)                 (* (uint32_t *)((DMAID(DMA)) + (0x24 + DMACHECKSTREAM(DMAFIFO,EVENT))) |= (FTH))
    #define SetDMAFIFOErrIT(DMA,EVENT,FEIE)                   (* (uint32_t *)((DMAID(DMA)) + (0x24 + DMACHECKSTREAM(DMAFIFO,EVENT))) |= (FEIE << 7))
//----------------------------------------Clear state----------------------------------------------------------------------------------------------------------------------//
    #define DMAStop(DMA,EVENT)                                (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) &= ~DMA_SxCR_EN)
    #define ClearDMADir(DMA,EVENT)                            (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) &= ~DMA_SxCR_DIR)
    #define ClearDMAPinc(DMA,EVENT)                           (* (uint32_t *)((DMAID(DMA)) + (0x10 + DMACHECKSTREAM(DMADEFAULT,EVENT))) &= ~DMA_SxCR_PINC)

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*---------------------------------------------------------------------------------------- STM32F410xx--------------------------------------------------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                    //////////////////////////                                                                                          //////////////////////////
                                    ///DMA1 request mapping///                                                                                          ///DMA2 request mapping///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//            | Stream 0    | Stream 1  | Stream 2    | Stream 3    | Stream 4    | Stream 5    | Stream 6  | Stream 7 |////            | Stream 0    | Stream 1  | Stream 2    | Stream 3    | Stream 4    | Stream 5    | Stream 6  | Stream 7 |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//// -----------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//  Channel 0 | SPI3_RX     |     -     | SPI3_RX     | SPI2_RX     | SPI2_TX     | SPI3_TX     |     -     | SPI3_TX  |////  Channel 0 | ADC1        |           | TIM8_CH1    |             | ADC1        |             | TIM1_CH1  |          |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////            |             |     -     | TIM8_CH2    |      -      |             |      -      | TIM1_CH2  |    -     |//
//  Channel 1 | I2C1_RX     |     -     | TIM7_UP     |     -       | TIM7_UP     | I2C1_RX     | I2C1_TX   | I2C1_TX  |////            |             |           | TIM8_CH3    |             |             |             | TIM1_CH3  |          |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//  Channel 2 | TIM4_CH1    |     -     | I2S3_EXT_RX | TIM4_CH2    | I2S3_EXT_TX | I2S3_EXT_TX | TIM4_UP   | TIM4_CH3 |////  Channel 1 |      -      | DCMI      | ADC2        | ADC2        |      -      |      -      |     -     | DCMI     |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//  Channel 3 | I2S3_EXT_RX | TIM2_UP   | I2C3_RX     | I2S2_EXT_RX | I2C3_TX     | TIM2_CH1    | TIM2_CH2  | TIM2_UP  |////  Channel 2 | ADC3        | ADC3      |      -      |      -      |      -      | CRYP_OUT    | CRYP_IN   | HASH_IN  |//
//            |             | TIM2_CH3  |             |             |             |             | TIM2_CH4  | TIM2_CH4 |////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////  Channel 3 | SPI1_RX     |     -     | SPI1_RX     | SPI1_TX     |      -      | SPI1_TX     |     -     |    -     |//
//  Channel 4 | UART5_RX    | USART3_RX | UART4_RX    | USART3_TX   | UART4_TX    | USART2_RX   | USART2_TX | UART5_TX |////            |             |           |             |             |             |             |           |          |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//  Channel 5 |      -      |     -     | TIM3_CH4    |     -       | TIM3_CH1    | TIM3_CH2    |     -     | TIM3_CH3 |////  Channel 4 |      -      |     -     | USART1_RX   | SDIO        |      -      | USART1_RX   | SDIO      | USART1_TX|//
//            |             |           | TIM3_UP     |             | TIM3_TRIG   |             |           |          |////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////  Channel 5 |      -      | USART6_RX | USART6_RX   |     -       |      -      |      -      | USART6_TX | USART6_TX|//
//  Channel 6 | TIM5_CH3    | TIM5_CH4  | TIM5_CH1    | TIM5_CH4    | TIM5_CH2    |     -       | TIM5_UP   |    -     |////            |             |           |             |             |             |             |           |          |//
//            | TIM5_UP     | TIM5_TRIG |             | TIM5_TRIG   |             |             |           |          |////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////  Channel 6 | TIM1_TRIG   | TIM1_CH1  | TIM1_CH2    | TIM1_CH1    | TIM1_CH4    | TIM1_UP     | TIM1_CH3  |          |//
//  Channel 7 |      -      | TIM6_UP   | I2C2_RX     | I2C2_RX     | USART3_TX   | DAC1        | DAC2      | I2C2_TX  |////            |             |           |             |             | TIM1_TRIG   |             |           |    -     |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////            |             |           |             |             | TIM1_COM    |             |           |          |//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////            |             |           |             |             |             |             |           |          |//
                                                                                                                          //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
                                                                                                                          //  Channel 7 |             | TIM8_UP   | TIM8_CH1    | TIM8_CH2    | TIM8_CH3    |             |           | TIM8_CH4 |//
                                                                                                                          //            |      -      |           |             |             |             |      -      |     -     | TIM8_TRIG|//
                                                                                                                          //            |             |           |             |             |             |             |           | TIM8_COM |//
                                                                                                                          //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
                                                                                                                          //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*---------------------------------------------------------------------------------------- STM32F401xx--------------------------------------------------------------------------------------------------------------------------------------------*/
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                    //////////////////////////                                                                                          //////////////////////////
                                    ///DMA1 request mapping///                                                                                          ///DMA2 request mapping///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//            | Stream 0    | Stream 1  | Stream 2    | Stream 3    | Stream 4    | Stream 5    | Stream 6  | Stream 7 |////            | Stream 0    | Stream 1  | Stream 2    | Stream 3    | Stream 4    | Stream 5    | Stream 6  | Stream 7 |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//// -----------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//  Channel 0 | SPI3_RX     |     -     | SPI3_RX     | SPI2_RX     | SPI2_TX     | SPI3_TX     |     -     | SPI3_TX  |////  Channel 0 | ADC1        |           |             |             | ADC1        |             | TIM1_CH1  |          |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////            |             |     -     |      -      |      -      |             |      -      | TIM1_CH2  |    -     |//
//  Channel 1 | I2C1_RX     | I2C3_RX   |      -      |     -       |     -       | I2C1_RX     | I2C1_TX   | I2C1_TX  |////            |             |           |             |             |             |             | TIM1_CH3  |          |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//  Channel 2 | TIM4_CH1    |     -     | I2S3_EXT_RX | TIM4_CH2    | I2S3_EXT_TX | I2S3_EXT_TX | TIM4_UP   | TIM4_CH3 |////  Channel 1 |      -      |     -     |      -      |      -      |      -      |      -      |     -     |    -     |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//  Channel 3 | I2S3_EXT_RX | TIM2_UP   | I2C3_RX     | I2S2_EXT_RX | I2C3_TX     | TIM2_CH1    | TIM2_CH2  | TIM2_UP  |////  Channel 2 |      -      |     -     |      -      |      -      |      -      |      -      |     -     |    -     |//
//            |             | TIM2_CH3  |             |             |             |             | TIM2_CH4  | TIM2_CH4 |////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////  Channel 3 | SPI1_RX     |     -     | SPI1_RX     | SPI1_TX     |      -      | SPI1_TX     |     -     |    -     |//
//  Channel 4 |      -      |     -     |      -      |     -       |     -       | USART2_RX   | USART2_TX |    -     |////            |             |           |             |             |             |             |           |          |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//  Channel 5 |      -      |     -     | TIM3_CH4    |     -       | TIM3_CH1    | TIM3_CH2    |     -     | TIM3_CH3 |////  Channel 4 | SPI4_RX     | SPI4_TX   | USART1_RX   | SDIO        |      -      | USART1_RX   | SDIO      | USART1_TX|//
//            |             |           | TIM3_UP     |             | TIM3_TRIG   |             |           |          |////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////  Channel 5 |      -      | USART6_RX | USART6_RX   | SPI4_RX     | SPI4_TX     |      -      | USART6_TX | USART6_TX|//
//  Channel 6 | TIM5_CH3    | TIM5_CH4  | TIM5_CH1    | TIM5_CH4    | TIM5_CH2    |  I2C3_TX    | TIM5_UP   |    -     |////            |             |           |             |             |             |             |           |          |//
//            | TIM5_UP     | TIM5_TRIG |             | TIM5_TRIG   |             |             |           |          |////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////  Channel 6 | TIM1_TRIG   | TIM1_CH1  | TIM1_CH2    | TIM1_CH1    | TIM1_CH4    | TIM1_UP     | TIM1_CH3  |          |//
//  Channel 7 |      -      |     -     | I2C2_RX     | I2C2_RX     |     -       |     -       |    -      | I2C2_TX  |////            |             |           |             |             | TIM1_TRIG   |             |           |    -     |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////            |             |           |             |             | TIM1_COM    |             |           |          |//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////            |             |           |             |             |             |             |           |          |//
                                                                                                                          //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
                                                                                                                          //  Channel 7 |             |     -     |      -      |     -       |     -       |             |           |          |//
                                                                                                                          //            |      -      |           |             |             |             |      -      |     -     |    -     |//
                                                                                                                          //            |             |           |             |             |             |             |           |          |//
                                                                                                                          //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
                                                                                                                          //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*---------------------------------------------------------------------------------------- STM32F10xx--------------------------------------------------------------------------------------------------------------------------------------------*/
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                    //////////////////////////                                                                                          //////////////////////////
                                    ///DMA1 request mapping///                                                                                          ///DMA2 request mapping///
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//            | Stream 0    | Stream 1  | Stream 2    | Stream 3    | Stream 4    | Stream 5    | Stream 6  | Stream 7 |////            | Stream 0    | Stream 1  | Stream 2    | Stream 3    | Stream 4    | Stream 5    | Stream 6  | Stream 7 |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//// -----------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//  Channel 0 | SPI3_RX     |     -     | SPI3_RX     | SPI2_RX     | SPI2_TX     | SPI3_TX     |     -     | SPI3_TX  |////  Channel 0 | ADC1        |           |             |             | ADC1        |             | TIM1_CH1  |          |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////            |             |     -     |      -      |      -      |             |      -      | TIM1_CH2  |    -     |//
//  Channel 1 | I2C1_RX     | I2C3_RX   |      -      |     -       |     -       | I2C1_RX     | I2C1_TX   | I2C1_TX  |////            |             |           |             |             |             |             | TIM1_CH3  |          |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//  Channel 2 | TIM4_CH1    |     -     | I2S3_EXT_RX | TIM4_CH2    | I2S3_EXT_TX | I2S3_EXT_TX | TIM4_UP   | TIM4_CH3 |////  Channel 1 |      -      |     -     |      -      |      -      |      -      |      -      |     -     |    -     |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//  Channel 3 | I2S3_EXT_RX | TIM2_UP   | I2C3_RX     | I2S2_EXT_RX | I2C3_TX     | TIM2_CH1    | TIM2_CH2  | TIM2_UP  |////  Channel 2 |      -      |     -     |      -      |      -      |      -      |      -      |     -     |    -     |//
//            |             | TIM2_CH3  |             |             |             |             | TIM2_CH4  | TIM2_CH4 |////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////  Channel 3 | SPI1_RX     |     -     | SPI1_RX     | SPI1_TX     |      -      | SPI1_TX     |     -     |    -     |//
//  Channel 4 |      -      |     -     |      -      |     -       |     -       | USART2_RX   | USART2_TX |    -     |////            |             |           |             |             |             |             |           |          |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//  Channel 5 |      -      |     -     | TIM3_CH4    |     -       | TIM3_CH1    | TIM3_CH2    |     -     | TIM3_CH3 |////  Channel 4 | SPI4_RX     | SPI4_TX   | USART1_RX   | SDIO        |      -      | USART1_RX   | SDIO      | USART1_TX|//
//            |             |           | TIM3_UP     |             | TIM3_TRIG   |             |           |          |////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////  Channel 5 |      -      | USART6_RX | USART6_RX   | SPI4_RX     | SPI4_TX     |      -      | USART6_TX | USART6_TX|//
//  Channel 6 | TIM5_CH3    | TIM5_CH4  | TIM5_CH1    | TIM5_CH4    | TIM5_CH2    |  I2C3_TX    | TIM5_UP   |    -     |////            |             |           |             |             |             |             |           |          |//
//            | TIM5_UP     | TIM5_TRIG |             | TIM5_TRIG   |             |             |           |          |////------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////  Channel 6 | TIM1_TRIG   | TIM1_CH1  | TIM1_CH2    | TIM1_CH1    | TIM1_CH4    | TIM1_UP     | TIM1_CH3  |          |//
//  Channel 7 |      -      |     -     | I2C2_RX     | I2C2_RX     |     -       |     -       |    -      | I2C2_TX  |////            |             |           |             |             | TIM1_TRIG   |             |           |    -     |//
//------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|////            |             |           |             |             | TIM1_COM    |             |           |          |//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////            |             |           |             |             |             |             |           |          |//
                                                                                                                          //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
                                                                                                                          //  Channel 7 |             |     -     |      -      |     -       |     -       |             |           |          |//
                                                                                                                          //            |      -      |           |             |             |             |      -      |     -     |    -     |//
                                                                                                                          //            |             |           |             |             |             |             |           |          |//
                                                                                                                          //------------|-------------|-----------|-------------|-------------|-------------|-------------|-----------|----------|//
                                                                                                                          //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif /*FIL_DMA*/
