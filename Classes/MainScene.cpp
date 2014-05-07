//
//  MainScene.cpp
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/07.
//
//

#include "MainScene.h"

USING_NS_CC;

Scene* MainScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto label = LabelTTF::create("ゲーム画面", "Arial", 24);
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height - label->getContentSize().height));
    this->addChild(label, 1);
    
    setChargeSystem();
    
    player = Player::create();
    player->setPosition(100,100);
    this->addChild(player);
    player->run();
    
    this->scheduleUpdate();
    srand((unsigned)time(nullptr));
    
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
}

void MainScene::charge(float f)
{
    CCLOG("charge");
}

void MainScene::update(float delta)
{
    encountEnemy();
    moveEnemy();
}

void MainScene::encountEnemy()
{
    // 敵がランダム出現
    if (rand() % 10 == 1)
	{
        Enemy *enemy = Enemy::create();
        enemy->setPosition(rand() % 500 + 50, 1000);
        enemies.pushBack(enemy);
        this->addChild(enemy);
        enemy->run();
	}
}

void MainScene::moveEnemy()
{
    // 敵の移動と消去
    for(Enemy *enemy : enemies){
        enemy->move();
        if (enemy->getPositionY() < -30) {
            enemy->removeFromParent();
        }
    }
}
