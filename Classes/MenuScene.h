//
//  MenuScene.h
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/07.
//
//

#ifndef __CharGame__MenuScene__
#define __CharGame__MenuScene__

#include "cocos2d.h"

class MenuScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);
    
    void pressStartBtn(cocos2d::Ref* sender);
};

#endif /* defined(__CharGame__MenuScene__) */
