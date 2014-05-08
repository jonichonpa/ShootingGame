//
//  Player.cpp
//  myProject
//
//  Created by 遠藤 和樹 on 2014/05/02.
//
//

#include "Player.h"
#include "NormalShot.h"
#include "BitMaskConfig.h"

USING_NS_CC;

Player* Player::create()
{
    Player *player = new Player();
    if (player && player->init()){
        player->autorelease();
        player->setScale(2.0f);
        player->initPhysicsBody();
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
}

void Player::initPhysicsBody()
{
    auto pb = PhysicsBody::createBox(Size(30,40));
    pb->setDynamic(true);
    pb->setRotationEnable(false);
    pb->setVelocityLimit(0.0f);
    pb->setCollisionBitmask(0);
    pb->setCategoryBitmask(PLAYER_CATEGORY);
    pb->setContactTestBitmask(ENEMY_CATEGORY);
    this->setPhysicsBody(pb);
}

void Player::run()
{
    SpriteBatchNode* spritebatch = SpriteBatchNode::create("spaceships.png");
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("spaceships.plist");
    Vector<SpriteFrame*> animFrames(8);
    for (int i = 1 ; i < 9 ; i++) {
        std::string str = StringUtils::format("spaceship_%02d.png",i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.01f);
    runAction(RepeatForever::create(Animate::create(animation)));
}

void Player::shot()
{
    NormalShot *normalShot = NormalShot::create();
    normalShot->setPosition(getPosition());
    getParent()->addChild(normalShot);
    normalShot->run();
}

void Player::move(cocos2d::Acceleration *acc)
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    // ジャイロセンサーの横軸の変化量に多少重みをかけて調整
    float nextX = getPositionX() + (float) acc->x * 10;
    float halfWidth = getContentSize().width / 2;
    // プレーヤーの体が画面外にならないなら移動する
    if (nextX - halfWidth < 0 || nextX + halfWidth > visibleSize.width) return;
    setPositionX(nextX);
}