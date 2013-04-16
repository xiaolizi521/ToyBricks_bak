//
//  TileSprite.h
//  Zuma_V4
//
//  Created by user on 13-1-19.
//
//

#ifndef __Zuma_V4__TileSprite__
#define __Zuma_V4__TileSprite__

#include <iostream>
#include "cocos2d.h"
using namespace cocos2d;

/*
 *  TileSprite:
 *
 */
class TileSprite: public CCSprite {

protected:
	//当前是第几帧
	int m_currentIndex;

	//保存帧的数组
	CCArray* m_frameArray;

	int m_columns;
	int m_rows;

	TileSprite() {
	}
	;

	/*
	 *  初始化方法
	 */
	void tileSpriteInit(const char* fileName, int columns, int rows);
    
    void tileSpriteInit(CCTexture2D* texture, int columns, int rows);
public:

	virtual ~TileSprite();
	virtual void onEnter();

	/*
	 *  显示第几帧
	 */
	void setCurrentIndex(int mIndex);

	/*
	 *  创建 TileSprite 的方法
	 */
	static TileSprite* createTileSprite(const char* fileName, int columns, int rows);
};

#endif /* defined(__Zuma_V4__TileSprite__) */
