//
//  AbstractShot.h
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/08.
//
//

#ifndef __CharGame__AbstractShot__
#define __CharGame__AbstractShot__

#include "cocos2d.h"

class AbstractShot : public cocos2d::Sprite
{
public:
    virtual void run() = 0;
    virtual void initPhysicsBody() = 0;
    void update(float delta);
    void destroy();
};

#endif /* defined(__CharGame__AbstractShot__) */
