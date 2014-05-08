//
//  Enemy.cpp
//  myProject
//
//  Created by 遠藤 和樹 on 2014/05/02.
//
//

#include "Enemy.h"
#include "BitMaskConfig.h"

USING_NS_CC;

Enemy* Enemy::create()
{
    Enemy *enemy = new Enemy();
    if (enemy && enemy->init()) {
        enemy->setScale(2.0f);
        enemy->initPhysicsBody();
        enemy->autorelease();
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return nullptr;
}

void Enemy::initPhysicsBody()
{
    auto pb = PhysicsBody::createBox(Size(24,30));
    pb->setRotationEnable(false);
    pb->setCategoryBitmask(ENEMY_CATEGORY);
    pb->setCollisionBitmask(0);
    pb->setContactTestBitmask(PLAYER_CATEGORY | NORMALSHOT_CATEGORY);
    pb->setVelocityLimit(0.0f);
    pb->setDynamic(true);
    this->setPhysicsBody(pb);
}

void Enemy::run()
{
    SpriteBatchNode* spritebatch = SpriteBatchNode::create("enemy.png");
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("enemy.plist");
    Vector<SpriteFrame*> animFrames(8);
    for (int i = 1 ; i < 9 ; i++) {
        std::string str = StringUtils::format("enemy_%02d.png",i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.01f);
    setTag(1);
    runAction(RepeatForever::create(Animate::create(animation)));
    scheduleUpdate();
}

void Enemy::update(float delta)
{
    this->setPositionY(this->getPositionY()-5);
}

void Enemy::destroy()
{
    SpriteBatchNode* spritebatch = SpriteBatchNode::create("Explosion.png");
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("Explosion.plist");
    Vector<SpriteFrame*> animFrames(10);
    for (int i = 1 ; i < 11 ; i++) {
        std::string str = StringUtils::format("explosion_%02d.png",i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
    stopAllActions();
    runAction(Animate::create(animation));
}

