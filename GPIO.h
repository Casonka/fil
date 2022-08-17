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
    *   @brief pin_id(PIN_PORT,PIN) - set the custom define with necessary pin address
    *       @value PIN_PORT - pins group
    *       @value PIN - pin in selected group
    */
    #define pin_id(PIN_PORT, PIN) ( (PIN_PORT<<4)|PIN )

    /*!
    *   @list Offset in local memory map for GPIO
    */
    #define GPIO_offset           ((uint32_t)0x00000400)
    #define GPIO_base(pin)        (GPIO_BASE +(pin>>4)*GPIO_offset )

    /*!
    *   @brief pin_mode(pin,mode) - calculate mode for initialization MODER
    *       @value pin - number of pin
    *       @value mode - value of MODER for selected pin
    */
    #define pin_mode(pin, mode) ((uint32_t) ( mode) <<((pin&0xF)<<1))

    /*!
    *   @brief pin_type(pin,type) - calculate type for initialization OTYPER
    *       @value pin - number of pin
    *       @value type - value of OTYPER for selected pin
    */
    #define pin_type(pin, type) ((uint32_t) ( type) <<((pin&0xF)))

    /*!
    *   @brief pin_speed(pin,speed) - calculate speed for initialization OSPEEDR
    *       @value pin - number of pin
    *       @value speed - value of OSPEEDR for selected pin
    */
    #define pin_speed(pin, speed) ((uint32_t) ( speed) <<((pin&0xF)<<1))

    /*!
    *   @brief pin_pull(pin,pull) - calculate pu/pd for initialization PUPDR
    *       @value pin - number of pin
    *       @value pull - value of PUPDR for selected pin
    */
    #define pin_pull(pin, pull) ((uint32_t) ( pull) <<((pin&0xF)<<1))

    /*!
    *   @brief pin_af(pin,af) - calculate mode for initialization AFR
    *       @value pin - number of pin
    *       @value af - value of AFR for selected pin
    */
    #define pin_af(pin,af) ((uint32_t) (af) <<((pin&0x7)<<2))


    #define clear_mode(pin) (*((uint32_t *) (GPIO_base(pin))) &= ~pin_mode(pin, 0x3))
    #define clear_type(pin) (*((uint32_t *) (GPIO_base(pin)+ 0x04)) &= ~pin_type(pin, 0x1))
    #define clear_speed(pin) (*((uint32_t *) (GPIO_base(pin) + 0x08)) &= ~pin_speed(pin, 0x3))
    #define clear_pull(pin) (*((uint32_t *) (GPIO_base(pin) + 0x0C)) &= ~pin_pull(pin, 0x3))

    //очиска всех регистров для пина
    #define clear_conf(pin) (           \
                 clear_mode(pin);       \
                 clear_type(pin);       \
                 clear_speed(pin);      \
                 clear_pull(pin) ;      )

    //вычисление адреса пина и установка значения
    #define set_mode(pin,mode)  (*((uint32_t *) (GPIO_base(pin)))       |= pin_mode(pin, mode))
    #define set_type(pin,type)  (*((uint32_t *) (GPIO_base(pin)+ 0x04)) |= pin_mode(pin, type))
    #define set_speed(pin,speed)(*((uint32_t *) (GPIO_base(pin)+ 0x08)) |= pin_mode(pin, speed))
    #define set_pull(pin,pull)  (*((uint32_t *) (GPIO_base(pin)+ 0x0C)) |= pin_mode(pin, pull)))

    //установка всех значений
    #define set_conf(pin, mode,type,speed,pull) (\
       set_mode(pin,mode);\
       set_type(pin,type); \
       set_speed(pin,speed);\
       set_pull(pin,pull); \
         )

    /*!
    *   @brief conf_pin(pin, mode) - clear and set MODER on selected pin
    *       @value pin
    *       @value mode - set the mode in register MODER
    */
    #define conf_mode(pin, mode)  {*((uint32_t *) (GPIO_base(pin)+0x00)) = \
                    ((*((uint32_t *) (GPIO_base(pin)+0x00))&(~pin_mode(pin, 0x3)))|pin_mode(pin, mode));}

    /*!
    *   @brief conf_type(pin, type) - clear and set OTYPER on selected pin
    *       @value pin
    *       @value type - set type of working pin in register OTYPER
    */
    #define conf_type(pin, type)  {*((uint32_t *) (GPIO_base(pin)+0x04)) = \
      ((*((uint32_t *) (GPIO_base(pin)+0x04))&(~pin_type(pin, 0x1)))|pin_type(pin, type));}

    /*!
    *   @brief conf_speed(pin, speed) - clear and set OSPEEDR on selected pin
    *       @value pin
    *       @value speed - set speed in register OSPEEDR
    */
    #define conf_speed(pin,speed) {*((uint32_t *) (GPIO_base(pin)+0x08)) = \
      ((*((uint32_t *) (GPIO_base(pin)+0x08))&(~pin_speed(pin, 0x3)))|pin_speed(pin,speed));}

    /*!
    *   @brief conf_pull(pin, pull) - clear and set PUPDR on selected pin
    *       @value pin
    *       @value pull - set the pull in register PUPDR
    */
    #define conf_pull(pin, pull)  {*((uint32_t *) (GPIO_base(pin)+0x0C)) = \
      ((*((uint32_t *) (GPIO_base(pin)+0x0C))&(~pin_pull(pin, 0x3)))|pin_pull(pin, pull));}

    /*!
    *   @brief conf_pin(pin, mode, type, speed, pull) - clear and set properties on selected pin
    *       @value pin
    *       @value mode - set the mode in register MODER
    *       @value type - set type of working pin in register OTYPER
    *       @value speed - set speed in register OSPEEDR
    *       @value pull - set the pull in register PUPDR
    */
    #define conf_pin(pin, mode, type, speed, pull) {    \
        conf_mode(pin, mode)    \
        conf_type(pin, type)    \
        conf_speed(pin, speed)  \
        conf_pull(pin, pull)    }

    /*!
    *   @brief conf_af(pin, af) - clear and set alternate function for necessary mode of pin
    *       @value pin
    *       @value af - set alternate function with necessary mode
    */
    #define conf_af(pin, af)  {*((uint32_t *) (GPIO_base(pin)+0x20+((pin&0x08)>>1))) = \
                    ((*((uint32_t *) (GPIO_base(pin)+0x20+((pin&0x08)>>1)))&(~pin_af(pin,0xF)))|pin_af(pin,af));}

    /*!
    *   @brief set_pin(pin) - set pin to logic high potential (>= 1.08 V)
    *       @value pin
    */
    #define set_pin(pin) (*((uint32_t *)((GPIO_base(pin)) + 0x18))= ((uint32_t)1<<((uint32_t)pin&0x0000000f)))

    /*!
    *   @brief reset_pin(pin) - reset pin to logic low potential(< 1.08 V)
    *       @value pin
    */
    #define reset_pin(pin)  (*((uint32_t *)(GPIO_base(pin) + 0x18))= (uint32_t)1<<(((uint32_t)pin&0xf)+0x00000010))

    /*!
    *   @brief pin_val(pin) - check the input status of selected pin(logical type of value)
    *       @value pin
    */
    #define pin_val(pin) ((*((uint32_t *)(GPIO_base(pin) + 0x10)))&((uint32_t)1<<(pin&0xf)))

    /*!
    *   @brief pin_out(pin) - check the output status of selected pin(logical type of value)
    *       @value pin
    */
    #define pin_out(pin) ((*((uint32_t *)(GPIO_base(pin) + 0x14)))&((uint32_t)1<<(pin&0xf)))

