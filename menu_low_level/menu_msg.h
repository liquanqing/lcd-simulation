/**
  ******************************************************************************
  * @file    menu_msg.h
  * @author  Inc
  * @version V0.0.1
  * @date    15-November-2016
  * @brief   This file contains the headers of System Menu Setting
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MENU_MSG_H
#define __MENU_MSG_H

#ifndef _OWN_MENU_MSG
    #define MENU_MSG_EXT extern
#else
    #define MENU_MSG_EXT
#endif

/* Includes ------------------------------------------------------------------*/
#include "stdint.h"		// 类型定义和结构体
#include "stdbool.h"

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/
#ifndef NULL
#define NULL 0
#endif

#define MSG_SHORT_DOWN          0x10
#define MSG_LONG_DOWN           0x20
#define MSG_HOLD_DOWN           0x30

#define MSG_VOL_UP              0x01
#define MSG_VOL_DOWN            0x02
#define MSG_CH_UP               0x03
#define MSG_CH_DOWN             0x04
#define MSG_CAM_KEY             0x05
#define MSG_KEY_HI              0x06

/* Exported macro ------------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
#ifdef __cplusplus
extern "C" {
#endif


MENU_MSG_EXT bool menu_msg_send(uint8_t chMsg);
MENU_MSG_EXT bool menu_msg_wait(uint8_t *pchMsg);


#ifdef __cplusplus
}
#endif



#endif /* __MENU_MSG_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/



