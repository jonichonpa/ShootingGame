//
//  Player.cpp
//  myProject
//
//  Created by 遠藤 和樹 on 2014/05/02.
//
//

#include "Player.h"

USING_NS_CC;

Player* Player::create()
{
    Player *player = new Player();
    if (player && player->init()){
        player->autorelease();
        player->setScale(2.0f);
        return player;
    }
    CC_SAFE_DELETE(player);
    return nullptr;
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