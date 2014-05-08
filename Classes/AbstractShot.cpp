//
//  AbstractShot.cpp
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/08.
//
//

#include "AbstractShot.h"

USING_NS_CC;

void AbstractShot::update(float delta)
{
    auto action = MoveTo::create(0.01f, Point(getPositionX(), getPositionY() + 5));
    runAction(action);
}

void AbstractShot::destroy()
{
    removeFromParent();
}