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
    void powerShot();
    void move(cocos2d::Acceleration* acc);
    void displayChargeBox();
    void updateChargeBox();
    void resetChargeBox();
    int getChargeTime();
    void removeFromParent() override;
    void destroy();
    
private:
    cocos2d::ProgressTimer* chargeBox;
    int chargeTime;
};

#endif /* defined(__CharGame__Player__) */
