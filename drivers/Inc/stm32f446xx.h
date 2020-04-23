/*
 * stm32f446xx.h
 *
 *  Created on: Apr 12, 2020
 *      Author: Minh Tran
 */

#ifndef INC_STM32F446XX_H_
#define INC_STM32F446XX_H_

#include <stdint.h>

#define IO volatile

// Memory Base Addresses, [1]
#define FLASH_BASEADDR   0x08000000U    // 16 KB
#define SRAM1_BASEADDR   0x20000000U	// 112 KB, Main internal SRAM, aliased by bit-banding
#define SRAM2_BASEADDR   0x2001C000U	// 16 KB, Auxiliary internal SRAM
#define ROM_BASEADDR     0x1FFF0000U 	// 30 KB, System memory
#define OTP_BASEADDR     0x1FFF7800U  	// 528 B
#define OPTION_BASEADDR  0x1FFFC000U  	// 16 B

// Bus Base Addresses, [1]
#define APB1_BASEADDR	0x40000000U    // 32 KB
#define APB2_BASEADDR	0x40010000U	   // 27 KB
#define AHB1_BASEADDR	0x40020000U    // 384 KB
#define AHB2_BASEADDR   0x50000000U	   // 387 KB

// Peripherals on APB1 Bus
#define I2C1_BASEADDR     (APB1_BASEADDR + 0x5400)
#define I2C2_BASEADDR     (APB1_BASEADDR + 0x5800)
#define I2C3_BASEADDR     (APB1_BASEADDR + 0x5C00)
#define SPI2_BASEADDR     (APB1_BASEADDR + 0x3800)
#define SPI3_BASEADDR     (APB1_BASEADDR + 0x3C00)
#define USART2_BASEADDR   (APB1_BASEADDR + 0x4400)
#define USART3_BASEADDR   (APB1_BASEADDR + 0x4800)
#define UART4_BASEADDR    (APB1_BASEADDR + 0x4C00)
#define UART5_BASEADDR    (APB1_BASEADDR + 0x5000)

// Peripherals on APB2 Bus
#define USART1_BASEADDR   (APB2_BASEADDR + 0x1000)
#define USART6_BASEADDR   (APB2_BASEADDR + 0x1400)
#define SPI1_BASEADDR     (APB2_BASEADDR + 0x3000)
#define SPI4_BASEADDR     (APB2_BASEADDR + 0x3400)
#define SYSCONFIG         (APB2_BASEADDR + 0x3800)
#define EXTI_BASEADDR     (APB2_BASEADDR + 0x3C00)

// Peripherals on AHB1 Bus
#define GPIOA_BASEADDR    (AHB1_BASEADDR)
#define GPIOB_BASEADDR    (AHB1_BASEADDR + 0x0400)
#define GPIOC_BASEADDR    (AHB1_BASEADDR + 0x0800)
#define GPIOD_BASEADDR    (AHB1_BASEADDR + 0x0C00)
#define GPIOE_BASEADDR    (AHB1_BASEADDR + 0x1000)
#define GPIOF_BASEADDR    (AHB1_BASEADDR + 0x1400)
#define GPIOG_BASEADDR    (AHB1_BASEADDR + 0x1800)
#define GPIOH_BASEADDR    (AHB1_BASEADDR + 0x1C00)
#define RCC_BASEADDR      (AHB1_BASEADDR + 0x3800)

// GPIO Peripheral Register Structures
typedef struct {
    IO uint32_t MODER;      // Mode Reg.
    IO uint32_t OTYPER;     // Output Type Reg.
    IO uint32_t OSPEEDER;   // Output Speed Reg. (Slew rate)
    IO uint32_t PUPDR;      // Internal Pull-up/Pull-down resistors
    IO uint32_t IDR;        // Input Data Reg.
    IO uint32_t ODR;        // Output Data Reg.
    IO uint32_t BSRR;       // Bit Set/Reset Reg.
    IO uint32_t LCKR;       // Port Configuration Lock Reg.
    IO uint32_t AFRL;       // Alternate Function Lower-Reg.
    IO uint32_t AFRH;       // Alternate Function Higher-Reg.
} GPIO_RegDef_t;

// GPIO Register Base Addresses
#define GPIOA_REG ((GPIO_RegDef_t *)GPIOA_BASEADDR)
#define GPIOB_REG ((GPIO_RegDef_t *)GPIOB_BASEADDR)
#define GPIOC_REG ((GPIO_RegDef_t *)GPIOC_BASEADDR)
#define GPIOD_REG ((GPIO_RegDef_t *)GPIOD_BASEADDR)
#define GPIOE_REG ((GPIO_RegDef_t *)GPIOE_BASEADDR)
#define GPIOF_REG ((GPIO_RegDef_t *)GPIOF_BASEADDR)
#define GPIOG_REG ((GPIO_RegDef_t *)GPIOG_BASEADDR)
#define GPIOH_REG ((GPIO_RegDef_t *)GPIOA_BASEADDR)

// Reset & Clock Control (RCC) Peripheral Register Structures
typedef struct {
    IO uint32_t CR;             // Clock Control Reg.                           0x00
    IO uint32_t PLLCFGR;        // PLL Configuration Reg.                       0x04
    IO uint32_t CFGR;           // Clock Configuration Reg.                     0x08
    IO uint32_t CIR;            // Clock Interrupt Reg.                         0x0C
    IO uint32_t AHB1RSTR;       // AHB1 Peripheral Reset Reg.                   0x10
    IO uint32_t AHB2RSTR;       // AHB2 Peripheral Reset Reg.                   0x14
    IO uint32_t AHB3RSTR;       // AHB3 Peripheral Reset Reg.                   0x18
    IO uint32_t RESERVED1;      // Reserved                                     0x1C
    IO uint32_t APB1RSTR;       // APB1 Peripheral Reset Reg.                   0x20
    IO uint32_t APB2RSTR;       // APB2 Peripheral Reset Reg.                   0x24
    IO uint32_t RESERVED2[2];   // Reserved                                     0x28-0x2C
    IO uint32_t AHB1ENR;        // AHB1 Peripheral Clock Enable Reg.            0x30
    IO uint32_t AHB2ENR;        // AHB2 Peripheral Clock Enable Reg.            0x34
    IO uint32_t AHB3ENR;        // AHB3 Peripheral Clock Enable Reg.            0x38
    IO uint32_t RESERVED3;      // Reserved                                     0x3C
    IO uint32_t APB1ENR;        // APB1 Peripheral Clock Enable Reg.            0x40
    IO uint32_t APB2ENR;        // APB2 Peripheral Clock Enable Reg.            0x44
    IO uint32_t RESERVED4[2];   // Reserved                                     0x48-0x4C
    IO uint32_t AHB1LPENDR;     // AHB1 Low-Power Peripheral Clock Enable Reg.  0x50
    IO uint32_t AHB2LPENDR;     // AHB2 Low-Power Peripheral Clock Enable Reg.  0x54
    IO uint32_t AHB3LPENDR;     // AHB3 Low-Power Peripheral Clock Enable Reg.  0x58
    IO uint32_t RESERVED5;      // Reserved                                     0x5C
    IO uint32_t APB1LPENDR;     // APB1 Low-Power Peripheral Clock Enable Reg.  0x60
    IO uint32_t APB2LPENDR;     // APB2 Low-Power Peripheral Clock Enable Reg.  0x64
    IO uint32_t RESERVED6[2];   // Reserved                                     0x68-0x6C
    IO uint32_t BDCR;           // Backup Domain Control Reg.                   0x70
    IO uint32_t CSR;            // Clock Control & Status Reg.                  0x74
    IO uint32_t RESERVED7[2];   // Reserved                                     0x78-0x7C
    IO uint32_t SSCGR;          // Spread Spectrum Clock Generation Reg.        0x80
    IO uint32_t PLLI2SCFGR;     // PLL I2S Configuration Reg.                   0x84
    IO uint32_t PLLSAICFGR;     // PLL SAI Configuration Reg.                   0x88
    IO uint32_t DCKCFGR;        // Dedicated Clock Configuration Reg.           0x8C
    IO uint32_t CKGATENR;       // Clocks Gated Enable Reg.                     0x90
    IO uint32_t DCKCFGR2;       // Dedicated Clock Configuration Reg. 2         0x94
} RCC_RegDef_t;

#define RCC ((RCC_RegDef_t*)RCC_BASEADDR)

// Peripheral Clock Enable Macros [2]
#define I2C1_CLK_ENA()       (RCC->APB1ENR |= (1 << 21))
#define I2C2_CLK_ENA()       (RCC->APB1ENR |= (1 << 22))
#define I2C3_CLK_ENA()       (RCC->APB1ENR |= (1 << 23))
#define SPI1_CLK_ENA()       (RCC->APB2ENR |= (1 << 12))
#define SPI2_CLK_ENA()       (RCC->APB1ENR |= (1 << 14))
#define SPI3_CLK_ENA()       (RCC->APB1ENR |= (1 << 15))
#define SPI4_CLK_ENA()       (RCC->APB2ENR |= (1 << 13))
#define USART1_CLK_ENA()     (RCC->APB2ENR |= (1 << 4))
#define USART2_CLK_ENA()     (RCC->APB1ENR |= (1 << 17))
#define USART3_CLK_ENA()     (RCC->APB1ENR |= (1 << 18))
#define UART4_CLK_ENA()      (RCC->APB1ENR |= (1 << 19))
#define UART5_CLK_ENA()      (RCC->APB1ENR |= (1 << 20))
#define USART6_CLK_ENA()     (RCC->APB2ENR |= (1 << 5))
#define SYSCONFIG_CLK_ENA()  (RCC->APB2ENR |= (1 << 14))    // System Configuration Controller Clock Enable

// Peripheral Clock Disable Macros [2]
#define I2C1_CLK_DIS()       (RCC->APB1ENR &= ~(1 << 21))
#define I2C2_CLK_DIS()       (RCC->APB1ENR &= ~(1 << 22))
#define I2C3_CLK_DIS()       (RCC->APB1ENR &= ~(1 << 23))
#define SPI1_CLK_DIS()       (RCC->APB2ENR &= ~(1 << 12))
#define SPI2_CLK_DIS()       (RCC->APB1ENR &= ~(1 << 14))
#define SPI3_CLK_DIS()       (RCC->APB1ENR &= ~(1 << 15))
#define SPI4_CLK_DIS()       (RCC->APB2ENR &= ~(1 << 13))
#define USART1_CLK_DIS()     (RCC->APB2ENR &= ~(1 << 4))
#define USART2_CLK_DIS()     (RCC->APB1ENR &= ~(1 << 17))
#define USART3_CLK_DIS()     (RCC->APB1ENR &= ~(1 << 18))
#define UART4_CLK_DIS()      (RCC->APB1ENR &= ~(1 << 19))
#define UART5_CLK_DIS()      (RCC->APB1ENR &= ~(1 << 20))
#define USART6_CLK_DIS()     (RCC->APB2ENR &= ~(1 << 5))
#define SYSCONFIG_CLK_DIS()  (RCC->APB2ENR &= ~(1 << 14))

// Reset

#endif /* INC_STM32F446XX_H_ */

/* NOTES & REFERENCES
[1] Reference manual
	2.2 Memory Organization, p.56
	3.3 Embedded Flash Memory, p.65
	2.2.2 Memory Map and Register Boundaries, p.56
[2] Reference manual
    6.3.10 RCC AHB1 peripheral clock enable rsegister (RCC_AHB1ENR)
*/
