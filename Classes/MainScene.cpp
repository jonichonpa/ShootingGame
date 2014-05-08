//
//  MainScene.cpp
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/07.
//
//

#include "MainScene.h"
#include "NormalShot.h"
#include "BitMaskConfig.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    auto scene = Scene::createWithPhysics();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    
    player = Player::create();
    player->setPosition(100,100);
    this->addChild(player);
    player->run();
    
    this->scheduleUpdate();
    srand((unsigned)time(nullptr));
    
    // ジャイロセンサー
    Device::setAccelerometerEnabled(true);
    auto listener = EventListenerAcceleration::create(CC_CALLBACK_2(MainScene::onGyro, this));
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    // 衝突検知
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(MainScene::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    // タッチによるショット
    setChargeSystem();
    
    return true;
}

void MainScene::setChargeSystem()
{
    auto listener = EventListenerTouchOneByOne::create();
    
    // イベントに対するメソッドの設定
    listener->onTouchBegan = CC_CALLBACK_2(MainScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(MainScene::onTouchEnded, this);
    
    // ディスパッチャーに登録
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

bool MainScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    chargeSEL = schedule_selector(MainScene::charge);
    this->schedule(chargeSEL, 1.0f);
    return true;
}

void MainScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    this->unschedule(chargeSEL);
    player->shot();
}

void MainScene::charge(float f)
{
    //CCLOG("charge");
}

void MainScene::update(float delta)
{
    encountEnemy();
}

void MainScene::encountEnemy()
{
    // 敵がランダム出現
    if (rand() % 10 == 1)
	{
        Enemy *enemy = Enemy::create();
        enemy->setPosition(rand() % 500 + 50, 1000);
        this->addChild(enemy);
        enemy->run();
	}
}

void MainScene::onGyro(cocos2d::Acceleration *acc, cocos2d::Event *event)
{
    player->move(acc);
}

bool MainScene::onContactBegin(cocos2d::PhysicsContact &contact)
{
    auto pb_a = contact.getShapeA()->getBody();
    auto pb_b = contact.getShapeB()->getBody();
    //auto node_a = pb_a->getNode();
    //auto node_b = pb_b->getNode();
    CCLOG("%x %x",pb_a->getCategoryBitmask(),pb_b->getCategoryBitmask());
    if(pb_a->getCategoryBitmask() == ENEMY_CATEGORY && pb_b->getCategoryBitmask() == NORMALSHOT_CATEGORY){
        auto node_a = (Enemy*) pb_a->getNode();
        node_a->destroy();
        auto node_b = (NormalShot*) pb_b->getNode();
        node_b->destroy();
    } else {
        log("contact");
    }
    return true;
}