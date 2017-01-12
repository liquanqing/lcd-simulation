/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MENU_LOW_LEVEL_H
#define __MENU_LOW_LEVEL_H

/* Include -------------------------------------------------------------------*/
#include "stdint.h"		// 类型定义和结构体

/* Exported Definition--------------------------------------------------------*/


/*
 * !Debug Mode , if you want to debug with UART, please #define DEBUG_MENU
 */
#define DEBUG_MENU


/* !when the first time to enter a page ,
 * 'PAGE_INIT' should be send to te CallBack Function
 */
#define PAGE_INIT		0xFF


/* Exported Types ------------------------------------------------------------*/
#ifdef __cplusplus
extern "C" {
#endif

typedef enum {MFALSE = 0, MTRUE = !MFALSE}menu_bool_t;

typedef struct _menu_list_t         menu_list_t;
typedef struct _menu_callback_t     menu_callback_t;
typedef struct _menu_page_t         menu_page_t;
typedef struct _menu_item_t         menu_item_t;

struct _menu_list_t{
    uint8_t ListMin;
    uint8_t ListMax;
    uint8_t Item;
};

struct _menu_callback_t{
    void (*enter)(void);
    void (*action)(void);
    void (*leave)(void);
};

struct _menu_page_t
{
    menu_page_t *pParentPage;
    menu_item_t *pMenuItem;
    menu_callback_t *CallBack;
    menu_list_t *pMenuList;
    uint8_t SinglePageItemNum;
    uint8_t TotalItemNum;
};

struct _menu_item_t
{
    uint8_t *pTextStr;
    menu_page_t *pChildPage;
};

/* Menu Exported Functions ---------------------------------------------------*/
extern menu_bool_t menu_ll_set_def_menu_config( menu_page_t *ptCurPage);
extern menu_bool_t menu_ll_set_cur_page( menu_page_t **ptCurPage,
                                    const  menu_page_t *pPage);

extern menu_bool_t menu_ll_chk_effect_child_page( menu_page_t *ptCurPage);

extern menu_bool_t menu_ll_enter_parent_page( menu_page_t **ptCurPage);
extern menu_bool_t menu_ll_enter_brother_page( menu_page_t **ptCurPage);
extern menu_bool_t menu_ll_enter_child_page( menu_page_t **ptCurPage);

extern menu_bool_t menu_ll_item_move_next( menu_page_t *ptCurPage);
extern menu_bool_t menu_ll_item_move_pre( menu_page_t *ptCurPage);

extern menu_bool_t menu_ll_init( menu_page_t **ptCurPage,
                                    const  menu_page_t *pPage);
extern menu_bool_t menu_ll_run( menu_page_t *ptCurPage);

#ifdef __cplusplus
}
#endif

#endif /* __MENU_LOW_LEVEL_H */
/* End of file ---------------------------------------------------------------*/

