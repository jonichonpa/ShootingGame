//
//  NormalShot.h
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/08.
//
//

#ifndef __CharGame__NormalShot__
#define __CharGame__NormalShot__

#include "cocos2d.h"
#include "AbstractShot.h"

class NormalShot : public AbstractShot
{
public:
    static NormalShot* create();
    virtual void run();
    virtual void initPhysicsBody();
};

#endif /* defined(__CharGame__NormalShot__) */
