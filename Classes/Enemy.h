//
//  Enemy.h
//  myProject
//
//  Created by 遠藤 和樹 on 2014/05/02.
//
//

#ifndef __CharGame__Enemy__
#define __CharGame__Enemy__

#include "cocos2d.h"

class Enemy : public cocos2d::Sprite
{
public:
    static Enemy* create();
    void initPhysicsBody();
    void run();
    void update(float delta);
    void removeFromParent() override;
    void destroy();
};

#endif /* defined(__CharGame__Enemy__) */
