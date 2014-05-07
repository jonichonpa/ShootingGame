//
//  Enemy.cpp
//  myProject
//
//  Created by 遠藤 和樹 on 2014/05/02.
//
//

#include "Enemy.h"

USING_NS_CC;

Enemy* Enemy::create()
{
    Enemy *enemy = new Enemy();
    if (enemy && enemy->init()) {
        enemy->setScale(2.0f);
        enemy->autorelease();
        return enemy;
    }
    CC_SAFE_DELETE(enemy);
    return nullptr;
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
        //CCLOG("%s",str.c_str());
    }
    Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.01f);
    runAction(RepeatForever::create(Animate::create(animation)));
}

void Enemy::move()
{
    this->setPositionY(this->getPositionY()-5);
}

void Enemy::moveSine()
{
    MoveTo *move = MoveTo::create(3.0f, Point(0,this->getPositionY()));
    auto sin = EaseSineInOut::create(move);
    this->runAction(sin);
}

