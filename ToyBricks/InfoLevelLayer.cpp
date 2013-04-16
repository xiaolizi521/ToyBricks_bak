//
//  InfoLevelLayer.cpp
//  ToyBricks
//
//  Created by user on 13-4-10.
//
//

#include "InfoLevelLayer.h"
#include "ButtonSprite.h"
#include "Util.h"
#include "GameResources.h"
#include "Config.h"
#include "GameScene.h"
#include "LevelScene.h"

const static int TAG_PRE_BTN = 1;
const static int TAG_NEXT_BTN = 2;

InfoLevelLayer::InfoLevelLayer(LevelScene* levelScene):
m_levelScene(levelScene)
{
    
}

InfoLevelLayer::~InfoLevelLayer()
{
}

void InfoLevelLayer::onEnter()
{
    CCLayer::onEnter();
 
    createPreAndNextPageBtn();
    
    // add back button
    ButtonSprite* backBtn = ButtonSprite::createButtonSprite(getMyTexture(c_preLevel));
    backBtn->setAnchorPoint(ccp(0, 1));
    backBtn->setPosition(ccp(0, 960));
    backBtn->setOnClickListener(this, click_selector(InfoLevelLayer::backBtnClicked));
    addChild(backBtn);
    
    setKeypadEnabled(true);
}

void  InfoLevelLayer::createPreAndNextPageBtn()
{
    ButtonSprite* prePageBtn = ButtonSprite::createButtonSprite(getMyTexture(c_preLevel));
    prePageBtn->setOnClickListener(this, click_selector(InfoLevelLayer::prePageBtnClicked));
    prePageBtn->setPosition(ccp(40, G_height/2));
    prePageBtn->setTag(TAG_PRE_BTN);
    addChild(prePageBtn);
    
    ButtonSprite* nextPageBtn = ButtonSprite::createButtonSprite(getMyTexture(c_nextLevel));
    nextPageBtn->setOnClickListener(this, click_selector(InfoLevelLayer::nextPageBtnClicked));
    nextPageBtn->setPosition(ccp(600, G_height/2));
    nextPageBtn->setTag(TAG_NEXT_BTN);
    addChild(nextPageBtn);
    
    if (m_levelScene->getCurrentPage() == 1) {
        prePageBtn->setVisible(false);
    }
    
    if (m_levelScene->getCurrentPage() == m_levelScene->getTotalPage()) {
        nextPageBtn->setVisible(false);
    }
}



void InfoLevelLayer::prePageBtnClicked()
{
    CCLog( "[prePageBtnClicked]" );
    
    m_levelScene->toPrePage();
}

void InfoLevelLayer::nextPageBtnClicked()
{
    CCLog( "[nextPageBtnClicked]" );
    
    // show next page
    m_levelScene->toNextPage();
}


void InfoLevelLayer::backBtnClicked()
{
    GameScene* game = new GameScene(1,1);
    game->autorelease();
    CCDirector::sharedDirector()->replaceScene(game);
}

void InfoLevelLayer::setPrePageBtnVisiable(bool flag){
    CCNode* node = getChildByTag(TAG_PRE_BTN);
    if (node) {
        node->setVisible(flag);
    }
}
void InfoLevelLayer::setNextPageBtnVisiable(bool flag){
    CCNode* node = getChildByTag(TAG_NEXT_BTN);
    if (node) {
        node->setVisible(flag);
    }
}
void InfoLevelLayer::keyBackClicked()
{
    // to  game scene
    GameScene* pScene = new GameScene(Game->m_difficult,Game->m_level);
    pScene->autorelease();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

