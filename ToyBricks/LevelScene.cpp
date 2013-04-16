//
//  LevelScene.cpp
//  ToyBricks
//
//  Created by user on 13-4-10.
//
//

#include "LevelScene.h"
#include "LevelLayer.h"
#include "ButtonSprite.h"
#include "Util.h"
#include "GameResources.h"
#include "Config.h"
#include "GameScene.h"
#include "InfoLevelLayer.h"

const static int kZorder_Down = 1;
const static int kZorder_Up = 2;
const static int kZorder_Btn = 3;

LevelScene::LevelScene(int chapter,int level):
m_chapter(chapter),
m_level(level),
m_currentPage(0),
m_isAnimationing(false)
{
    m_totalLevelCount = getTotalCount(Game->m_difficult);
    
    m_totalPage = (m_totalLevelCount % kCountOfPage == 0) ? m_totalLevelCount / kCountOfPage : m_totalLevelCount / kCountOfPage + 1;
}

void LevelScene::onEnter(){
    CCScene::onEnter();
    
    // set a bg
    CCSprite* bgSprite = CCSprite::create("selectLevelBg.png");
    bgSprite->setAnchorPoint(ccp(0, 0));
    addChild(bgSprite);
    
    m_currentPage = computerCurrentPage();
    
    m_firstLayer = new LevelLayer(m_totalLevelCount);
   // m_firstLayer->setBg(ccc4(255, 255, 0, 255));
    
    m_secondLayer = new LevelLayer(m_totalLevelCount);
    
    // 为了避免截取 touch事件，所以将其移到屏幕外
    m_secondLayer->setPositionX(G_width);
  //  m_secondLayer->setBg(ccc4(255, 0, 0, 255));
    
    addChild(m_firstLayer,kZorder_Up);
    addChild(m_secondLayer, kZorder_Down);
    m_firstLayer->setFirstLevel(1);
    m_firstLayer->m_showingLayer = true;
    m_secondLayer->m_showingLayer = false;
    
    m_infoLayer = new InfoLevelLayer(this);
    addChild(m_infoLayer,kZorder_Btn);
}


LevelScene::~LevelScene(){
    CC_SAFE_RELEASE(m_firstLayer);
    CC_SAFE_RELEASE(m_secondLayer);
    CC_SAFE_RELEASE(m_infoLayer);
}


int LevelScene::computerCurrentPage()
{
    int  mod = m_level % kCountOfPage;
    if (mod == 0) {
        return m_level / kCountOfPage;
    }else
    {
        return m_level / kCountOfPage + 1;
    }
}

void LevelScene::toNextPage()
{
    if (m_isAnimationing) {
        return;
    }

    m_isAnimationing = true;
    
    ++m_currentPage;
    
    LevelLayer* showingLayer = NULL;
    LevelLayer* anotherLayer = NULL;
    if (m_firstLayer->m_showingLayer) {
        showingLayer = m_firstLayer;
        anotherLayer = m_secondLayer;
    }else
    {
        showingLayer = m_secondLayer;
        anotherLayer = m_firstLayer;
    }
    
    // start reset
    anotherLayer->setFirstLevel((m_currentPage-1)*kCountOfPage+1);
    anotherLayer->setPosition(G_width, 0);
    
    //  change order
    reorderChild(anotherLayer, kZorder_Up);
    reorderChild(showingLayer, kZorder_Down);
    
    // start animation
    CCActionInterval*  appearAction = CCMoveTo::create(0.5, ccp(0, 0));
    
   // CCActionInterval* move_ease_inout = CCEaseBackInOut::create(appearAction);
    
    CCCallFuncND* callFun = CCCallFuncND::create(this, callfuncND_selector(LevelScene::afterNextAnimation), showingLayer);
    
    CCActionInterval* seqAction = (CCActionInterval*)CCSequence::create(appearAction,callFun,NULL);
    
    anotherLayer->runAction(seqAction);
    
    showingLayer->m_showingLayer = false;
    anotherLayer->m_showingLayer = true;
    
    // set preBtn  visiable
    m_infoLayer->setPrePageBtnVisiable(true);
    
    if (m_currentPage == m_totalPage) {
        m_infoLayer->setNextPageBtnVisiable(false);
    }
}
void LevelScene::toPrePage()
{
    if (m_isAnimationing) {
        return;
    }
    
    m_isAnimationing = true;
    
    --m_currentPage;
    
    LevelLayer* showingLayer = NULL;
    LevelLayer* anotherLayer = NULL;
    if (m_firstLayer->m_showingLayer) {
        showingLayer = m_firstLayer;
        anotherLayer = m_secondLayer;
    }else
    {
        showingLayer = m_secondLayer;
        anotherLayer = m_firstLayer;
    }
    
    //start reset
    anotherLayer->setFirstLevel((m_currentPage-1)*kCountOfPage+1);
    anotherLayer->setPosition(0, 0);
    
    //  change order
    reorderChild(anotherLayer, kZorder_Down);
    reorderChild(showingLayer, kZorder_Up);
    
    // start animation
    CCActionInterval*  appearAction = CCMoveTo::create(0.5, ccp(G_width, 0));
//    CCActionInterval* move_ease_inout = CCEaseBackInOut::create(appearAction);
    CCCallFunc* callFun = CCCallFunc::create(this,callfunc_selector(LevelScene::afterPreAnimation));
    
    CCActionInterval* seqAction = (CCActionInterval*)CCSequence::create(appearAction,callFun,NULL);
    
    showingLayer->runAction(seqAction);
    
    showingLayer->m_showingLayer = false;
    anotherLayer->m_showingLayer = true;
    
    // set nextBtn  visiable
    m_infoLayer->setNextPageBtnVisiable(true);
    
    if (m_currentPage == 1) {
        m_infoLayer->setPrePageBtnVisiable(false);
    }
}



void LevelScene::afterPreAnimation(){
     m_isAnimationing = false;
}
void LevelScene::afterNextAnimation(CCNode* n, void* p){
    LevelLayer* layer = (LevelLayer*)p;
    layer->setPositionX(G_width);
    m_isAnimationing = false;
}
