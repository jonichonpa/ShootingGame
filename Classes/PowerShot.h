//
//  PowerShot.h
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/09.
//
//

#ifndef __CharGame__PowerShot__
#define __CharGame__PowerShot__

#include "cocos2d.h"
#include "AbstractShot.h"

class PowerShot : public AbstractShot
{
public:
    static PowerShot* create();
    virtual void run();
    virtual void initPhysicsBody();
};

#endif /* defined(__CharGame__PowerShot__) */
