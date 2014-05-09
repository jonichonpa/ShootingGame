//
//  MainScene.cpp
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/07.
//
//

#include "MainScene.h"
#include "GameOverScene.h"
#include "NormalShot.h"
#include "BitMaskConfig.h"
#include "PowerShot.h"
#include "TagConfig.h"
#include "Background.h"

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
    
    // 背景はスカイブルー
    //LayerColor* layer = cocos2d::LayerColor::create(Color4B(135,206,235,210));
    //this->addChild(layer);
    Background* background = Background::create();
    this->addChild(background);
    
    player = Player::create();
    player->setPosition(100,100);
    this->addChild(player);
    player->displayChargeBox();
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
    player->updateChargeBox();
    this->schedule(chargeSEL, 1.0f);
    return true;
}

void MainScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    this->unschedule(chargeSEL);
    if(player->getChargeTime() > 3) {
        player->powerShot();
    } else {
        player->shot();
    }
}

void MainScene::charge(float f)
{
    player->updateChargeBox();
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
    auto result = pb_a->getCategoryBitmask() + pb_b->getCategoryBitmask();
    // ノーマルショットと敵
    if(result == NORMALSHOT_CATEGORY + ENEMY_CATEGORY) {
        pb_a->getNode()->removeFromParent();
        pb_b->getNode()->removeFromParent();
    } else if (result == POWERSHOT_CATEGORY + ENEMY_CATEGORY) {
    // パワーショットと敵
        auto enemy = pb_a->getTag() == ENEMY_TAG ? (Enemy*)pb_a->getNode() : (Enemy*)pb_b->getNode();
        enemy->removeFromParent();
    } else {
    // プレーヤーと敵
        player->removeFromParent();
        Scene *nextScene = TransitionFade::create(1.0f, GameOverScene::createScene());
        if(nextScene){
            Director::getInstance()->replaceScene(nextScene);
        }
    }
    return true;
}