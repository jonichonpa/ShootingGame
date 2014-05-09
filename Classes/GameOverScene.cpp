//
//  GameOverScene.cpp
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/09.
//
//

#include "GameOverScene.h"
#include "MenuScene.h"

USING_NS_CC;

Scene* GameOverScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameOverScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameOverScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    auto label = LabelTTF::create("ゲームオーバーだよ〜", "Times", 34);
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height/2));
    this->addChild(label, 1);
    
    auto listener = EventListenerTouchOneByOne::create();
    
    // イベントに対するメソッドの設定
    listener->onTouchBegan = CC_CALLBACK_2(GameOverScene::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameOverScene::onTouchEnded, this);
    
    // ディスパッチャーに登録
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    return true;
}

bool GameOverScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    return true;
}

void GameOverScene::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
    Scene *nextScene = TransitionFade::create(1.0f, MenuScene::createScene());
    if(nextScene){
        Director::getInstance()->replaceScene(nextScene);
    }
}