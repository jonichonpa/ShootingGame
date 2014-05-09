//
//  GameOverScene.h
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/09.
//
//

#ifndef __CharGame__GameOverScene__
#define __CharGame__GameOverScene__

#include "cocos2d.h"

class GameOverScene : cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameOverScene);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
};

#endif /* defined(__CharGame__GameOverScene__) */
