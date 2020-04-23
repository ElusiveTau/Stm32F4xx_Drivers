#ifndef INC_STM32F446XX_GPIO_DRIVER_H_
#define INC_STM32F446XX_GPIO_DRIVER_H_

#include "stm32f446xx.h"
#include "stdlib.h"

// Generic Macros
#define OFF        0
#define DISABLE    0
#define PIN_CLEAR  OFF
#define RESET      OFF
#define ON         1
#define ENABLE     ON
#define PIN_SET    ON

// @GPIO_Pin_Modes
#define MODE_INPUT       0
#define MODE_OUTPUT      1
#define MODE_ALTFN       2
#define MODE_ANLG        3
#define MODE_INT_FALLING 4
#define MODE_INT_RISING  5
#define MODE_INT_TRIGGER 6

// @GPIO_Output_SlewRateSpeeds
#define SPEED_LOW    0
#define SPEED_MEDIUM 1
#define SPEED_FAST   2
#define SPEED_HIGH   3

// @GPIO_PullUpPullDown_Resistor
#define RSTR_NONE     0
#define RSTR_PULLUP   1
#define RSTR_PULLDOWN 2

// @GPIO_Output_Types
#define TYPE_PUSHPULL  0
#define TYPE_OPENDRAIN 1

// @GPIO_Alt_Functionality
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

// @GPIO_Alias
// A unique unsigned integer that identifies the GPIO port
// The alias values are used as bit position in RCC clock enable and reset registers
#define GPIOA 0
#define GPIOB 1
#define GPIOC 2
#define GPIOD 3
#define GPIOE 4
#define GPIOF 5
#define GPIOG 6
#define GPIOH 7

typedef struct
{
    uint8_t PinNumber;          // A value between 0-15
    uint8_t PinMode;            // A value from @GPIO_Pin_Modes
    uint8_t PinSpeed;           // A value from @GPIO_Output_SlewRateSpeeds
    uint8_t PinPuPdControl;     // A value from @GPIO_PullUpPullDown_Resistor
    uint8_t PinOPType;          // A value from @GPIO_Output_Types
    uint8_t PinAltFuncMode;     // A value from @GPIO_Alt_Functionality
} GPIO_PinConfig_t;

typedef struct
{
    uint8_t GPIOx;                  // A value from @GPIO_Alias
    GPIO_RegDef_t *pGPIO;
    GPIO_PinConfig_t PinConfig;     // User-provided pin configuration
} GPIO_Handle_t;

/**
@fn GPIO_SetClock
@brief
    Enables or disables the clock signal to a GPIO port.
@param GPIOx
    A value from @GPIO_Alias indicating the GPIO port that should be enabled or disabled.
@param Status
    Either ENABLE(1) or DISABLE(1) macro or their unsigned integer equivalent
@return
    None
*/
void GPIO_SetClock(uint8_t GPIOx, uint8_t Status);

/**
@fn GetGPIOPortHandler
@brief
    Returns a GPIO handle for the pin configuration and pin operations (init/de-init, port and pin set/clear)
@param GPIOx
    A value from @GPIO_Alias
@return
    Returns the GPIO_Handle_t for the GPIOx port (x=A...H)
*/
GPIO_Handle_t* GetGPIOPortHandler(uint8_t GPIOx);

/**
@fn GPIO_Init
@brief
    Initialize the GPIO port and their pins (Mode, Speed, Output type, Pull-up/Pull-down
    resistor, Alt func, etc.)
@param
@return
    None
*/
void GPIO_Init(GPIO_Handle_t *hGPIO);

/**
@fn GPIO_DeInit
@brief
    Resets GPIO port registers to their default reset values.
@param
@return
    None
*/
void GPIO_DeInit(uint8_t hGPIO); // Resets GPIO register values to their reset state

uint8_t GPIO_PinRead(GPIO_Handle_t *hGPIO, uint8_t PinNumber);

uint16_t GPIO_PortRead(GPIO_Handle_t *hGPIO);

void GPIO_PinWrite(GPIO_Handle_t *hGPIO, uint8_t PinNumber, uint8_t Value);

/**
@fn
@brief
@param
@return
*/
void GPIO_PortWrite(GPIO_Handle_t *hGPIO, uint16_t Value);

/**
@fn
@brief
@param
@return
*/
void GPIO_TogglePin(GPIO_Handle_t *hGPIO, uint8_t PinNumber);

// IRQ Configuration & ISR Handling

/**
@fn
@brief
@param
@return
*/
void GPIO_IRQConfig(uint8_t IRQNumber, uint8_t IRQPriority, uint8_t EnableOrDisable);

/**
@fn
@brief
@param
@return
*/
void GPIO_Handler(uint8_t PinNumber);

#endif /* INC_STM32F446XX_GPIO_DRIVER_H_ */

/*
GPIO Driver provides client code an API with the following goals:
    1. GPIO Initialization
    2. Enable/Disable GPIO Port Clock
    3. Read From GPIO Pin
    4. Write to GPIO Pin
    5. Configure Alternate Functionality
    6. Interrupt Handling (configuring priority)
*/
