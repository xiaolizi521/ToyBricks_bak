//
//  TargetArea.h
//  ToyBricks
//
//  Created by user on 13-4-6.
//
//

#ifndef __ToyBricks__TargetArea__
#define __ToyBricks__TargetArea__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;


class TargetArea : public CCNode
{
public:
    TargetArea();
    
    int m_indexX;
    int m_indexY;
    
    int m_row;
    int m_column;
    
    void setIndexX(int ix);
    void setIndexY(int iy);
    void setRow(int row);
    void setColumn(int column);
    int getIndexX(){return m_indexX;}
    int getIndexY(){return m_indexY;}
    int getRow(){return m_row;}
    int getColumn(){return m_column;}
    
    virtual void onEnter();
};


#endif /* defined(__ToyBricks__TargetArea__) */
