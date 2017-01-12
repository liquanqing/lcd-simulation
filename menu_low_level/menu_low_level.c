/**
  ******************************************************************************
  * @file    menu_low_level.c
  * @author  Inc
  * @version V2.0.0
  * @date    10-8-2015
  * @brief   This provides the menu structure of low level api
  ******************************************************************************
  * @modify
  *         之前版本  1.0.0
  *         现在版本  1.0.1
  *         2016/8/18 修改代码风格，删除所有printf打印信息 ------Inc
  *         之前版本  1.0.1
  *         现在版本  1.0.2
  *         2016/8/31 对指针进行判空，同时对关键参数做保护处理---Inc
  *         之前版本  1.0.2
  *         现在版本  1.1.0
  *         2016/9/1  删除tCurList变量，所有页面提供自己的list
  *                   给menu管理---------------------------------Inc
  *         之前版本  1.1.0
  *         现在版本  1.1.1
  *         2016/9.2  更改menu_item_move_next 和
  *                       menu_item_move_pre函数，如果不需要获取
  *                   翻页信息，可以给函数输入NULL参数-----------Inc
  *                   删除CurList变量以及相关功能函数------------Inc
  *         2016/11.9 优化函数-----------------------------------Inc
  *         之前版本  1.1.1
  *         现在版本  2.0.0
  *         2016/11/14  删除内部全局变量ptCurPage----------------Inc
  *                     修改结构体，pLastList更改为pMenuList-----Inc
  *                     修改选项变更函数，删除IsFlipPage,增加类型
  *                     如果需要翻页，则返回true，否则返回false--Inc
  *                     优化细节---------------------------------Inc
  *                     menu_task函数改为menu_run----------------Inc
  *         之前版本  2.0.0
  *         现在版本  2.1.0
  *                     模块更名为menu_low_level-----------------Inc
  *                     模块全部函数前缀为menu_low_level---------Inc
  *                     增加获取子页的函数-----------------------Inc
  *                     优化细节---------------------------------Inc
  *         之前版本  2.1.0
  *         现在版本  2.2.0
  *         2016/11/17  解决没法对外部page指针赋值的bug，改为双指
  *                     针，从而达到修改指针指向的要求-----------Inc
  *                     函数返回统一改为menu_bool_t，方便debug---Inc
  *         之前版本  2.2.0
  *         现在版本  2.2.1
  *         2016/11/18  解决切换兄弟菜单时没有复位menulist的bug--Inc
  *                     修改注释风格
  *         2017/1/12   修改函数命名，不再兼容以前版本-----------Inc
  ******************************************************************************
  */

/*

List = ListMin~ListMax
+-----------------------------------+         +-----------------------------------+
| +-------+   +-------+   +-------+ |         | +-------+   +-------+   +-------+ |
| |ListMin|   |ListNum|   |ListNum| |         | |ListMin|   |ListNum|   |ListNum| |
| +-------+   +-------+   +-------+ |         | +-------+   +-------+   +-------+ |
| +-------+   +-------+   +-------+ |         | +-------+   +-------+   +-------+ |
| |ListNum|   |ListNum|   |ListNum| |         | |ListNum|   |ListNum|   |ListNum| |
| +-------+   +-------+   +-------+ | Enter-> | +-------+   +-------+   +-------+ |
| +-------+   +-------+   +-------+ | <-Exit  | +-------+   +-------+   +-------+ |
| |ListNum|   |ListNum|   |ListMax| |         | |ListNum|   |ListNum|   |ListMax| |
| +-------+   +-------+   +-------+ |         | +-------+   +-------+   +-------+ |
|            Parent Page            |         |            Child Page             |
+-----------------------------------+         +-----------------------------------+

 */

/* Includes ------------------------------------------------------------------*/
#include "menu_low_level.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ABS(X)  ((X) >= 0 ? (X) : (-X))

#ifndef TRUE
#define	TRUE	1
#endif

#ifndef FALSE
#define	FALSE	0
#endif

#ifndef NULL
#define NULL 0
#endif
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/*
 *@ brief : Set Default List Frame and Current Item.
 *@ param : target page
 *@ return : None
 *@ attention : ListMax can not smaller than ListMin
 */
menu_bool_t menu_ll_set_def_menu_config(menu_page_t *ptCurPage)
{
    if ((NULL != ptCurPage) &&
        (NULL != ptCurPage->pMenuList)) {
        ptCurPage->pMenuList->ListMin = 0;
        ptCurPage->pMenuList->Item = 0;
        if (0 != ptCurPage->SinglePageItemNum) {
            ptCurPage->pMenuList->ListMax = ptCurPage->SinglePageItemNum - 1;
        } else {
            ptCurPage->pMenuList->ListMax = 0;
        }

        return MTRUE;
    }

    return MFALSE;
}

/*
 *@ breif : Set Current Page,but Set the Default List Frame in the same time
 *@ param : *pPage is point to a Page structure
 *@ param : target page
 *@ return : None
 *@ attention :
 */
menu_bool_t menu_ll_set_cur_page( menu_page_t **ptCurPage,
                        const menu_page_t *pPage)
{
    if ((NULL != pPage) && (NULL != ptCurPage)) {
        *ptCurPage = (menu_page_t *)pPage;
        return MTRUE;
    }

    return MFALSE;
}

/*
 *@ brief :Exit Current Page, do something such as GUI.etc
 *@ param : target page
 *@ return : None
 *@ attention :
 */
void menu_ll_exit_cur_page(menu_page_t *ptCurPage)
{
    if (NULL != ptCurPage) {
        ptCurPage->CallBack->leave();
    }
}

/*
 *@ brief :Enter Current Page, do something such as GUI.etc
 *@ param : target page
 *@ return : None
 *@ attention :
 */
void menu_ll_enter_cur_page(menu_page_t *ptCurPage)
{
    if (NULL != ptCurPage) {
        ptCurPage->CallBack->enter();
    }
}


/*
 *@ brief : Check effect for Children Page
 *@ Param : target page
 *@ return : TRUE or FALSE
 *@ attention :
 */
menu_bool_t menu_ll_chk_effect_child_page(menu_page_t *ptCurPage)
{
    menu_bool_t tFlag = MFALSE;

    if (NULL != ptCurPage->pMenuItem[ptCurPage->pMenuList->Item].pChildPage) {
        tFlag = MTRUE;
    }

    return tFlag;
}

/*
 *@ brief : get the current item 's children page
 *@ Param : target page
 *@ return : TRUE or FALSE
 *@ attention :
 */
menu_page_t * menu_ll_get_child_page(menu_page_t *ptCurPage)
{
    if ((ptCurPage == NULL) ||
        (ptCurPage->pMenuItem == NULL) ||
        (ptCurPage->pMenuList == NULL) ||
        (ptCurPage->pMenuItem[ptCurPage->pMenuList->Item].pChildPage == NULL)) {
        return NULL;
    }

    return ptCurPage->pMenuItem[ptCurPage->pMenuList->Item].pChildPage;
}

/*
 *@ brief : Enter a new page, this page is a children page for current item;
 *@ param : target page
 *@ return : None
 *@ attention :
 */
menu_bool_t menu_ll_enter_child_page(menu_page_t **ptCurPage)
{
    menu_page_t *ptChildPage = NULL;

    if ((ptCurPage == NULL) ||
        ((*ptCurPage)->pMenuItem == NULL) ||
        ((*ptCurPage)->pMenuList == NULL)) {
        return MFALSE;
    }

    ptChildPage = menu_ll_get_child_page(*ptCurPage);

    if (NULL != ptChildPage) {
        menu_ll_exit_cur_page(*ptCurPage);
        menu_ll_set_cur_page(ptCurPage, ptChildPage);
        menu_ll_set_def_menu_config(*ptCurPage);
        menu_ll_enter_cur_page(*ptCurPage);
        return MTRUE;
    }

    return MFALSE;
}

/*
 *@ brief : Exit current page, this page is a parent page for current page
 *@ param : target page
 *@ return : None
 *@ attention :
 */
menu_bool_t menu_ll_enter_parent_page(menu_page_t **ptCurPage)
{
    if ((NULL != ptCurPage) &&
        (NULL != (*ptCurPage)->pParentPage)) {
        menu_ll_exit_cur_page(*ptCurPage);
        menu_ll_set_cur_page(ptCurPage, (*ptCurPage)->pParentPage);
        menu_ll_enter_cur_page(*ptCurPage);

        return MTRUE;
    }

    return MFALSE;
}

/*
 *@ brief : Exit current page and Enter a next page
 *@ param : target page
 *@ return : bool
 *@ attention : its brother page should be a effective page,
                if not, it will live in dead loop
 */
menu_bool_t menu_ll_enter_brother_page(menu_page_t **ptCurPage)
{
    menu_page_t *ptChildPage = NULL;

    if ((NULL != ptCurPage) &&
        (NULL != (*ptCurPage)->pParentPage) &&
        (NULL != (*ptCurPage)->pMenuItem)) {

        menu_ll_exit_cur_page(*ptCurPage);
        menu_ll_set_cur_page(ptCurPage, (*ptCurPage)->pParentPage);
        menu_ll_item_move_next(*ptCurPage);
        ptChildPage = menu_ll_get_child_page(*ptCurPage);

        if (NULL != ptChildPage) {
            menu_ll_set_cur_page(ptCurPage, ptChildPage);
            menu_ll_set_def_menu_config(*ptCurPage);
            menu_ll_enter_cur_page(*ptCurPage);
            return MTRUE;
        }

        return MFALSE;
    }

    return MFALSE;
}

/*
 *@ brief : Move next item
 *@ param : *pIsFlipPage : point to a flag,
                           if need to flip, it will be set to '1'
                           else it will be set to '0'
 *@ param : target page
 *@ return : bool
 *@ attention :
 */
menu_bool_t menu_ll_item_move_next(menu_page_t *ptCurPage)
{
    menu_bool_t tIsFilpPage = MFALSE;

    if ((NULL == ptCurPage) ||
        (NULL == ptCurPage->pMenuList) ||
        (NULL == ptCurPage->pMenuItem)) {
        return tIsFilpPage;
    }

    if ((ptCurPage->SinglePageItemNum == 0) || (ptCurPage->TotalItemNum == 0)) {
        return tIsFilpPage;
    }

    if (ptCurPage->pMenuList->Item >= (ptCurPage->TotalItemNum - 1)) {
        ptCurPage->pMenuList->ListMin = 0;
        ptCurPage->pMenuList->Item = 0;

        if (ptCurPage->SinglePageItemNum >= ptCurPage->TotalItemNum) {
            ptCurPage->pMenuList->ListMax = ptCurPage->TotalItemNum - 1;
        } else {
            ptCurPage->pMenuList->ListMax = ptCurPage->SinglePageItemNum - 1;
            tIsFilpPage = MTRUE; //need to flip a page
        }

    } else if (ptCurPage->pMenuList->Item == ptCurPage->pMenuList->ListMax) {
        ptCurPage->pMenuList->ListMin = ptCurPage->pMenuList->ListMax + 1;

        if((ptCurPage->TotalItemNum - ptCurPage->pMenuList->ListMax)
            < ptCurPage->SinglePageItemNum) {
            ptCurPage->pMenuList->ListMax = ptCurPage->TotalItemNum - 1;
        } else {
            ptCurPage->pMenuList->ListMax = ptCurPage->pMenuList->ListMin
                                            + ptCurPage->SinglePageItemNum - 1;
        }

        ptCurPage->pMenuList->Item = ptCurPage->pMenuList->ListMin;
        tIsFilpPage = MTRUE;//need to flip a page
    } else {
        ptCurPage->pMenuList->Item += 1;
    }

    return tIsFilpPage;
}

/*
 *@ brief : Move previous item
 *@ param : target page
 *@ return : bool
 *@ attention :
 */
menu_bool_t menu_ll_item_move_pre(menu_page_t *ptCurPage)
{
    menu_bool_t tIsFilpPage = MFALSE;

    if ((NULL == ptCurPage) ||
        (NULL == ptCurPage->pMenuList) ||
        (NULL == ptCurPage->pMenuItem)) {
        return tIsFilpPage;
    }

    if ((ptCurPage->SinglePageItemNum == 0) || (ptCurPage->TotalItemNum == 0)) {
        return tIsFilpPage;
    }

    if (0 == ptCurPage->pMenuList->Item) {
        if (ptCurPage->SinglePageItemNum >= ptCurPage->TotalItemNum) {
            ptCurPage->pMenuList->ListMin = 0;
        } else {
            ptCurPage->pMenuList->ListMin = ptCurPage->TotalItemNum
                            - (ptCurPage->TotalItemNum
                            % ptCurPage->SinglePageItemNum);
            tIsFilpPage = MTRUE;
        }

        ptCurPage->pMenuList->ListMax = ptCurPage->TotalItemNum - 1;
        ptCurPage->pMenuList->Item = ptCurPage->pMenuList->ListMax;

    } else if (ptCurPage->pMenuList->Item == ptCurPage->pMenuList->ListMin) {
        ptCurPage->pMenuList->ListMax = ptCurPage->pMenuList->ListMin - 1;
        ptCurPage->pMenuList->ListMin = ptCurPage->pMenuList->ListMax
                                        - ptCurPage->SinglePageItemNum + 1;
        ptCurPage->pMenuList->Item = ptCurPage->pMenuList->ListMax;
        tIsFilpPage = MTRUE;
    } else {
        ptCurPage->pMenuList->Item -= 1;
    }

    return tIsFilpPage;
    /**pCurItem = ptCurPage->pMenuList->Item;*/

}

/*
 *@ brief : init menu, set the main page and set default manu list information
 *@ param : *pPage : Main page
 *@ return : bool
 */
menu_bool_t menu_ll_init(menu_page_t **ptCurPage,
                const menu_page_t *pPage)
{
    if ((NULL != pPage) && (NULL != ptCurPage)) {
        menu_ll_set_cur_page(ptCurPage, pPage);
        menu_ll_set_def_menu_config(*ptCurPage);
        menu_ll_enter_cur_page(*ptCurPage);
        return MTRUE;
    }

    return MFALSE;
}

/*
 *@ brief : menu task
 *@ param : target page
 *@ return : bool
 *@ attention :
 */
menu_bool_t menu_ll_run(menu_page_t *ptCurPage)
{
    if (NULL != ptCurPage) {
	    ptCurPage->CallBack->action();
        return MTRUE;
    }

    return MFALSE;
}


/******************* (C) COPYRIGHT 2016 Inc *****END OF FILE*******************/









