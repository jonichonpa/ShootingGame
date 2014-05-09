//
//  Cloud.h
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/09.
//
//

#ifndef __CharGame__Cloud__
#define __CharGame__Cloud__

#include "cocos2d.h"

class Cloud : public cocos2d::Sprite
{
public:
    static Cloud* create();
    virtual bool init();
    void update(float delta);
};

#endif /* defined(__CharGame__Cloud__) */
