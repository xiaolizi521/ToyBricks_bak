//
//  CallBack.h
//  Paopao_Game
//
//  Created by user on 13-2-17.
//
//

#ifndef __Paopao_Game__CallBack__
#define __Paopao_Game__CallBack__

#include <iostream>
#include "cocos2d.h"



using namespace cocos2d;


//
//
//   成员函数指针
typedef  void  (CCObject::*ButtonClick_Func)();
typedef  void  (CCObject::*ButtonClick_FuncN)(CCObject* obj);
typedef  void  (CCObject::*ButtonClick_FuncND)(CCObject* obj,void* param);


//   长按事件
typedef void  (CCObject::*ButtonLongClick_Func)();
//   long long Click
typedef void  (CCObject::*ButtonLongLongClick_Func)();

#define click_selector(_SELECTOR) (ButtonClick_Func)(&_SELECTOR)
#define click_selectorN(_SELECTOR) (ButtonClick_FuncN)(&_SELECTOR)
#define click_selectorND(_SELECTOR) (ButtonClick_FuncND)(&_SELECTOR)

#define click_long_selector(_SELECTOR) (ButtonLongClick_Func)(&_SELECTOR)
#define click_longlong_selector(_SELECTOR) (ButtonLongLongClick_Func)(&_SELECTOR)



#endif /* defined(__Paopao_Game__CallBack__) */
