//
//  Player.h
//  myProject
//
//  Created by 遠藤 和樹 on 2014/05/02.
//
//

#ifndef __CharGame__Player__
#define __CharGame__Player__

#include "cocos2d.h"

class Player : public cocos2d::Sprite
{
public:    
    static Player* create();
    void initPhysicsBody();
    void run();
    void shot();
    void move(cocos2d::Acceleration* acc);
};

#endif /* defined(__CharGame__Player__) */
