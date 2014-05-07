//
//  Enemy.h
//  myProject
//
//  Created by 遠藤 和樹 on 2014/05/02.
//
//

#ifndef __myProject__Enemy__
#define __myProject__Enemy__

#include <cocos2d.h>

class Enemy : public cocos2d::Sprite
{
public:
    static Enemy* create();
    void run();
    void move();
    void moveSine();
};

#endif /* defined(__myProject__Enemy__) */
