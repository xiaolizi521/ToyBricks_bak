//
//  MainMenu.cpp
//  ToyBricks
//
//  Created by user on 13-4-2.
//
//

#include "MainMenu.h"
#include "ButtonSprite.h"
#include "Chapter.h"
#include "Util.h"
#include "GameResources.h"
#include "Model.h"

MainMenu::MainMenu()
{}
MainMenu::~MainMenu(){}

void MainMenu::onEnter()
{
    CCLayer::onEnter();
    
    // main bg
    CCSprite* bgSprite = CCSprite::create("mainMenubg.png");
    bgSprite->setAnchorPoint(ccp(0, 0));
    addChild(bgSprite);
    
    loadGameResources();
    
//    ButtonSprite* playBtn = ButtonSprite::createButtonSprite("play.png");
//    playBtn->setPosition(ccp(320, 480));
//    playBtn->setOnClickListener(this,click_selector(MainMenu::playBtnClicked));
//    addChild(playBtn);
    
    CCMenuItemImage* playBtn = CCMenuItemImage::create("play.png", "playSelected.png", this, menu_selector(MainMenu::playBtnClicked));
    playBtn->setPosition(ccp(323, 625));
    
    CCMenuItemImage* moreBtn = CCMenuItemImage::create("more.png","moreSelected.png", this, menu_selector(MainMenu::moreBtnClicked));
    moreBtn->setPosition(ccp(319, 453));
    
    CCMenu* pMenu = CCMenu::create(playBtn,moreBtn,NULL);
    pMenu->setPosition(ccp(0, 0));
    
    addChild(pMenu);
    
    
    
    //  测试镜像
    CCSprite* testSprite = CCSprite::create("moreSelected.png");
   // CCSize size = testSprite->getContentSize();
  //  testSprite->setPosition(ccp(size.width, size.height));
    testSprite->setAnchorPoint(ccp(0, 0));
   testSprite->setFlipX(true);
//    testSprite->setFlipY(true);
 //   testSprite->setRotation(10);
    addChild(testSprite);
    
}

void MainMenu::playBtnClicked(CCObject* pSender)
{
    
    CCScene* scene = CCScene::create();
    Chapter* chapter = new Chapter;
    chapter->autorelease();
    scene->addChild(chapter);
    
    CCDirector::sharedDirector()->replaceScene(scene);
    
}
void MainMenu::moreBtnClicked(CCObject* pSender)
{
}


//void MainMenu::playBtnClicked()
//{
//    CCLog("I am clicked !!");
//    
//    // to select difficulty
//    CCScene* scene = CCScene::create();
//    Chapter* chapter = new Chapter;
//    chapter->autorelease();
//    scene->addChild(chapter);
//    
//    CCDirector::sharedDirector()->replaceScene(scene);
//}


void MainMenu::loadGameResources()
{
    CCTextureCache* cache = CCTextureCache::sharedTextureCache();
    cache->addImage(c_s1);
    cache->addImage(c_s2);
    cache->addImage(c_s3);
    cache->addImage(c_s4);
    cache->addImage(c_s5);
    cache->addImage(c_s6);
    cache->addImage(c_s7);
    cache->addImage(c_shadow_bg);
    cache->addImage(c_target_image);
    cache->addImage(c_nextLevel);
    cache->addImage(c_preLevel);
    cache->addImage(c_reset);
    cache->addImage(c_selectLevel);
    cache->addImage(c_share);
    cache->addImage(c_home);
    cache->addImage(c_itemBg);
    cache->addImage(c_dialog_home);
    cache->addImage(c_dialog_next);
    cache->addImage(c_dialog_reset);
    cache->addImage(c_gamebg);
}