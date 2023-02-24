/**
  ******************************************************************************
  * @file           : buttons.h
  * @author         : Rusanov M.N.
  * @version        : V1.0.0
  * @date           : 17-February-2023
  * @brief          : Header for buttons.c file.
  *                   This file contains functions for working with the buttons.
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _BUTTONS_H
#define _BUTTONS_H

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
#define BUT_COUNT_THR   200 // contact bounce protection

/* Exported functions prototypes ---------------------------------------------*/
/**
* @retval Code of the pressed button
*/
ButtonCode GetPressedButtonCode(void);

#endif // _BUTTONS_H
