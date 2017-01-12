/**
  ******************************************************************************
  * @file    Menu.c
  * @author  Inc Li
  * @version V0.0.1
  * @date    29-Aug-2016
  * @brief   Main Menu
  * @modify
  ******************************************************************************
  */

#define _OWN_MENU_MSG
/* Includes ------------------------------------------------------------------*/
#include "menu_msg.h"
#include <string.h>

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define MSG_MAX_COUNT       5
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
static uint8_t chMsgBuffer[MSG_MAX_COUNT] = {0};
static uint8_t chMsgIn = 0;
static uint8_t chMsgOut = 0;
static uint8_t chCurMsgCnt = 0;
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/
bool menu_msg_send(uint8_t chMsg)
{
    if (chCurMsgCnt >= MSG_MAX_COUNT) {
        return false;
    }
    chCurMsgCnt ++;

    chMsgBuffer[chMsgIn] = chMsg;
    chMsgIn ++;
    if (chMsgIn >= MSG_MAX_COUNT) {
        chMsgIn = 0;
    }

    return true;
}

bool menu_msg_wait(uint8_t *pchMsg)
{
    if ((NULL == pchMsg) || (0 == chCurMsgCnt)) {
        return false;
    }
    chCurMsgCnt --;

    *pchMsg = chMsgBuffer[chMsgOut];
    chMsgOut ++;
    if (chMsgOut >= MSG_MAX_COUNT) {
        chMsgOut = 0;
    }

    return true;
}
/******************* (C) COPYRIGHT 2016 Inc *****END OF FILE*******************/



