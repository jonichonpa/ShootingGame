//
//  Player.cpp
//  myProject
//
//  Created by 遠藤 和樹 on 2014/05/02.
//
//

#include "Player.h"
#include "NormalShot.h"
#include "PowerShot.h"
#include "BitMaskConfig.h"

USING_NS_CC;

static const int CHARGE_ANIMATION_TAG = 2;
static const int PLAYER_ANIMATION_TAG = 4;
static const int PLAYER_DEATH_TAG = 3;

Player* Player::create()
{
    static SpriteBatchNode* spritebatch = SpriteBatchNode::create("spaceships.png");
    static SpriteBatchNode* deathAnimbatch = SpriteBatchNode::create("death.png");
    
    Player *player = new Player();
    if (player && player->init()){
        player->autorelease();
        player->setScale(2.0f);
        player->initPhysicsBody();
        player->chargeTime = 0;
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

void Player::displayChargeBox()
{
    auto size = Director::getInstance()->getVisibleSize();
    auto progressSprite = Sprite::create("progress.png");
    auto contentSize = progressSprite->getContentSize();
    chargeBox = ProgressTimer::create(progressSprite);
    chargeBox->setPosition(size.width - contentSize.width - 8, size.height - contentSize.height - 8);
    chargeBox->setType(ProgressTimer::Type::BAR);
    chargeBox->setAnchorPoint(Point::ZERO);
    chargeBox->setMidpoint(Point(1,0));
    chargeBox->setBarChangeRate(Point(0,1));
    chargeBox->setPercentage(0);
    getParent()->addChild(chargeBox);
}

void Player::updateChargeBox()
{
    chargeTime++;
    //CCLOG("%d",chargeTime);
    auto progress = ProgressTo::create(1.0f, (float)chargeTime/3*100);
    progress->setTag(CHARGE_ANIMATION_TAG);
    chargeBox->runAction(progress);
}

void Player::run()
{
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("spaceships.plist");
    Vector<SpriteFrame*> animFrames(8);
    for (int i = 1 ; i < 9 ; i++) {
        std::string str = StringUtils::format("spaceship_%02d.png",i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.01f);
    Action* action = RepeatForever::create(Animate::create(animation));
    action->setTag(PLAYER_ANIMATION_TAG);
    runAction(action);
}

void Player::shot()
{
    NormalShot *normalShot = NormalShot::create();
    normalShot->setPosition(getPosition());
    getParent()->addChild(normalShot);
    normalShot->run();
    
    resetChargeBox();
}

void Player::powerShot()
{
    PowerShot *powerShot = PowerShot::create();
    powerShot->setPosition(getPosition());
    getParent()->addChild(powerShot);
    powerShot->run();
    
    resetChargeBox();
}

void Player::resetChargeBox()
{
    chargeBox->stopActionByTag(CHARGE_ANIMATION_TAG);
    chargeTime = 0;
    chargeBox->setPercentage(0);
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

int Player::getChargeTime()
{
    return chargeTime;
}

void Player::removeFromParent()
{
    // 爆発アニメーションの間衝突を避ける
    getPhysicsBody()->setContactTestBitmask(0x00000000);
    
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("death.plist");
    Vector<SpriteFrame*> animFrames(14);
    for (int i = 1 ; i < 15 ; i++) {
        std::string str = StringUtils::format("death_%02d.png",i);
        SpriteFrame* frame = SpriteFrameCache::getInstance()->getSpriteFrameByName(str);
        animFrames.pushBack(frame);
    }
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.05f);
    stopActionByTag(PLAYER_ANIMATION_TAG);
    Animate *animate = Animate::create(animation);
    //auto func = [=](){Sprite::removeFromParent();};
    CallFunc *func = CallFunc::create(CC_CALLBACK_0(Player::destroy,this));
    runAction(Sequence::create(animate,func,NULL));
}

void Player::destroy()
{
    Sprite::removeFromParent();
}