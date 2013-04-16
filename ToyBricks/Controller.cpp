//
//  Controller.cpp
//  ToyBricks
//
//  Created by user on 13-4-9.
//
//

#include "Controller.h"
#include "ButtonSprite.h"
#include "Util.h"
#include "GameResources.h"
#include "LevelLayer.h"
#include "GameScene.h"
#include "Chapter.h"
#include "LevelScene.h"
#include "Map.h"


//const static int TAG_PRE_BUTTON = 1;
//const static int TAG_NEXT_BUTTON = 2;

Controller::~Controller(){
}
void Controller::onEnter(){
    CCLayer::onEnter();
    
    //  tow button
    //  preBtn
//    ButtonSprite* preBtn = ButtonSprite::createButtonSprite(getMyTexture(c_preLevel));
//    preBtn->setOnClickListener(this,click_selector(Controller::preBtnClicked));
//    preBtn->setPosition(ccp(50, 840));
//    preBtn->setTag(TAG_PRE_BUTTON);
//    addChild(preBtn);

    CCMenuItemImage* preBtn = CCMenuItemImage::create("preLevel.png", "preLevelSelected.png", this, menu_selector(Controller::preBtnClicked));
    preBtn->setPosition(ccp(50, 840));

    
    // next Button
//    ButtonSprite* nextBtn = ButtonSprite::createButtonSprite(getMyTexture(c_nextLevel));
//    nextBtn->setPosition(ccp(590, 840));
//    nextBtn->setOnClickListener(this, click_selector(Controller::nextBtnClicked));
//    nextBtn->setTag(TAG_NEXT_BUTTON);
//    addChild(nextBtn);
     CCMenuItemImage* nextBtn = CCMenuItemImage::create("nextLevel.png","nextLevelSelected.png", this, menu_selector(Controller::nextBtnClicked));
    nextBtn->setPosition(ccp(590, 840));
    
    
    int totalLevelCount = getTotalCount(Game->m_difficult);
    if (Game->m_level == 1) {
        preBtn->setVisible(false);
    }else if(Game->m_level >= totalLevelCount)
    {
        nextBtn->setVisible(false);
    }
    
    //    int the bottom,has four button
//    ButtonSprite* homeBtn = ButtonSprite::createButtonSprite(getMyTexture(c_home));
//    homeBtn->setOnClickListener(this, click_selector(Controller::homeBtnClicked));
//    homeBtn->setPosition(ccp(80, 40));
//    addChild(homeBtn);
    
    CCMenuItemImage* homeBtn = CCMenuItemImage::create("home.png","homeSelected.png", this, menu_selector(Controller::homeBtnClicked));
    homeBtn->setPosition(ccp(80, 40));

    // reset button
//    ButtonSprite* resetBtn = ButtonSprite::createButtonSprite(getMyTexture(c_reset));
//    resetBtn->setOnClickListener(this,click_selector(Controller::resetBtnClicked));
//    resetBtn->setPosition(ccp(240, 40));
//    addChild(resetBtn);
    
    CCMenuItemImage* resetBtn = CCMenuItemImage::create("reset.png","resetSelected.png", this, menu_selector(Controller::resetBtnClicked));
    resetBtn->setPosition(ccp(240, 40));
    
    // selectLevel button
//    ButtonSprite* selectBtn = ButtonSprite::createButtonSprite(getMyTexture(c_selectLevel));
//    selectBtn->setOnClickListener(this,click_selector(Controller::selectLevelBtnClicked));
//    selectBtn->setPosition(ccp(400, 40));
//    addChild(selectBtn);
    
    CCMenuItemImage* selectBtn = CCMenuItemImage::create("selectLevel.png", "selectLevelSelected.png", this,menu_selector(Controller::selectLevelBtnClicked));
    selectBtn->setPosition(ccp(400, 40));
    
    // share Button
//    ButtonSprite* shareBtn = ButtonSprite::createButtonSprite(getMyTexture(c_share));
//    shareBtn->setOnClickListener(this,click_selector(Controller::shareBtnClicked));
//    shareBtn->setPosition(ccp(560, 40));
//    addChild(shareBtn);

    CCMenuItemImage* shareBtn = CCMenuItemImage::create("share.png","shareSelected.png", this, menu_selector(Controller::shareBtnClicked));
    shareBtn->setPosition(ccp(560, 40));
    
    CCMenu* pMenu = CCMenu::create(preBtn,nextBtn,homeBtn,resetBtn,selectBtn,shareBtn,NULL);
    pMenu->setPosition(ccp(0, 0));
    addChild(pMenu);
    
    
    setKeypadEnabled(true);
    
    // set a  back button
    ButtonSprite*  backBtn = ButtonSprite::createButtonSprite(getMyTexture(c_preLevel));
    backBtn->setOnClickListener(this,click_selector(Controller::backBtnClicked));
    backBtn->setPosition(ccp(20, 930));
    addChild(backBtn);
}


void Controller::backBtnClicked()
{
    // back to chapter layer
    CCScene* pScene = CCScene::create();
    
    Chapter* pLayer = new Chapter;
    pLayer->autorelease();
    
    pScene->addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(pScene);
    
}


void Controller::preBtnClicked(CCObject* pSender)
{
    CCLog(" to pre Level");
    
    --Game->m_level;
    
    GameScene* pScene = new GameScene(Game->m_difficult,Game->m_level);
    pScene->autorelease();
    CCDirector::sharedDirector()->replaceScene(pScene); 
}

void Controller::nextBtnClicked(CCObject* pSender)
{
    CCLog(" to next Level");
    
    ++Game->m_level;
    
    CCLog("level:%d",Game->m_level);
    
    GameScene* pScene = new GameScene(Game->m_difficult,Game->m_level);
    pScene->autorelease();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void Controller::homeBtnClicked(CCObject* pSender)
{
    CCLog(" [homeBtnClicked]");
}

void Controller::selectLevelBtnClicked(CCObject* pSender)
{
    CCLog(" [selectLevelBtnClicked]");

    LevelScene* pScene = new LevelScene(Game->m_difficult,Game->m_level);
    pScene->autorelease();
    
    CCDirector::sharedDirector()->pushScene(pScene);
}

void Controller::shareBtnClicked(CCObject* pSender)
{
    CCLog(" [shareBtnClicked]");
}

void Controller::resetBtnClicked(CCObject* pSender)
{
    CCLog(" [resetBtnClicked]");
}

void Controller::keyBackClicked()
{
    
}