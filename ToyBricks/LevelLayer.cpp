//
//  LevelLayer.cpp
//  ToyBricks
//
//  Created by user on 13-4-9.
//
//

#include "LevelLayer.h"
#include "LevelItemSprite.h"
#include "Util.h"
#include "GameResources.h"
#include "Config.h"
#include "GameScene.h"

const static int kWidth = 80;
const static int kHeight = 80;

// at the bottom,this 150 use to place ads and page indicate
const static int kBottomOffsetY = 128;

const static int kLeftOffsetX = 80;

//  int y axis , the space of two item;
const static int kIntentY = 20 ;
const static int kIntentX = 20;


LevelLayer::LevelLayer(int totalLevel):
m_firstLevel(0),
m_showingLayer(false),
m_totalLevelCount(totalLevel)
{
    
}
LevelLayer::~LevelLayer(){}

void LevelLayer::onEnter(){
    
    CCLayer::onEnter();

    
    CCSprite* bg = CCSprite::create("levelAnimationBg.png");
    bg->setAnchorPoint(ccp(0, 0));
    bg->setPosition(ccp(0, 105));
    addChild(bg);
    
    //set white bg
//    CCLayerColor* bgLayer = CCLayerColor::create(m_Bgcolor, G_width, G_height);
//    addChild(bgLayer);
    
    // load this page
    loadPage();
}


void LevelLayer::setFirstLevel(int level)
{   
    // 开始循环
    vector<LevelItemSprite*>::iterator it = m_levelItemVector.begin();
    while (it!=m_levelItemVector.end()) {
        LevelItemSprite* sprite = (*it);
        sprite->setLevelCount(this,click_selectorND(LevelLayer::levelItemClicked),level,m_totalLevelCount);
        ++level;
        ++it;
    }
}

void LevelLayer::loadPage()
{
    for (int i = 0; i < kRow; ++i) {
        for (int j = 0; j < kColumn; ++j) {
            
            LevelItemSprite* sprite = LevelItemSprite::createLevelItemSprite(getMyTexture(c_itemBg));
            sprite->setAnchorPoint(ccp(0, 0));
            
            int x = kLeftOffsetX + j*(kWidth + kIntentX);
            int y = kBottomOffsetY + (kRow - i - 1)*(kHeight + kIntentY);
            
            sprite->setPosition(ccp(x, y));
            addChild(sprite);
            m_levelItemVector.push_back(sprite);
        }
    }
}

void LevelLayer::levelItemClicked(CCObject* obj,void* param)
{
    int level = *((int*)param);
    
    CCLog(" [============level :% d===================] ",level);
}

