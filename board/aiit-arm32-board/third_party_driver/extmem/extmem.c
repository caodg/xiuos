/*
* Copyright (c) 2020 AIIT XUOS Lab
* XiUOS is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*        http://license.coscl.org.cn/MulanPSL2
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
* See the Mulan PSL v2 for more details.
*/

/**
* @file extmem.c
* @brief support extmem function
* @version 1.0 
* @author AIIT XUOS Lab
* @date 2021-04-25
*/

#include <extmem.h>
#include <stm32f4xx.h>

#if defined (DATA_IN_ExtSRAM) && defined (DATA_IN_ExtSDRAM)
#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx)\
 || defined(STM32F469xx) || defined(STM32F479xx)
void SystemInitExtMemCtl(void)
{
  __IO uint32_t tmp = 0x00;

  register uint32_t tmpreg = 0, timeout = 0xFFFF;
  register __IO uint32_t index;

  RCC->AHB1ENR |= 0x000001F8;

  tmp = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
  
  GPIOD->AFR[0]  = 0x00CCC0CC;
  GPIOD->AFR[1]  = 0xCCCCCCCC;
  GPIOD->MODER   = 0xAAAA0A8A;
  GPIOD->OSPEEDR = 0xFFFF0FCF;
  GPIOD->OTYPER  = 0x00000000;
  GPIOD->PUPDR   = 0x00000000;

  GPIOE->AFR[0]  = 0xC00CC0CC;
  GPIOE->AFR[1]  = 0xCCCCCCCC;
  GPIOE->MODER   = 0xAAAA828A;
  GPIOE->OSPEEDR = 0xFFFFC3CF;
  GPIOE->OTYPER  = 0x00000000;
  GPIOE->PUPDR   = 0x00000000;
  
  GPIOF->AFR[0]  = 0xCCCCCCCC;
  GPIOF->AFR[1]  = 0xCCCCCCCC;
  GPIOF->MODER   = 0xAA800AAA;
  GPIOF->OSPEEDR = 0xAA800AAA;
  GPIOF->OTYPER  = 0x00000000;
  GPIOF->PUPDR   = 0x00000000;

  GPIOG->AFR[0]  = 0xCCCCCCCC;
  GPIOG->AFR[1]  = 0xCCCCCCCC;
  GPIOG->MODER   = 0xAAAAAAAA;
  GPIOG->OSPEEDR = 0xAAAAAAAA;
  GPIOG->OTYPER  = 0x00000000;
  GPIOG->PUPDR   = 0x00000000;
  
  GPIOH->AFR[0]  = 0x00C0CC00;
  GPIOH->AFR[1]  = 0xCCCCCCCC;
  GPIOH->MODER   = 0xAAAA08A0;
  GPIOH->OSPEEDR = 0xAAAA08A0;
  GPIOH->OTYPER  = 0x00000000;
  GPIOH->PUPDR   = 0x00000000;

  GPIOI->AFR[0]  = 0xCCCCCCCC;
  GPIOI->AFR[1]  = 0x00000CC0;
  GPIOI->MODER   = 0x0028AAAA;
  GPIOI->OSPEEDR = 0x0028AAAA;
  GPIOI->OTYPER  = 0x00000000;
  GPIOI->PUPDR   = 0x00000000;
  
  RCC->AHB3ENR |= 0x00000001;
  tmp = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN);

  FMC_Bank5_6->SDCR[0] = 0x000019E4;
  FMC_Bank5_6->SDTR[0] = 0x01115351;      
  
  FMC_Bank5_6->SDCMR = 0x00000011; 
  tmpreg = FMC_Bank5_6->SDSR & 0x00000020; 
  while((tmpreg != 0) && (timeout-- > 0))
  {
    tmpreg = FMC_Bank5_6->SDSR & 0x00000020; 
  }

  for (index = 0; index<1000; index++);
  
  FMC_Bank5_6->SDCMR = 0x00000012;           
  timeout = 0xFFFF;
  while((tmpreg != 0) && (timeout-- > 0))
  {
    tmpreg = FMC_Bank5_6->SDSR & 0x00000020; 
  }
  
  FMC_Bank5_6->SDCMR = 0x00000073;
  timeout = 0xFFFF;
  while((tmpreg != 0) && (timeout-- > 0))
  {
    tmpreg = FMC_Bank5_6->SDSR & 0x00000020; 
  }
 
  FMC_Bank5_6->SDCMR = 0x00046014;
  timeout = 0xFFFF;
  while((tmpreg != 0) && (timeout-- > 0))
  {
    tmpreg = FMC_Bank5_6->SDSR & 0x00000020; 
  } 
  
  tmpreg = FMC_Bank5_6->SDRTR;
  FMC_Bank5_6->SDRTR = (tmpreg | (0x0000027C<<1));
  
  tmpreg = FMC_Bank5_6->SDCR[0]; 
  FMC_Bank5_6->SDCR[0] = (tmpreg & 0xFFFFFDFF);

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx)
  FMC_Bank1->BTCR[2]  = 0x00001011;
  FMC_Bank1->BTCR[3]  = 0x00000201;
  FMC_Bank1E->BWTR[2] = 0x0fffffff;
#endif
#if defined(STM32F469xx) || defined(STM32F479xx)
  FMC_Bank1->BTCR[2]  = 0x00001091;
  FMC_Bank1->BTCR[3]  = 0x00110212;
  FMC_Bank1E->BWTR[2] = 0x0fffffff;
#endif

  (void)(tmp); 
}
#endif
#elif defined (DATA_IN_ExtSRAM) || defined (DATA_IN_ExtSDRAM)
void SystemInitExtMemCtl(void)
{
  __IO uint32_t tmp = 0x00;
#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx)\
 || defined(STM32F446xx) || defined(STM32F469xx) || defined(STM32F479xx)
#if defined (DATA_IN_ExtSDRAM)
  register uint32_t tmpreg = 0, timeout = 0xFFFF;
  register __IO uint32_t index;

#if defined(STM32F446xx)
  RCC->AHB1ENR |= 0x0000007D;
#else
  RCC->AHB1ENR |= 0x000001F8;
#endif
  tmp = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIOCEN);
  
#if defined(STM32F446xx)
  GPIOA->AFR[0]  |= 0xC0000000;
  GPIOA->AFR[1]  |= 0x00000000;
  GPIOA->MODER   |= 0x00008000;
  GPIOA->OSPEEDR |= 0x00008000;
  GPIOA->OTYPER  |= 0x00000000;
  GPIOA->PUPDR   |= 0x00000000;

  GPIOC->AFR[0]  |= 0x00CC0000;
  GPIOC->AFR[1]  |= 0x00000000;
  GPIOC->MODER   |= 0x00000A00;
  GPIOC->OSPEEDR |= 0x00000A00;
  GPIOC->OTYPER  |= 0x00000000;
  GPIOC->PUPDR   |= 0x00000000;
#endif

  GPIOD->AFR[0]  = 0x000000CC;
  GPIOD->AFR[1]  = 0xCC000CCC;
  GPIOD->MODER   = 0xA02A000A;
  GPIOD->OSPEEDR = 0xA02A000A;
  GPIOD->OTYPER  = 0x00000000;
  GPIOD->PUPDR   = 0x00000000;

  GPIOE->AFR[0]  = 0xC00000CC;
  GPIOE->AFR[1]  = 0xCCCCCCCC;
  GPIOE->MODER   = 0xAAAA800A;
  GPIOE->OSPEEDR = 0xAAAA800A;
  GPIOE->OTYPER  = 0x00000000;
  GPIOE->PUPDR   = 0x00000000;

  GPIOF->AFR[0]  = 0xCCCCCCCC;
  GPIOF->AFR[1]  = 0xCCCCCCCC;
  GPIOF->MODER   = 0xAA800AAA;
  GPIOF->OSPEEDR = 0xAA800AAA;
  GPIOF->OTYPER  = 0x00000000;
  GPIOF->PUPDR   = 0x00000000;

  GPIOG->AFR[0]  = 0xCCCCCCCC;
  GPIOG->AFR[1]  = 0xCCCCCCCC;
  GPIOG->MODER   = 0xAAAAAAAA;
  GPIOG->OSPEEDR = 0xAAAAAAAA;
  GPIOG->OTYPER  = 0x00000000;
  GPIOG->PUPDR   = 0x00000000;

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx)\
 || defined(STM32F469xx) || defined(STM32F479xx)  
  GPIOH->AFR[0]  = 0x00C0CC00;
  GPIOH->AFR[1]  = 0xCCCCCCCC;
  GPIOH->MODER   = 0xAAAA08A0;
  GPIOH->OSPEEDR = 0xAAAA08A0;
  GPIOH->OTYPER  = 0x00000000;
  GPIOH->PUPDR   = 0x00000000;
  
  GPIOI->AFR[0]  = 0xCCCCCCCC;
  GPIOI->AFR[1]  = 0x00000CC0;
  GPIOI->MODER   = 0x0028AAAA;
  GPIOI->OSPEEDR = 0x0028AAAA;
  GPIOI->OTYPER  = 0x00000000;
  GPIOI->PUPDR   = 0x00000000;
#endif
  
  RCC->AHB3ENR |= 0x00000001;
  tmp = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN);

#if defined(STM32F446xx)
  FMC_Bank5_6->SDCR[0] = 0x00001954;
#else  
  FMC_Bank5_6->SDCR[0] = 0x000019E4;
#endif
  FMC_Bank5_6->SDTR[0] = 0x01115351;      
  
  FMC_Bank5_6->SDCMR = 0x00000011; 
  tmpreg = FMC_Bank5_6->SDSR & 0x00000020; 
  while((tmpreg != 0) && (timeout-- > 0))
  {
    tmpreg = FMC_Bank5_6->SDSR & 0x00000020; 
  }

  for (index = 0; index<1000; index++);
  
  FMC_Bank5_6->SDCMR = 0x00000012;           
  timeout = 0xFFFF;
  while((tmpreg != 0) && (timeout-- > 0))
  {
    tmpreg = FMC_Bank5_6->SDSR & 0x00000020; 
  }
  
#if defined(STM32F446xx)
  FMC_Bank5_6->SDCMR = 0x000000F3;
#else  
  FMC_Bank5_6->SDCMR = 0x00000073;
#endif
  timeout = 0xFFFF;
  while((tmpreg != 0) && (timeout-- > 0))
  {
    tmpreg = FMC_Bank5_6->SDSR & 0x00000020; 
  }
 
#if defined(STM32F446xx)
  FMC_Bank5_6->SDCMR = 0x00044014;
#else  
  FMC_Bank5_6->SDCMR = 0x00046014;
#endif
  timeout = 0xFFFF;
  while((tmpreg != 0) && (timeout-- > 0))
  {
    tmpreg = FMC_Bank5_6->SDSR & 0x00000020; 
  } 
  
  tmpreg = FMC_Bank5_6->SDRTR;
#if defined(STM32F446xx)
  FMC_Bank5_6->SDRTR = (tmpreg | (0x0000050C<<1));
#else    
  FMC_Bank5_6->SDRTR = (tmpreg | (0x0000027C<<1));
#endif
  
  tmpreg = FMC_Bank5_6->SDCR[0]; 
  FMC_Bank5_6->SDCR[0] = (tmpreg & 0xFFFFFDFF);
#endif
#endif

#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx) || defined(STM32F417xx)\
 || defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx)\
 || defined(STM32F469xx) || defined(STM32F479xx) || defined(STM32F412Zx) || defined(STM32F412Vx)

#if defined(DATA_IN_ExtSRAM)
  RCC->AHB1ENR   |= 0x00000078;
  tmp = READ_BIT(RCC->AHB1ENR, RCC_AHB1ENR_GPIODEN);
  
  GPIOD->AFR[0]  = 0x00CCC0CC;
  GPIOD->AFR[1]  = 0xCCCCCCCC;
  GPIOD->MODER   = 0xAAAA0A8A;
  GPIOD->OSPEEDR = 0xFFFF0FCF;
  GPIOD->OTYPER  = 0x00000000;
  GPIOD->PUPDR   = 0x00000000;

  GPIOE->AFR[0]  = 0xC00CC0CC;
  GPIOE->AFR[1]  = 0xCCCCCCCC;
  GPIOE->MODER   = 0xAAAA828A;
  GPIOE->OSPEEDR = 0xFFFFC3CF;
  GPIOE->OTYPER  = 0x00000000;
  GPIOE->PUPDR   = 0x00000000;

  GPIOF->AFR[0]  = 0x00CCCCCC;
  GPIOF->AFR[1]  = 0xCCCC0000;
  GPIOF->MODER   = 0xAA000AAA;
  GPIOF->OSPEEDR = 0xFF000FFF;
  GPIOF->OTYPER  = 0x00000000;
  GPIOF->PUPDR   = 0x00000000;

  GPIOG->AFR[0]  = 0x00CCCCCC;
  GPIOG->AFR[1]  = 0x000000C0;
  GPIOG->MODER   = 0x00085AAA;
  GPIOG->OSPEEDR = 0x000CAFFF;
  GPIOG->OTYPER  = 0x00000000;
  GPIOG->PUPDR   = 0x00000000;
  
  RCC->AHB3ENR         |= 0x00000001;

#if defined(STM32F427xx) || defined(STM32F437xx) || defined(STM32F429xx) || defined(STM32F439xx)
  tmp = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN);
  FMC_Bank1->BTCR[2]  = 0x00001011;
  FMC_Bank1->BTCR[3]  = 0x00000201;
  FMC_Bank1E->BWTR[2] = 0x0fffffff;
#endif
#if defined(STM32F469xx) || defined(STM32F479xx)
  tmp = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FMCEN);
  FMC_Bank1->BTCR[2]  = 0x00001091;
  FMC_Bank1->BTCR[3]  = 0x00110212;
  FMC_Bank1E->BWTR[2] = 0x0fffffff;
#endif
#if defined(STM32F405xx) || defined(STM32F415xx) || defined(STM32F407xx)|| defined(STM32F417xx)\
   || defined(STM32F412Zx) || defined(STM32F412Vx)
  tmp = READ_BIT(RCC->AHB3ENR, RCC_AHB3ENR_FSMCEN);
  FSMC_Bank1->BTCR[2]  = 0x00001011;
  FSMC_Bank1->BTCR[3]  = 0x00000201;
  FSMC_Bank1E->BWTR[2] = 0x0FFFFFFF;
#endif

#endif
#endif
  (void)(tmp); 
}
#endif