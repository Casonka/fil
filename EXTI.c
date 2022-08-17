#include "EXTI.h"

#if(configUSE_EXTI == 1)
//---------------------------------------------------------//
//----------------------External Interrupts----------------//
//---------------------------------------------------------//
void EXTI0_IRQHandler(void)
{
    EXTI->PR=0x1;
}

void EXTI1_IRQHandler(void)
{
    EXTI->PR=0x2;
}

void EXTI2_IRQHandler(void)
{
  EXTI->PR=0x4;
}

void EXTI3_IRQHandler(void)
{
  EXTI->PR=0x8;
}

void EXTI4_IRQHandler(void)
{
  EXTI->PR=0x10;
}

void EXTI9_5_IRQHandler(void)
{

  if (EXTI->PR&(1<<6))
  {
    EXTI->PR=(1<<6);
  }

  if (EXTI->PR&(1<<7))
  {
    EXTI->PR=(1<<7);
  }

    if (EXTI->PR&(1<<8))
  {
    EXTI->PR=(1<<8);
  }

  if (EXTI->PR&(1<<9))
{
    EXTI->PR=(1<<9);
}
}

void EXTI15_10_IRQHandler(void)
{

  if (EXTI->PR&(1<<10))
  {
    EXTI->PR=(1<<10);
  }

}
#endif /*configUSE_EXTI*/
