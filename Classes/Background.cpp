//
//  Background.cpp
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/09.
//
//

#include "Background.h"
#include "Cloud.h"

USING_NS_CC;

Background* Background::create()
{
    Background *background = new Background();
    if (background && background->init()){
        background->autorelease();
        return background;
    }
    CC_SAFE_DELETE(background);
    return nullptr;
}

bool Background::init()
{
    this->initWithColor(Color4B(135,206,235,210));
    scheduleUpdate();
    return true;
}

void Background::update(float delta)
{
    Size size = Director::getInstance()->getVisibleSize();
    
    if(rand() % 100 == 1){
        auto cloud = Cloud::create();
        cloud->setPosition(rand() % (int)size.width, -100);
        addChild(cloud);
    }
}