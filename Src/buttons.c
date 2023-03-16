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
  static uint8_t clickCount = 0;
  static uint32_t tickStart = 0;
  static bool isLongPress = false;
  if (buttonCode != BT_NONE)
  {
    if (buttonCode != previousButtonCode)
    {
      tickStart = HAL_GetTick();
      previousButtonCode = buttonCode;
      clickCount = 0;
      isLongPress = false;
    }

    if (!isLongPress && (HAL_GetTick() - tickStart > BUT_COUNT_THR)) 
    {
      buttonCodeEnd = buttonCode;
      isLongPress = true;
    }

    if (enableMultipleButtonPresses && isLongPress)
    {
      if (HAL_GetTick() - tickStart > DELAY_BEFORE_LONG_PRESS)
      {
        const uint16_t delayBetweenPresses = (clickCount < NUMBER_OF_SLOW_PRESSES)
                                            ? DELAY_BETWEEN_SLOW_PRESSES
                                            : DELAY_BETWEEN_FAST_PRESSES;
        tickStart += delayBetweenPresses;
        if (clickCount < NUMBER_OF_SLOW_PRESSES)
        {
          clickCount++;
        }
        buttonCodeEnd = buttonCode;
      }
    }
  }
  else
  {
    tickStart = HAL_GetTick();
    isLongPress = false;
    clickCount = 0;
  }
  return buttonCodeEnd;
}
