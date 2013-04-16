//
//  Chapter.cpp
//  ToyBricks
//
//  Created by user on 13-4-2.
//
//

#include "Chapter.h"
#include "ButtonSprite.h"
#include "GameScene.h"
#include "MainMenu.h"

Chapter::Chapter(){}
Chapter::~Chapter(){}
void Chapter::onEnter(){
    CCLayer::onEnter();
    
    // 5 difficulty
    //    ButtonSprite* noob = ButtonSprite::createButtonSprite("easyChapter.png");
    //    noob->setPosition(ccp(320, 480));
    //    noob->setOnClickListener(this, click_selector(Chapter::noobClicked));
    //    addChild(noob);
    
    // bg
    CCSprite* bgSprite = CCSprite::create("chapterBg.png");
    bgSprite->setAnchorPoint(ccp(0, 0));
    addChild(bgSprite);
    
    
    // some button
    CCMenuItemImage* noobBtn = CCMenuItemImage::create("noob.png","noobSelected.png", this, menu_selector(Chapter::noobBtnClicked));
    noobBtn->setPosition(ccp(322, 760));
    
    CCMenuItemImage* easyBtn = CCMenuItemImage::create("easy.png","easySelected.png",this,menu_selector(Chapter::easyBtnClicked));
    easyBtn->setPosition(ccp(322, 617));
    
    CCMenuItemImage* normalBtn = CCMenuItemImage::create("normal.png","normalSelected.png",this,
                                                         menu_selector(Chapter::noobBtnClicked));
    normalBtn->setPosition(ccp(324, 475));
    
    
    CCMenuItemImage* expertBtn = CCMenuItemImage::create("expert.png","expertSelected.png",this,menu_selector(Chapter::expertBtnClicked));
    expertBtn->setPosition(ccp(322, 333));
    
    CCMenuItemImage* challengeBtn = CCMenuItemImage::create("challenge.png", "challengeSelected.png",this,menu_selector(Chapter::challengeBtnClicked));
    challengeBtn->setPosition(ccp(322, 191));
    
    CCMenu* pMenu = CCMenu::create(noobBtn,easyBtn,normalBtn,expertBtn,challengeBtn,NULL);
    pMenu->setPosition(ccp(0, 0));
    
    addChild(pMenu);
    
    // set a  back button
    ButtonSprite* backBtn = ButtonSprite::createButtonSprite(c_preLevel);
    backBtn->setOnClickListener(this,click_selector(Chapter::backBtnClicked));
    backBtn->setPosition(ccp(20, 930));
    addChild(backBtn);
    
    
    setKeypadEnabled(true);
}

void Chapter::backBtnClicked()
{
    CCScene* pScene = CCScene::create();
    
    MainMenu* pLayer = new MainMenu;
    pLayer->autorelease();
    
    pScene->addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(pScene);
}

// Callback
//void Chapter::noobClicked()
//{
//    //  to Game
//    GameScene* pScene = new GameScene(1,1);
//    pScene->autorelease();
//    CCDirector::sharedDirector()->replaceScene(pScene);
//
//}

//
//---------------------
void Chapter::noobBtnClicked(CCObject* sender){
    GameScene* pScene = new GameScene(1,1);
    pScene->autorelease();
    CCDirector::sharedDirector()->replaceScene(pScene);
}
void Chapter::easyBtnClicked(CCObject* sender){
    GameScene* pScene = new GameScene(2,1);
    pScene->autorelease();
    CCDirector::sharedDirector()->replaceScene(pScene);
}
void Chapter::normalBtnClicked(CCObject* sender){
    GameScene* pScene = new GameScene(3,1);
    pScene->autorelease();
    CCDirector::sharedDirector()->replaceScene(pScene);
}
void Chapter::expertBtnClicked(CCObject* sender){
    GameScene* pScene = new GameScene(4,1);
    pScene->autorelease();
    CCDirector::sharedDirector()->replaceScene(pScene);
}
void Chapter::challengeBtnClicked(CCObject* sender){
    GameScene* pScene = new GameScene(5,1);
    pScene->autorelease();
    CCDirector::sharedDirector()->replaceScene(pScene);
}

void Chapter::keyBackClicked()
{
    // to mainmenu scene
    CCScene* pScene = CCScene::create();
    
    MainMenu* pLayer = new MainMenu;
    pLayer->autorelease();
    pScene->addChild(pLayer);
    
    CCDirector::sharedDirector()->replaceScene(pScene);
}