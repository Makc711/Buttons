/**
  ******************************************************************************
  * @file           : buttons.h
  * @author         : Rusanov M.N.
  * @version        : V1.1.2
  * @date           : 24-February-2023
  * @brief          : Header for buttons.c file.
  *                   This file contains functions for working with the buttons.
  *                   If you hold down the button for a long time, the button is
  *                   pressed several times.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef BUTTONS_H
#define BUTTONS_H

/* Includes ------------------------------------------------------------------*/
#include <stdbool.h>

/* Exported types ------------------------------------------------------------*/
typedef enum {
  BT_NONE = 0,
  BT_1,
  BT_2,
  BT_3,
  BT_4,
  BT_USER
}ButtonCode;

/* Exported defines ----------------------------------------------------------*/
#define BUT_COUNT_THR   20 // contact bounce protection
#define DELAY_BEFORE_LONG_PRESS  500
#define DELAY_BETWEEN_SLOW_PRESSES 300
#define DELAY_BETWEEN_FAST_PRESSES 150
#define NUMBER_OF_SLOW_PRESSES 3


#if (DELAY_BEFORE_LONG_PRESS > 0xFFFF)
#error "DELAY_BEFORE_LONG_PRESS is greater than the maximum allowed!"
#endif
#if ((DELAY_BEFORE_LONG_PRESS - DELAY_BETWEEN_SLOW_PRESSES) <= BUT_COUNT_THR)
#error "DELAY_BETWEEN_SLOW_PRESSES is too much!"
#endif
#if (((DELAY_BEFORE_LONG_PRESS - DELAY_BETWEEN_FAST_PRESSES) <= BUT_COUNT_THR) || \
  (DELAY_BETWEEN_FAST_PRESSES > DELAY_BETWEEN_SLOW_PRESSES))
#error "DELAY_BETWEEN_FAST_PRESSES is too much!"
#endif
#if (NUMBER_OF_SLOW_PRESSES > 0xFF)
#error "NUMBER_OF_SLOW_PRESSES is greater than the maximum allowed!"
#endif

/* Exported functions prototypes ---------------------------------------------*/
ButtonCode getPressedButtonCode(bool enableMultipleButtonPresses);

#endif // BUTTONS_H
