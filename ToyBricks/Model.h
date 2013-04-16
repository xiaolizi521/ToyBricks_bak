//
//  Model.h
//  ToyBricks
//
//  Created by user on 13-4-2.
//
//

#ifndef __ToyBricks__Model__
#define __ToyBricks__Model__

#include <iostream>
#include <vector>
#include "cocos2d.h"
#include "Util.h"
#include "GameResources.h"
using namespace cocos2d;
using namespace std;

//
//   a 5X5  area
//
//
class BorderModel;
class Model : public CCNode,public CCTouchDelegate
{
protected:
    
    int m_array[25];
    
    //  square count
    int m_length;
    
    // array in map Array
    int* m_arrayInMapArray;
    
    vector<CCRect> m_rectVec;
    
    //  parsed indexX,indexY
    int m_indexX;
    int m_indexY;
    
    // collsionBound, use to check the valid touch
    CCRect m_collisionBox;
    
    //  pre position;
    int m_preIndexX;
    int m_preIndexY;
    
    //  use to prevent over bounds
    int m_minY;
    int m_maxY;
    int m_minX;
    int m_maxX;
    
    // use to load different texture
    int m_color;
    
    BorderModel* m_borthor;
public:
    
    enum{
        kUp = 1,
        kDown,
        kLeft,
        kRight
    };
    
    
    CCRect getCollisionBox() const;
    
    Model();
    virtual ~Model();
    
    virtual void onEnter();
    virtual void onExit();
    
    
    int* getArray();
    vector<CCRect>* getRectVec();
    
    bool isTouched(const float x,const float y);
    bool isTouched(const CCPoint& point);
    bool isRepeadWithMapArray();
    
    
    // return direction;
    int getDirection(int* xy);
    
    virtual void moveToDir(int dir);
    
    void afterMove();
    
    // restore the pre position
    void restorePre();
    
    // set indexX indexY
    void setIndexX(int ix);
    int getIndexX(){return m_indexX;};
    void setIndexY(int iy);
    int getIndexY(){return m_indexY;}
    void setArray(int* p, int length);
    void setColor(int c){ m_color = c;};
    void setBorthor(BorderModel* bor){m_borthor = bor;};

    // set array in mapArrayIndex
    void setArrayInMapIndex(int index,int mapIndex);
    
    // debug print
    void debugPrint();
    
    void printPosition();
    
    
    //   之前的代码
    void setPropPosition();
    
    void setBortherPropPosition();
    
    //  compute prop position
    void getResultXY(int* result,float reallyX,float reallyY);
    
    // compute bounds
    void computeBounds();
    
    
    //--------------------- CCTouchDelegate
    virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    // optional
    
    virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);
};

#endif /* defined(__ToyBricks__Model__) */
