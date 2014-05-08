//
//  NormalShot.cpp
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/08.
//
//

#include "NormalShot.h"
#include "BitMaskConfig.h"

USING_NS_CC;

NormalShot* NormalShot::create()
{
    NormalShot *normalShot = new NormalShot();
    if (normalShot && normalShot->init()) {
        normalShot->setScale(2.0f);
        normalShot->initPhysicsBody();
        normalShot->autorelease();
        return normalShot;
    }
    CC_SAFE_DELETE(normalShot);
    return nullptr;
}

void NormalShot::initPhysicsBody()
{
    auto pb = PhysicsBody::createBox(Size(14,14));
    pb->setRotationEnable(false);
    pb->setCategoryBitmask(NORMALSHOT_CATEGORY);
    pb->setCollisionBitmask(0);
    pb->setContactTestBitmask(ENEMY_CATEGORY);
    pb->setVelocityLimit(0.0f);
    pb->setDynamic(true);
    setPhysicsBody(pb);
}

void NormalShot::run()
{
    SpriteBatchNode* spritebatch = SpriteBatchNode::create("Shot.png");
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("Shot.plist");
    Vector<SpriteFrame*> animFrames(3);
    for (int i = 1 ; i < 4 ; i++) {
        std::string str = StringUtils::format("NormalShot_%02d.png",i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.01f);
    runAction(RepeatForever::create(Animate::create(animation)));
    scheduleUpdate();
}
