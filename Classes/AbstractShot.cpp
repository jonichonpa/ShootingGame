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
    Size size = Director::getInstance()->getOpenGLView()->getVisibleSize();
    setPositionY(getPositionY() + 5);
    if (getPositionY() > size.height) {
        removeFromParent();
    }
}