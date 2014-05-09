//
//  Background.h
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/09.
//
//

#ifndef __CharGame__Background__
#define __CharGame__Background__

#include "cocos2d.h"

class Background : public cocos2d::LayerColor
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static Background* create();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    void update(float delta);
};

#endif /* defined(__CharGame__Background__) */
