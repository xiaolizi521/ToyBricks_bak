//
//  LevelScene.h
//  ToyBricks
//
//  Created by user on 13-4-10.
//
//

#ifndef __ToyBricks__LevelScene__
#define __ToyBricks__LevelScene__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;



class LevelLayer;
class InfoLevelLayer;
class LevelScene : public CCScene
{
protected:
    
    LevelLayer* m_firstLayer;
    LevelLayer* m_secondLayer;
    InfoLevelLayer* m_infoLayer;
    
    int m_level;
    int m_chapter;
    
    int m_currentPage;
    int m_totalPage;
    
    bool m_isAnimationing;
    int m_totalLevelCount;
public:
    
    LevelScene(int chapter,int level);
    virtual void onEnter();
    virtual ~LevelScene();
    
    //
    int getCurrentPage(){return m_currentPage;}
    int getTotalPage(){return m_totalPage;}
    int computerCurrentPage();

    void toNextPage();
    void toPrePage();
    
    void afterPreAnimation();
    void afterNextAnimation(CCNode* n, void* p);
};



#endif /* defined(__ToyBricks__LevelScene__) */
