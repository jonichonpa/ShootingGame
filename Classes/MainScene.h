//
//  MainScene.h
//  CharGame
//
//  Created by 遠藤 和樹 on 2014/05/07.
//
//

#ifndef __CharGame__MainScene__
#define __CharGame__MainScene__

#include "cocos2d.h"
#include "Player.h"
#include "Enemy.h"

class MainScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainScene);
    
private:
    void setChargeSystem();
    // イベント
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
    void charge(float f);
    // 敵のランダム発生
    void update(float delta);
    void encountEnemy();
    // 出現している敵の移動
    void moveEnemy();
    // ジャイロセンサー
    void onGyro(cocos2d::Acceleration* acc, cocos2d::Event* event);
    // 衝突
    bool onContactBegin(cocos2d::PhysicsContact& contact);
    
    cocos2d::SEL_SCHEDULE chargeSEL;
    
    // プレーヤー
    Player *player;
};

#endif /* defined(__CharGame__MainScene__) */
