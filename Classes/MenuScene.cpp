//
//  MenuScene.cpp
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/07.
//
//

#include "MenuScene.h"
#include "MainScene.h"

USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = MenuScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();
    
    // 終了ボタン
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MenuScene::menuCloseCallback, this));
	closeItem->setPosition(Point(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                 origin.y + closeItem->getContentSize().height/2));

    // スタートボタン
    auto startBtn = MenuItemImage::create(
                                          "startBtn.png",
                                          "startBtn_press.png",
                                          CC_CALLBACK_1(MenuScene::pressStartBtn, this));
    startBtn->setScale(1.5f);
    startBtn->setPosition(Point(visibleSize.width/2 + origin.x,
                                visibleSize.height/2 + origin.y - 100));
    
    auto menu = Menu::create(closeItem, startBtn, NULL);
    menu->setPosition(Point::ZERO);
    this->addChild(menu, 1);
    
    
    auto label = LabelTTF::create("シューティングゲーム", "Times", 34);
    label->setPosition(Point(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height/2 + 100));
    this->addChild(label, 1);
    
    return true;
}


void MenuScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif
    
    Director::getInstance()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void MenuScene::pressStartBtn(cocos2d::Ref *sender)
{
    Scene *nextScene = TransitionFade::create(1.0f, MainScene::createScene());
    if(nextScene){
        Director::getInstance()->replaceScene(nextScene);
    }
}
