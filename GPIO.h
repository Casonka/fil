    /*!
    *   --------------------------------------------------------------------------
    *                       ///GPIO initialization\\\
    *   --------------------------------------------------------------------------
    *   @author RCR group developers - Evgeny Garanin
    *   @date 14/08/2020 - last update version GPIO
    *
    *       @note [FIL:GPIO] Configuration file GPIO
    */
#pragma once
#include "FilConfig.h"

    #define PORTA 0
    #define PORTB 1
    #define PORTC 2
    #define PORTD 3
    #define PORTE 4

    /*!
    *   @arg AFx - number of alternate function
    */
    #define AF0  0
    #define AF1  1
    #define AF2  2
    #define AF3  3
    #define AF4  4
    #define AF5  5
    #define AF6  6
    #define AF7  7
    #define AF8  8
    #define AF9  9
    #define AF10 10
    #define AF11 11
    #define AF12 12
    #define AF13 13
    #define AF14 14
    #define AF15 15

    /*!
    *   @list Pin mode for register MODER
    */
    #define INPUT       0
    #define GENERAL     1
    #define ALTERNATE   2
    #define ANALOG      3

    /*!
    *   @list Type of connection for register OTYPER
    */
    #define PUSH_PULL   0
    #define OPEN_DRAIN  1

    /*!
    *   @list Speed for configuration on OSPEEDR
    */
    #define LOW_S       0     //2 MHz
    #define MEDIUM_S    1     //25 MHz
    #define FAST_S      2     //50 MHz
    #define HIGH_S      3     //100 MHz

    /*!
    *   @list pull up/pull down for register PUPDR
    */
    #define NO_PULL_UP 0
    #define PULL_UP    1
    #define PULL_DOWN  2

    /*!
    *   @list Base address General Purpose Input/Output (GPIO) in memory map
    */
    #define GPIO_BASE  (AHB1PERIPH_BASE + 0x0000)
    #define GPIO       ((unsigned char *) GPIO_BASE)

    /*!
    *   @brief GPIOPinID(PIN_PORT,PIN) - set the custom define with necessary pin address
    *       @value PIN_PORT - pins group
    *       @value PIN - pin in selected group
    */
    #define GPIOPinID(PIN_PORT, PIN) ( (PIN_PORT<<4)|PIN )

    /*!
    *   @list Offset in local memory map for GPIO
    */
    #define GPIO_offset           ((uint32_t)0x00000400)
    #define GPIO_base(pin)        (GPIO_BASE +(pin>>4)*GPIO_offset )

    /*!
    *   @brief GPIOPinMode(pin,mode) - calculate mode for initialization MODER
    *       @value pin - number of pin
    *       @value mode - value of MODER for selected pin
    */
    #define GPIOPinMode(pin, mode) ((uint32_t) ( mode) <<((pin&0xF)<<1))

    /*!
    *   @brief GPIOPinType(pin,type) - calculate type for initialization OTYPER
    *       @value pin - number of pin
    *       @value type - value of OTYPER for selected pin
    */
    #define GPIOPinType(pin, type) ((uint32_t) ( type) <<((pin&0xF)))

    /*!
    *   @brief GPIOPinSpeed(pin,speed) - calculate speed for initialization OSPEEDR
    *       @value pin - number of pin
    *       @value speed - value of OSPEEDR for selected pin
    */
    #define GPIOPinSpeed(pin, speed) ((uint32_t) ( speed) <<((pin&0xF)<<1))

    /*!
    *   @brief GPIOPinPull(pin,pull) - calculate pu/pd for initialization PUPDR
    *       @value pin - number of pin
    *       @value pull - value of PUPDR for selected pin
    */
    #define GPIOPinPull(pin, pull) ((uint32_t) ( pull) <<((pin&0xF)<<1))

    /*!
    *   @brief GPIOPinAF(pin,af) - calculate mode for initialization AFR
    *       @value pin - number of pin
    *       @value af - value of AFR for selected pin
    */
    #define GPIOPinAF(pin,af) ((uint32_t) (af) <<((pin&0x7)<<2))

    /*!
    *   @brief GPIOClearMode(pin) - clear MODER on selected pin
    *       @value pin
    */
    #define GPIOClearMode(pin) (*((uint32_t *) (GPIO_base(pin))) &= ~GPIOPinMode(pin, 0x3))

    /*!
    *   @brief GPIOClearType(pin) - clear OTYPER on selected pin
    *       @value pin
    */
    #define GPIOClearType(pin) (*((uint32_t *) (GPIO_base(pin)+ 0x04)) &= ~GPIOPinType(pin, 0x1))

    /*!
    *   @brief GPIOClearSpeed(pin) - clear OSPEEDR on selected pin
    *       @value pin
    */
    #define GPIOClearSpeed(pin) (*((uint32_t *) (GPIO_base(pin) + 0x08)) &= ~GPIOPinSpeed(pin, 0x3))

    /*!
    *   @brief GPIOClearPULL(pin) - clear PUPDR on selected pin
    *       @value pin
    */
    #define GPIOClearPull(pin) (*((uint32_t *) (GPIO_base(pin) + 0x0C)) &= ~GPIOPinPull(pin, 0x3))

    /*!
    *   @brief GPIOClearConf(pin) - clear all registers on selected pin
    *       @value pin
    */
    #define GPIOClearConf(pin)         {\
                 GPIOClearMode(pin);    \
                 GPIOClearType(pin);    \
                 GPIOClearSpeed(pin);   \
                 GPIOClearPull(pin) ;   }

    /*!
    *   @brief GPIOSetMode(pin, mode) - set MODER on selected pin
    *       @value pin
    *       @value mode - set the mode in register MODER
    */
    #define GPIOSetMode(pin,mode)  (*((uint32_t *) (GPIO_base(pin)))       |= GPIOPinMode(pin, mode))

    /*!
    *   @brief GPIOSetType(pin, type) - set OTYPER on selected pin
    *       @value pin
    *       @value type - set the mode in register OTYPER
    */
    #define GPIOSetType(pin,type)  (*((uint32_t *) (GPIO_base(pin)+ 0x04)) |= GPIOPinType(pin, type))

    /*!
    *   @brief GPIOSetSpeed(pin, speed) - set OSPEEDR on selected pin
    *       @value pin
    *       @value speed - set the mode in register OSPEEDR
    */
    #define GPIOSetSpeed(pin,speed)(*((uint32_t *) (GPIO_base(pin)+ 0x08)) |= GPIOPinSpeed(pin, speed))

    /*!
    *   @brief GPIOSetPull(pin, pull) - set PUPDR on selected pin
    *       @value pin
    *       @value pull - set the mode in register PUPDR
    */
    #define GPIOSetPull(pin,pull)  (*((uint32_t *) (GPIO_base(pin)+ 0x0C)) |= GPIOPinPull(pin, pull))

    /*!
    *   @brief GPIOConfPin(pin, mode, type, speed, pull) - set properties on selected pin
    *       @value pin
    *       @value mode - set the mode in register MODER
    *       @value type - set type of working pin in register OTYPER
    *       @value speed - set speed in register OSPEEDR
    *       @value pull - set the pull in register PUPDR
    */
    #define GPIOSetConf(pin, mode,type,speed,pull) {\
       GPIOSetMode(pin,mode);                       \
       GPIOSetType(pin,type);                       \
       GPIOSetSpeed(pin,speed);                     \
       GPIOSetPull(pin,pull);                       }

    /*!
    *   @brief GPIOConfMode(pin, mode) - clear and set MODER on selected pin
    *       @value pin
    *       @value mode - set the mode in register MODER
    */
    #define GPIOConfMode(pin, mode)  {*((uint32_t *) (GPIO_base(pin)+0x00)) = \
                    ((*((uint32_t *) (GPIO_base(pin)+0x00))&(~GPIOPinMode(pin, 0x3)))|GPIOPinMode(pin, mode));}

    /*!
    *   @brief GPIOConfType(pin, type) - clear and set OTYPER on selected pin
    *       @value pin
    *       @value type - set type of working pin in register OTYPER
    */
    #define GPIOConfType(pin, type)  {*((uint32_t *) (GPIO_base(pin)+0x04)) = \
      ((*((uint32_t *) (GPIO_base(pin)+0x04))&(~GPIOPinType(pin, 0x1)))|GPIOPinType(pin, type));}

    /*!
    *   @brief GPIOConfSpeed(pin, speed) - clear and set OSPEEDR on selected pin
    *       @value pin
    *       @value speed - set speed in register OSPEEDR
    */
    #define GPIOConfSpeed(pin,speed) {*((uint32_t *) (GPIO_base(pin)+0x08)) = \
      ((*((uint32_t *) (GPIO_base(pin)+0x08))&(~GPIOPinSpeed(pin, 0x3)))|GPIOPinSpeed(pin,speed));}

    /*!
    *   @brief GPIOConfPull(pin, pull) - clear and set PUPDR on selected pin
    *       @value pin
    *       @value pull - set the pull in register PUPDR
    */
    #define GPIOConfPull(pin, pull)  {*((uint32_t *) (GPIO_base(pin)+0x0C)) = \
      ((*((uint32_t *) (GPIO_base(pin)+0x0C))&(~GPIOPinPull(pin, 0x3)))|GPIOPinPull(pin, pull));}

    /*!
    *   @brief GPIOConfPin(pin, mode, type, speed, pull) - clear and set properties on selected pin
    *       @value pin
    *       @value mode - set the mode in register MODER
    *       @value type - set type of working pin in register OTYPER
    *       @value speed - set speed in register OSPEEDR
    *       @value pull - set the pull in register PUPDR
    */
    #define GPIOConfPin(pin, mode, type, speed, pull) {\
        GPIOConfMode(pin, mode)                        \
        GPIOConfType(pin, type)                        \
        GPIOConfSpeed(pin, speed)                      \
        GPIOConfPull(pin, pull)                        }

    /*!
    *   @brief GPIOConfAF(pin, af) - clear and set alternate function for necessary mode of pin
    *       @value pin
    *       @value af - set alternate function with necessary mode
    */
    #define GPIOConfAF(pin, af)  {*((uint32_t *) (GPIO_base(pin)+0x20+((pin&0x08)>>1))) = \
                    ((*((uint32_t *) (GPIO_base(pin)+0x20+((pin&0x08)>>1)))&(~GPIOPinAF(pin,0xF)))|GPIOPinAF(pin,af));}

    /*!
    *   @brief SetPin(pin) - set pin to logic high potential (>= 1.08 V)
    *       @value pin
    */
    #define SetPin(pin) (*((uint32_t *)((GPIO_base(pin)) + 0x18))= ((uint32_t)1<<((uint32_t)pin&0x0000000f)))

    /*!
    *   @brief ResetPin(pin) - reset pin to logic low potential(< 1.08 V)
    *       @value pin
    */
    #define ResetPin(pin)  (*((uint32_t *)(GPIO_base(pin) + 0x18))= (uint32_t)1<<(((uint32_t)pin&0xf)+0x00000010))

    /*!
    *   @brief TooglePin(pin) - toogle pin to logic low/high potential
    *       @value pin
    */
    #define TooglePin(pin)                      {\
                if(PinVal(pin)) ResetPin(pin);   \
                else SetPin(pin);                }

    /*!
    *   @brief PinVal(pin) - check the input status of selected pin(logical type of value)
    *       @value pin
    */
    #define PinVal(pin) ((*((uint32_t *)(GPIO_base(pin) + 0x10)))&((uint32_t)1<<(pin&0xf)))

    /*!
    *   @brief PinOut(pin) - check the output status of selected pin(logical type of value)
    *       @value pin
    */
    #define PinOut(pin) ((*((uint32_t *)(GPIO_base(pin) + 0x14)))&((uint32_t)1<<(pin&0xf)))

