//
//  PowerShot.cpp
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/09.
//
//

#include "PowerShot.h"
#include "BitMaskConfig.h"
#include "TagConfig.h"

USING_NS_CC;

PowerShot* PowerShot::create()
{
    static SpriteBatchNode* spritebatch = SpriteBatchNode::create("Shot.png");
    
    PowerShot *powerShot = new PowerShot();
    if (powerShot && powerShot->init()) {
        powerShot->setScale(2.0f);
        powerShot->initPhysicsBody();
        powerShot->autorelease();
        return powerShot;
    }
    CC_SAFE_DELETE(powerShot);
    return nullptr;
}

void PowerShot::initPhysicsBody()
{
    auto pb = PhysicsBody::createBox(Size(26,26));
    pb->setRotationEnable(false);
    pb->setCategoryBitmask(POWERSHOT_CATEGORY);
    pb->setCollisionBitmask(0);
    pb->setContactTestBitmask(ENEMY_CATEGORY);
    pb->setVelocityLimit(0.0f);
    pb->setDynamic(true);
    pb->setTag(POWERSHOT_TAG);
    setPhysicsBody(pb);
}

void PowerShot::run()
{
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("Shot.plist");
    Vector<SpriteFrame*> animFrames(4);
    for (int i = 1 ; i < 5 ; i++) {
        std::string str = StringUtils::format("PowerShot_%02d.png",i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.01f);
    runAction(RepeatForever::create(Animate::create(animation)));
    scheduleUpdate();
}
