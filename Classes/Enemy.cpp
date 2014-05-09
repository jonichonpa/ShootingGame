//
//  Enemy.cpp
//  myProject
//
//  Created by 遠藤 和樹 on 2014/05/02.
//
//

#include "Enemy.h"
#include "BitMaskConfig.h"
#include "TagConfig.h"
#include "SimpleAudioEngine.h"

USING_NS_CC;

static const int ENEMY_ANIMATION_TAG = 1;

Enemy* Enemy::create()
{
    static SpriteBatchNode* spriteBatch1 = SpriteBatchNode::create("enemy.png");
    static SpriteBatchNode* spriteBatch2 = SpriteBatchNode::create("Explosion.png");
    
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
    auto pb = PhysicsBody::createBox(Size(30,30));
    pb->setRotationEnable(false);
    pb->setCategoryBitmask(ENEMY_CATEGORY);
    pb->setCollisionBitmask(0);
    pb->setContactTestBitmask(PLAYER_CATEGORY | NORMALSHOT_CATEGORY | POWERSHOT_CATEGORY);
    pb->setVelocityLimit(0.0f);
    pb->setDynamic(true);
    pb->setTag(ENEMY_TAG);
    this->setPhysicsBody(pb);
}

void Enemy::run()
{
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("enemy.plist");
    Vector<SpriteFrame*> animFrames(8);
    for (int i = 1 ; i < 9 ; i++) {
        std::string str = StringUtils::format("enemy_%02d.png",i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.01f);
    Action *action = RepeatForever::create(Animate::create(animation));
    action->setTag(ENEMY_ANIMATION_TAG);
    runAction(action);
    scheduleUpdate();
}

void Enemy::update(float delta)
{
    setPositionY(getPositionY()-5);
    if (getPositionY() < 0) {
        removeFromParent();
    };
}
    
void Enemy::removeFromParent()
{
    // 爆発アニメーションの間衝突を避ける
    getPhysicsBody()->setContactTestBitmask(0x00000000);
    
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("Explosion.plist");
    Vector<SpriteFrame*> animFrames(11);
    for (int i = 1 ; i < 11 ; i++) {
        std::string str = StringUtils::format("explosion_%02d.png",i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
    stopActionByTag(ENEMY_ANIMATION_TAG);
    Animate *animate = Animate::create(animation);
    CallFunc *func = CallFunc::create(CC_CALLBACK_0(Enemy::destroy,this));
    runAction(Sequence::create(animate,func,NULL));
}

void Enemy::destroy()
{
    Sprite::removeFromParent();
}
