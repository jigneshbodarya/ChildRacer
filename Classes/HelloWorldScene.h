#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "TrackScene.h"
#include "GameOverScene.h"
USING_NS_CC;
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
   
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    void initBackground();
    void setBackground();
    void update(float) override;

    void goToPauseScene(Ref *pSender);
    void goToGameOverScene(Ref *pSender);
    void goToGameResumeScene(Ref *pSender);
    void goToGameNewScene(Ref *pSender);
    void goToRetryScene(Ref *pSender);
    void showParticles();
    void displayLevelInfo();
    void setPhyWorld(PhysicsWorld* world){m_world = world;}
    
    virtual bool onTouchBegan(Touch *touch, Event *unused_event);
    virtual void onTouchEnded(Touch *touch, Event *unused_event);
    void onAcceleration(Acceleration* acc, Event* event);
    void addNewSpriteAtPosition(Point p);
    void delayCall();
    void addObserver();
    void removeObserver();
    
private:
    PhysicsWorld* m_world;
    float score;
    float highscore;
    float level;
    float jump;
    bool onContactBegin(const PhysicsContact& contact);
    cocos2d::LabelTTF* lblScore;
    cocos2d::Sprite* sprite;
    cocos2d::Sprite* hero;
    cocos2d::Sprite* reward;
    cocos2d::Label* lblHighScore;
    float _scale, _screenW, _screenH;
    
    
    TrackScene* _pauseLayer;
    GameOverScene* _gameOverScene;
    Size visibleSize;
    Vec2 origin;
    Vec2 heroPosition;
    //cocos2d::JumpTo* jump;

    Sprite *background1;
    Sprite *background2;
    Sprite *background3;
    Sprite *background4;
};

#endif


