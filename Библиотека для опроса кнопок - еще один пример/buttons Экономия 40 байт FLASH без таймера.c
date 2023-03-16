/* Includes ------------------------------------------------------------------*/
#include "buttons.h"
#include "main.h"

/* Functions -----------------------------------------------------------------*/
static ButtonCode buttonDebrief(void)
{
  ButtonCode buttonCode = BT_NONE;
  if (HAL_GPIO_ReadPin(BT1_GPIO_Port, BT1_Pin) == GPIO_PIN_RESET)
    buttonCode = BT_1;
  if (HAL_GPIO_ReadPin(BT2_GPIO_Port, BT2_Pin) == GPIO_PIN_RESET)
    buttonCode = BT_2;
  if (HAL_GPIO_ReadPin(BT3_GPIO_Port, BT3_Pin) == GPIO_PIN_RESET)
    buttonCode = BT_3;
  if (HAL_GPIO_ReadPin(BT4_GPIO_Port, BT4_Pin) == GPIO_PIN_RESET)
    buttonCode = BT_4;
  if (HAL_GPIO_ReadPin(BT_USER_GPIO_Port, BT_USER_Pin) == GPIO_PIN_SET)
    buttonCode = BT_USER;
  return buttonCode;
}

/**
  * @param enableMultipleButtonPresses = true - enable, false - disable
  * @retval Code of the pressed button
  */
ButtonCode getPressedButtonCode(bool enableMultipleButtonPresses)
{
  const ButtonCode buttonCode = buttonDebrief();
  ButtonCode buttonCodeEnd = BT_NONE;
  static ButtonCode previousButtonCode = BT_NONE;
  static uint16_t pressCount = 0;
  static uint8_t clickCount = 0;
  if (buttonCode != BT_NONE)
  {
    if (buttonCode != previousButtonCode)
    {
      pressCount = 0;
      previousButtonCode = buttonCode;
      clickCount = 0;
    }

    if (pressCount > DELAY_BEFORE_LONG_PRESS) 
    {
      if (enableMultipleButtonPresses)
      {
        const uint16_t delayBetweenPresses = (clickCount < NUMBER_OF_SLOW_PRESSES)
                                            ? DELAY_BETWEEN_SLOW_PRESSES
                                            : DELAY_BETWEEN_FAST_PRESSES;
        pressCount = DELAY_BEFORE_LONG_PRESS - delayBetweenPresses;
        if (clickCount < NUMBER_OF_SLOW_PRESSES)
        {
          clickCount++;
        }
        buttonCodeEnd = buttonCode;
      }
    }
    else
    {
      pressCount++;
    }

    if (pressCount == BUT_COUNT_THR) 
    {
      buttonCodeEnd = buttonCode;
    }
  }
  else
  {
    pressCount = 0;
    clickCount = 0;
  }
  return buttonCodeEnd;
}
