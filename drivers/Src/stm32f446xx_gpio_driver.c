#include "stm32f446xx_gpio_driver.h"

void GPIO_SetClock(uint8_t GPIOx, uint8_t Status)
{
    if (Status == ENABLE) {
        RCC->AHB1ENR |= (1 << GPIOx);
    }
    else if (Status == DISABLE) {
        RCC->AHB1ENR &= ~(1 << GPIOx);
    }
}

GPIO_Handle_t* GetGPIOPortHandler(uint8_t GPIOx)
{
    GPIO_Handle_t *Handle = (GPIO_Handle_t *)malloc(sizeof(GPIO_Handle_t));
    Handle->GPIOx = GPIOx;
    Handle->PinConfig.PinNumber = -1;
    Handle->PinConfig.PinMode = MODE_INPUT;
    Handle->PinConfig.PinSpeed = SPEED_LOW;
    Handle->PinConfig.PinPuPdControl = RSTR_NONE;
    Handle->PinConfig.PinOPType = TYPE_OPENDRAIN;
    Handle->PinConfig.PinAltFuncMode = AF0;

    switch (GPIOx)
    {
        case GPIOA:
            Handle->pGPIO = GPIOA_REG;
            break;
        case GPIOB:
            Handle->pGPIO = GPIOB_REG;
            break;
        case GPIOC:
            Handle->pGPIO = GPIOC_REG;
            break;
        case GPIOD:
            Handle->pGPIO = GPIOD_REG;
            break;
        case GPIOE:
            Handle->pGPIO = GPIOE_REG;
            break;
        case GPIOF:
            Handle->pGPIO = GPIOF_REG;
            break;
        case GPIOG:
            Handle->pGPIO = GPIOG_REG;
            break;
    }
    return Handle;
}

void GPIO_Init(GPIO_Handle_t *hGPIO)
{
    GPIO_Handle_t GPIO = *hGPIO;
    uint8_t pNum = hGPIO->PinConfig.PinNumber;

    // Set the pin mode
    if (GPIO.PinConfig.PinMode <= MODE_ANLG) {
        // Non-interrupt mode
        GPIO.pGPIO->MODER &= ~(0x3 << pNum);
        GPIO.pGPIO->MODER |= GPIO.PinConfig.PinMode << (2 * pNum);
    }
    else {
        // Interrupt mode
    }

    // Set slew rate
    GPIO.pGPIO->OSPEEDER &= ~(0x3 << pNum);
    GPIO.pGPIO->OSPEEDER |= hGPIO->PinConfig.PinSpeed << (2 * pNum);

    // Set Pull-up/Pull-down
    GPIO.pGPIO->PUPDR &= ~(0x3 << pNum);
    GPIO.pGPIO->PUPDR |= hGPIO->PinConfig.PinPuPdControl << (2 * pNum);

    // Set output type
    GPIO.pGPIO->OTYPER &= ~(1 << pNum);
    GPIO.pGPIO->OTYPER |= hGPIO->PinConfig.PinOPType << pNum;

    // Set alternate functionality
    if (GPIO.PinConfig.PinMode == MODE_ALTFN) {
        // GPIOx_AFRL is used for pins 0-7, GPIOx_AFRH is used for pins 8-15
        if (pNum < 8)
        {
            GPIO.pGPIO->AFRL &= ~(0xF << pNum);
            GPIO.pGPIO->AFRL |= GPIO.PinConfig.PinAltFuncMode << pNum;
        }
        else
        {
            GPIO.pGPIO->AFRH &= ~(0xF << pNum);
            GPIO.pGPIO->AFRH |= GPIO.PinConfig.PinAltFuncMode << pNum;
        }
    }
}

void GPIO_DeInit(uint8_t GPIOx)
{
    // Set and clear the reset bit for the corresponding GPIO port
    RCC->AHB1RSTR |= (1 << GPIOx);
    RCC->AHB1RSTR &= ~(1 << GPIOx);
}

uint8_t GPIO_PinRead(GPIO_Handle_t *hGPIO, uint8_t PinNumber)
{
    return (uint8_t)((hGPIO->pGPIO->IDR >> PinNumber) & (0x00000001));
}

uint16_t GPIO_PortRead(GPIO_Handle_t *hGPIO)
{
    return (uint16_t)(hGPIO->pGPIO->IDR);
}

void GPIO_PinWrite(GPIO_Handle_t *hGPIO, uint8_t PinNumber, uint8_t Value)
{
    if (Value == PIN_SET) {
        hGPIO->pGPIO->ODR |= (1 << PinNumber);
    }
    else if (Value == PIN_CLEAR) {
        hGPIO->pGPIO->ODR &= ~(1 << PinNumber);
    }
}

void GPIO_PortWrite(GPIO_Handle_t *hGPIO, uint16_t Value)
{
    hGPIO->pGPIO->ODR = Value;
}

void GPIO_TogglePin(GPIO_Handle_t *hGPIO, uint8_t PinNumber)
{
    hGPIO->pGPIO->ODR ^= (1 << PinNumber);
}

void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnableOrDisable);
void GPIO_Handler(uint8_t PinNumber);

/*
TODO:
1. GPIO_PortWriteAtomic() // Using GPIOx_BSRR
 */
