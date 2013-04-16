//
//  BorderModel.h
//  ToyBricks
//
//  Created by user on 13-4-15.
//
//

#ifndef __ToyBricks__BorderModel__
#define __ToyBricks__BorderModel__

#include <iostream>
#include "Model.h"
class BorderModel : public Model
{
protected:
    // use to set bg
    int m_transformIndex;
    int m_backIndex;
    
public:
    
    BorderModel();
    virtual void onEnter();
    
    void addBorder();
    void transform(int tIndex,CCSprite* sprite);
    
    void setTransformIndex(int idx){m_transformIndex = idx;};
    void setBackIndex(int idx){m_backIndex = idx;};
    
    
    // override
    void moveToDir(int dir);
  //  bool checkCover();
    
    void moveToPropPosition();
    
    
    Model* createCustomModel();
    
    virtual ~BorderModel();
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
};

#endif /* defined(__ToyBricks__BorderModel__) */
