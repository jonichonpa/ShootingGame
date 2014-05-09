//
//  Cloud.cpp
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/09.
//
//

#include "Cloud.h"

USING_NS_CC;

Cloud* Cloud::create()
{
    static SpriteBatchNode* cloudBatchNode = SpriteBatchNode::create("Cloud.png");
    
    Cloud *cloud = new Cloud();
    if (cloud && cloud->init()){
        cloud->autorelease();
        return cloud;
    }
    CC_SAFE_DELETE(cloud);
    return nullptr;
}

bool Cloud::init()
{
    Sprite::init();
    
    SpriteFrameCache* cache = SpriteFrameCache::getInstance();
    cache->addSpriteFramesWithFile("Cloud.plist");
    
    // 雲の形をランダムに取得
    std::string frameName = StringUtils::format("Cloud_%02d.png",rand() % 5 + 1);
    this->initWithSpriteFrame(cache->getSpriteFrameByName(frameName));
    scheduleUpdate();
    
    return true;
}

void Cloud::update(float delta)
{
    Size size = Director::getInstance()->getVisibleSize();
    
    setPositionY(getPositionY()+5);
    if (getPositionY() > size.height + 100) {
        removeFromParent();
    };
}