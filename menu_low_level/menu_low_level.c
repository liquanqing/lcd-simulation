/**
  ******************************************************************************
  * @file    menu_low_level.c
  * @author  Inc
  * @version V2.0.0
  * @date    10-8-2015
  * @brief   This provides the menu structure of low level api
  ******************************************************************************
  * @modify
  *         ֮ǰ�汾  1.0.0
  *         ���ڰ汾  1.0.1
  *         2016/8/18 �޸Ĵ�����ɾ������printf��ӡ��Ϣ ------Inc
  *         ֮ǰ�汾  1.0.1
  *         ���ڰ汾  1.0.2
  *         2016/8/31 ��ָ������пգ�ͬʱ�Թؼ���������������---Inc
  *         ֮ǰ�汾  1.0.2
  *         ���ڰ汾  1.1.0
  *         2016/9/1  ɾ��tCurList����������ҳ���ṩ�Լ���list
  *                   ��menu����---------------------------------Inc
  *         ֮ǰ�汾  1.1.0
  *         ���ڰ汾  1.1.1
  *         2016/9.2  ����menu_item_move_next ��
  *                       menu_item_move_pre�������������Ҫ��ȡ
  *                   ��ҳ��Ϣ�����Ը���������NULL����-----------Inc
  *                   ɾ��CurList�����Լ���ع��ܺ���------------Inc
  *         2016/11.9 �Ż�����-----------------------------------Inc
  *         ֮ǰ�汾  1.1.1
  *         ���ڰ汾  2.0.0
  *         2016/11/14  ɾ���ڲ�ȫ�ֱ���ptCurPage----------------Inc
  *                     �޸Ľṹ�壬pLastList����ΪpMenuList-----Inc
  *                     �޸�ѡ����������ɾ��IsFlipPage,��������
  *                     �����Ҫ��ҳ���򷵻�true�����򷵻�false--Inc
  *                     �Ż�ϸ��---------------------------------Inc
  *                     menu_task������Ϊmenu_run----------------Inc
  *         ֮ǰ�汾  2.0.0
  *         ���ڰ汾  2.1.0
  *                     ģ�����Ϊmenu_low_level-----------------Inc
  *                     ģ��ȫ������ǰ׺Ϊmenu_low_level---------Inc
  *                     ���ӻ�ȡ��ҳ�ĺ���-----------------------Inc
  *                     �Ż�ϸ��---------------------------------Inc
  *         ֮ǰ�汾  2.1.0
  *         ���ڰ汾  2.2.0
  *         2016/11/17  ���û�����ⲿpageָ�븳ֵ��bug����Ϊ˫ָ
  *                     �룬�Ӷ��ﵽ�޸�ָ��ָ���Ҫ��-----------Inc
  *                     ��������ͳһ��Ϊmenu_bool_t������debug---Inc
  *         ֮ǰ�汾  2.2.0
  *         ���ڰ汾  2.2.1
  *         2016/11/18  ����л��ֵܲ˵�ʱû�и�λmenulist��bug--Inc
  *                     �޸�ע�ͷ��
  *         2017/1/12   �޸ĺ������������ټ�����ǰ�汾-----------Inc
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









