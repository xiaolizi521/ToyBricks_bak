//
//  LevelItemSprite.cpp
//  ToyBricks
//
//  Created by user on 13-4-9.
//
//

#include "LevelItemSprite.h"

const static int TAG_OF_LABEL = 1;

LevelItemSprite::LevelItemSprite():m_BtnClick_FuncND(NULL)
{
    
}

LevelItemSprite* LevelItemSprite::createLevelItemSprite(CCTexture2D* texture,int tPriority)
{
    LevelItemSprite* button  = new LevelItemSprite;
    button->m_touchPriority = tPriority;
    if (button && button->initWithTexture(texture)) {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return NULL;
}



void LevelItemSprite::setLevelCount(CCObject* target,ButtonClick_FuncND funND,int count,int totalCount)
{
    // if it has label
    CCNode* node =  getChildByTag(TAG_OF_LABEL);
    if (node) {
        CCLabelTTF* levelCountLabel = (CCLabelTTF*)node;
        levelCountLabel->setString(CCString::createWithFormat("%d",count)->getCString());
        setOnClickListener(target, funND, count);
        
        if (count > totalCount) {
            setVisible(false);
        }else
        {
            setVisible(true);
        }
    }else
    {
        CCLabelTTF* levelCountLabel = CCLabelTTF::create(CCString::createWithFormat("%d",count)->getCString(),"Helvetica-Oblique", 30);
        setOnClickListener(target, funND, count);
        levelCountLabel->setPosition(ccp(40, 40));
        levelCountLabel->setColor(ccc3(49, 47, 34));
        levelCountLabel->setTag(TAG_OF_LABEL);
        addChild(levelCountLabel);
        
        if (count > totalCount) {
            setVisible(false);
        }else
        {
            setVisible(true);
        }
    }
}


void LevelItemSprite::setOnClickListener(CCObject* target,ButtonClick_FuncND funND,int param)
{
    m_selectorTarget = target;
    m_BtnClick_FuncND = funND;
    m_param = param;
    
    CCLog("[m_BtnClick_FuncND : %d]",m_BtnClick_FuncND);
}


void LevelItemSprite::clicked()
{
    (m_selectorTarget->*m_BtnClick_FuncND)(m_selectorTarget,&m_param);
}


void LevelItemSprite::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent){
   
    CCLog("[m_BtnClick_FuncND : %d]",m_BtnClick_FuncND);
    CCPoint touchPoint = getParent()->convertTouchToNodeSpace(pTouch);
    if (boundingBox().containsPoint(touchPoint) && m_isDown) {
        /* 相当于产生了click事件 */
        if (m_BtnClick_FuncND) {
            //来个点击效果
            CCActionInterval* sAction = CCScaleTo::create(0.06, 1.2);
            CCActionInterval* sAction2 = CCScaleTo::create(0.06, 1);
            CCCallFunc*  callFun = CCCallFunc::create(this,callfunc_selector(LevelItemSprite::clicked));
            runAction(CCSequence::create(sAction,sAction2,callFun,NULL));
            
        }
        m_isDown = false;
    }
};
