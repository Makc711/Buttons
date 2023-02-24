/* Includes ------------------------------------------------------------------*/
#include "buttons.h"
#include "main.h"

/* Functions -----------------------------------------------------------------*/
static ButtonCode ButtonDebrief(void)
{
  ButtonCode buttonCode = BT_NONE;
  if (HAL_GPIO_ReadPin(BT1_GPIO_Port, BT1_Pin) == GPIO_PIN_RESET)
    buttonCode = BT_1;
  else if (HAL_GPIO_ReadPin(BT2_GPIO_Port, BT2_Pin) == GPIO_PIN_RESET)
    buttonCode = BT_2;
  else if (HAL_GPIO_ReadPin(BT3_GPIO_Port, BT3_Pin) == GPIO_PIN_RESET)
    buttonCode = BT_3;
  else if (HAL_GPIO_ReadPin(BT4_GPIO_Port, BT4_Pin) == GPIO_PIN_RESET)
    buttonCode = BT_4;
  else if (HAL_GPIO_ReadPin(BT_USER_GPIO_Port, BT_USER_Pin) == GPIO_PIN_SET)
    buttonCode = BT_USER;
  return buttonCode;
}

/**
  * @retval Code of the pressed button
  */
ButtonCode GetPressedButtonCode(void)
{
  const ButtonCode buttonCode = ButtonDebrief();
  ButtonCode buttonCodeEnd = BT_NONE;
  static ButtonCode previousButtonCode = BT_NONE;
  static uint16_t pressCount = 0;
  static uint8_t clickCount = 0;
  if (buttonCode != BT_NONE)
  {
    if ((previousButtonCode != BT_NONE) && (buttonCode != previousButtonCode))
    {
      pressCount = 0;
      previousButtonCode = buttonCode;
      clickCount = 0;
    }

    if (pressCount > DELAY_BEFORE_LONG_PRESS) 
    {
      const uint16_t delayBetweenPresses = (clickCount < NUMBER_OF_SLOW_PRESSES) ? 
        DELAY_BETWEEN_SLOW_PRESSES : DELAY_BETWEEN_FAST_PRESSES;
      pressCount = DELAY_BEFORE_LONG_PRESS - delayBetweenPresses;
      buttonCodeEnd = buttonCode;
      previousButtonCode = buttonCodeEnd;
      if (clickCount < NUMBER_OF_SLOW_PRESSES)
      {
        clickCount++;
      }
    }
    else
    {
      pressCount++;
    }

    if (pressCount == BUT_COUNT_THR) 
    {
      buttonCodeEnd = buttonCode;
      previousButtonCode = buttonCodeEnd;
    }
  }
  else
  {
    pressCount = 0;
    clickCount = 0;
  }
  return buttonCodeEnd;
}
