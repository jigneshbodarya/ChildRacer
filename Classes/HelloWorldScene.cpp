#include "HelloWorldScene.h"
#include "TrackScene.h"
#include "Constants.h"
#include "MainMenu.h"
#include "SimpleAudioEngine.h"
#define SCROLLING_BACKGROUND_SPEED 0.01

// Notifications

USING_NS_CC;

static Size s_visibleSize;
static Vec2 s_origin;
static Vec2 s_centre;
//static Scene* s_currScene;
//static const int DRAG_BODYS_TAG = 0x80;

enum GameDeep
{
    kDeepSky = -9999,
    kDeepCloud = -9900,
    kDeepBGBack = -9500,
    kDeepBGMid = -9250,
    kDeepBGFront = -9000,
    kDeepTracks = -8500,
    kDeepGameElements = -2500,
    kDeepGameFinish = 500,
    kDeepScore = 1000,
    kDeepPauseLayer = 2500,
    kDeepPopUpLoseLayer = 3500,
    kDeepTutorial = 2200
};


Scene* HelloWorld::createScene()
{

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // some upfront items that we need
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    s_visibleSize = Director::getInstance()->getVisibleSize();
    s_origin = Director::getInstance()->getVisibleOrigin();
    s_centre = s_origin + s_visibleSize / 2;
    
    
    
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // create a scene with physics world for our game to hold everything
    // 'scene' is an autorelease object
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    auto scene = Scene::createWithPhysics();
    
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
    
    auto visibleSize = Director::getInstance()->getVisibleSize();
    //auto body = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3);
    
    // 'layer' is an autorelease object
   
    auto edgeBody = PhysicsBody::createEdgeBox(visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 1);
    auto edgeNode = Node::create();
    edgeNode->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    edgeNode->setPhysicsBody(edgeBody);
    //this->addChild(edgeNode);
    
    auto layer = HelloWorld::create();
    
    layer->addChild(edgeNode);
    //layer->setPhyWorld(scene->getPhysicsWorld());
    
    // add layer as a child to scene
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    _screenW = Director::getInstance()->getWinSize().width;
    _screenH = Director::getInstance()->getWinSize().height;
    
    //=================================================================
    visibleSize = Director::getInstance()->getVisibleSize();
    origin = Director::getInstance()->getVisibleOrigin();
    
    background1 = Sprite::create("foreground_02.png");
    background1->setAnchorPoint(Vec2(0, 0));
    background1->setPosition(Vec2(origin.x, origin.y));
    
    background3 = Sprite::create("background_01.png");
    background3->setAnchorPoint(Vec2(0, 0));
    background3->setPosition(Vec2(origin.x, origin.y));

    
    background2 = Sprite::create("foreground_02.png");
    background2->setAnchorPoint(Vec2(0, 0));
    background2->setPosition(Vec2(origin.x + visibleSize.width, origin.y  ));
//
    background4 = Sprite::create("background_01.png");
    background4->setAnchorPoint(Vec2(0, 0));
    background4->setPosition(Vec2(origin.x + visibleSize.width, origin.y  ));
    
    
    background1->setScale(visibleSize.width / background1->getContentSize().width, visibleSize.height / background1->getContentSize().height);
    
    background2->setScale(visibleSize.width / background2->getContentSize().width, visibleSize.height / background2->getContentSize().height);

    background3->setScale(visibleSize.width / background3->getContentSize().width, visibleSize.height / background3->getContentSize().height);

    background4->setScale(visibleSize.width / background4->getContentSize().width, visibleSize.height / background4->getContentSize().height);

    
     background1->setAnchorPoint(Vec2(0, 0));
    // add the sprite as a child to this layer
    this->addChild(background3, 0);
    this->addChild(background4, 0);

    this->addChild(background1, 0);
    this->addChild(background2, 0);
    //=================================================================
    
    _pauseLayer = new TrackScene();
    _pauseLayer->setVisible(false);
    _pauseLayer->setPosition(Vec2(0, -Director::getInstance()->getWinSize().height));
    _pauseLayer->setPositionY(0);
    _pauseLayer->autorelease();
    addChild(_pauseLayer, kDeepPauseLayer);
   
    _gameOverScene = new GameOverScene();
    _gameOverScene->setVisible(false);
    _gameOverScene->setPosition(Vec2(0, -Director::getInstance()->getWinSize().height));
    _gameOverScene->setPositionY(0);
    _gameOverScene->autorelease();
    addChild(_gameOverScene, kDeepPopUpLoseLayer);

    
    addObserver();
    //PEShapeCache::getInstance()->addBodysWithFile("physics/body.plist");
    
    auto coinSymbol = Sprite::create("coin.png");
    coinSymbol->setPosition(Director::getInstance()->getWinSize().width-160, origin.y+ visibleSize.height-coinSymbol->getContentSize().height/5);
    coinSymbol->setScale(0.20);
    this->addChild(coinSymbol);
    
    auto highScoreIcon = Sprite::create("highscore.png");
    highScoreIcon->setPosition(Vec2(origin.x+highScoreIcon->getContentSize().width/3,origin.y+ visibleSize.height-highScoreIcon->getContentSize().height/3));
    highScoreIcon->setScale(0.35);
//    highScoreIcon->setAnchorPoint(Vec2(0, 0));
    this->addChild(highScoreIcon);
    
    
    highscore = UserDefault::getInstance()->getIntegerForKey(USER_DEFAULT_HIGH_SCORE);
    char text[255];
    sprintf(text,"%5.0f", highscore);
    
    lblHighScore = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 22);
    lblHighScore->setPosition(Vec2(origin.x+highScoreIcon->getContentSize().width/3*2+5,origin.y+ visibleSize.height-highScoreIcon->getContentSize().height/3));
    //lblHighScore->setAnchorPoint(Vec2(0.5, 0.5));
    this->addChild(lblHighScore);
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto spritecache = SpriteFrameCache::getInstance();
    spritecache->addSpriteFramesWithFile("spritesheet.plist");
    
    reward = Sprite::create();
    reward->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2+10));
    reward->setAnchorPoint(Vec2(0.5,0.5));
    reward->setTag(1011);
    this->addChild(reward);
    Vector<SpriteFrame*> animFrames;
    char str[100];
    for(int i = 1; i <= 8; i++)
    {
        sprintf(str, "character/%02d.png", i);
        animFrames.pushBack(spritecache->getSpriteFrameByName(str));
    }
    
    
    //set score
    score = 0;
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
   

    level = UserDefault::getInstance()->getIntegerForKey(USER_DEFAULT_LEVEL);
    
    if(level>26)
    {
        auto label = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 22);
        label->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
        this->addChild(label);
        return true;
        
    }

    if(level == 0)
    {
        level++;
        UserDefault::getInstance()->setIntegerForKey(USER_DEFAULT_LEVEL,1);
    }
    auto menuItem = MenuItemImage::create("pauseBtn.png", "pauseBtn.png", CC_CALLBACK_1(HelloWorld::goToPauseScene,this));
    lblScore = LabelTTF::create("00000", "Marker Felt.ttf", 22);
    lblScore->setPosition(origin.x+visibleSize.width-100, origin.y+ visibleSize.height-coinSymbol->getContentSize().height/5);
    this->addChild(lblScore);
    menuItem->setPosition(Vec2(origin.x+visibleSize.width - menuItem->getContentSize().width/2, origin.y + visibleSize.height - menuItem->getContentSize().height/2));
    menuItem->setAnchorPoint(Vec2(0, 0));
    menuItem->setScale(0.35);
    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem,menuItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    

    
    hero = Sprite::createWithSpriteFrame(animFrames.front());
    Animation *animation = Animation::createWithSpriteFrames(animFrames, 1.0f/16);
    auto action = RepeatForever::create(Animate::create(animation));
    hero->runAction(action);
    hero->setPosition(30, Director::getInstance()->getWinSize().height/2);
    action->setTag(123);
    auto heroBody = PhysicsBody::createBox(Size(45.0f,115.0f),PhysicsMaterial(0.1f,1.0f,0.0f));
    heroBody->setDynamic(false);
    heroBody->setContactTestBitmask(0x1);
    hero->setScale(0.5);
    hero->setPhysicsBody(heroBody);

    
    
    addChild(hero);
    

    
    auto actionMove = MoveTo::create(2,Point(Director::getInstance()->getWinSize().width/2,Director::getInstance()->getWinSize().height/2));
    hero->runAction(actionMove);
    sprite = Sprite::create("obstacle.png");
    sprite->setPosition(this->getBoundingBox().getMaxX()+ 50,visibleSize.height/2);
     sprite->setAnchorPoint(Vec2(1 ,1));
    this->addChild(sprite, 0);
    sprite->setTag(5);

    auto physicsBodywhite = PhysicsBody::createBox(Size(50,49),PhysicsMaterial(0.0f,0.0f,0.0f));
    physicsBodywhite->setContactTestBitmask(0x2);
    physicsBodywhite->setGravityEnable(false);
      //  physicsBodywhite->setCategoryBitmask(0x1);
    physicsBodywhite->setCollisionBitmask(0x1);
//    physicsBodywhite->setContactTestBitmask(true);
    sprite->setPhysicsBody(physicsBodywhite);
   
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(HelloWorld::onContactBegin,this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    displayLevelInfo();


    auto actions = Sequence::create(
                                   DelayTime::create(1),
                                   CallFunc::create(
                                                    [&]() {
                                                        this->delayCall();
                                                    }
                                                    ), 
                                   NULL
                                   );
    
    this->runAction(actions);
    Device::setAccelerometerEnabled(true);
    auto acclistener = EventListenerAcceleration::create(CC_CALLBACK_2(HelloWorld::onAcceleration, this));
    _eventDispatcher->addEventListenerWithSceneGraphPriority(acclistener, this);
    heroPosition = hero->getPosition();
    return true;
}

//==================================================
// Function Name:
// Function Parameter:
// Function ReturnType:
// Function Purpose:
//==================================================
void HelloWorld::addObserver()
{
    
    NotificationCenter::getInstance()->addObserver(this,
                                                                callfuncO_selector(HelloWorld::goToPauseScene), NOTIFICATION_PAUSE_GAME, NULL);
    NotificationCenter::getInstance()->addObserver(this,
                                                                callfuncO_selector(HelloWorld::goToGameResumeScene), NOTIFICATION_RESUME_GAME, NULL);
    NotificationCenter::getInstance()->addObserver(this,
                                                                callfuncO_selector(HelloWorld::goToRetryScene), NOTIFICATION_PLAY_AGAIN, NULL);

    NotificationCenter::getInstance()->addObserver(this,
                                                                callfuncO_selector(HelloWorld::goToGameNewScene), NOTIFICATION_GO_HOME, NULL);
    NotificationCenter::getInstance()->addObserver(this,
                                                   callfuncO_selector(HelloWorld::goToGameOverScene), NOTIFICSTION_GAME_OVER, NULL);
    

}

void HelloWorld::removeObserver()
{
    NotificationCenter::getInstance()->removeObserver(this, NOTIFICATION_PAUSE_GAME);
    NotificationCenter::getInstance()->removeObserver(this, NOTIFICATION_RESUME_GAME);
    NotificationCenter::getInstance()->removeObserver(this, NOTIFICATION_PLAY_AGAIN);
    NotificationCenter::getInstance()->removeObserver(this, NOTIFICATION_GO_HOME);
    NotificationCenter::getInstance()->removeObserver(this, NOTIFICSTION_GAME_OVER);
}

// Implementation of the accelerometer callback function prototype
void HelloWorld::onAcceleration(Acceleration* acc, Event* event)
{
    log("X: %f", acc->x);
    log("Y: %f", acc->y);
    log("Z: %f", acc->z);
}
bool HelloWorld::onContactBegin(const PhysicsContact& contact)
{
//    auto sp = (Sprite*)contact.getShapeA()->getBody()->getNode();
//    auto action = RotateBy::create(0.5, 90);
//    sp->runAction(action);
//    int tag = sp->getTag();
//    this->removeChild(sp, true);
//    CCLOG("onContactBegin: %d", tag);
    this->pause();
    hero->stopAllActions();
    auto actions1 = Sequence::create(
                                                           DelayTime::create(1),
                                                           CallFunc::create(
                                                                            [&]() {
                                                                                
                                                                                NotificationCenter::getInstance()->postNotification(NOTIFICSTION_GAME_OVER);

                                                                            }
                                                                            ),
                                                           NULL
                                                           );
    
    this->runAction(actions1);
    cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
   // actions.pushBack(cocos2d::ScaleBy::create(1.5, 1.5));
    actions.pushBack(cocos2d::TintTo::create(1.5, 255, 0, 0));
    actions.pushBack(cocos2d::FadeTo::create(1.5, 30));
    
    auto spawn = cocos2d::Spawn::create(actions);
    hero->runAction(spawn);
    
    return true;
}
//==================================================
// Function Name:
// Function Parameter:
// Function ReturnType:
// Function Purpose:
//==================================================
void HelloWorld::goToPauseScene(cocos2d::Ref *pSender)
{
    Director::getInstance()->pause();
    _pauseLayer->setVisible(true);
    
}


//==================================================
// Function Name: showParticles
// Function Parameter:
// Function ReturnType:
// Function Purpose:
//==================================================
void HelloWorld::showParticles()
{
    // Particles
    auto emitter = ParticleFireworks::create();
    emitter->setAngleVar(180);
    emitter->setLife(4);
//    emitter->setBlendAdditive(true);
 //   reward->setPosition(visibleSize.width/2, visibleSize.height/2);
   // reward->s
   
    
    this->addChild(emitter, 2,124);

    auto actions1 = Sequence::create(
                                     DelayTime::create(4),
                                     CallFunc::create(
                                                      [&]() {
                                                          
                                                          this->resume();
                                                          hero->resume();
                                                          this->removeChildByTag(124);
                                                          level = UserDefault::getInstance()->getIntegerForKey(USER_DEFAULT_LEVEL);
                                                          level++;
                                                          reward->setVisible(false);
                                                          UserDefault::getInstance()->setIntegerForKey(USER_DEFAULT_LEVEL, level);
                                                        NotificationCenter::getInstance()->postNotification(NOTIFICATION_RESUME_GAME);
                                                      }
                                                      ),
                                     NULL
                                     );
    this->runAction(actions1);
}
//==================================================
// Function Name:
// Function Parameter:
// Function ReturnType:
// Function Purpose:
//==================================================
void HelloWorld::goToGameOverScene(cocos2d::Ref *pSender)
{
    Director::getInstance()->pause();
    _gameOverScene->setVisible(true);

}

//==================================================
// Function Name:
// Function Parameter:
// Function ReturnType:
// Function Purpose:
//==================================================
void HelloWorld::goToGameResumeScene(cocos2d::Ref *pSender)
{
    Director::getInstance()->resume();
    _pauseLayer->setVisible(false);
    _gameOverScene->setVisible(false);
}
//==================================================
// Function Name:
// Function Parameter:
// Function ReturnType:
// Function Purpose:
//==================================================
void HelloWorld::goToGameNewScene(cocos2d::Ref *pSender)
{
    auto scene = MainMenu::createScene();
    removeObserver();
    Director::getInstance()->resume();
    Director::getInstance()->replaceScene(scene);


}
//==================================================
// Function Name:
// Function Parameter:
// Function ReturnType:
// Function Purpose:
//==================================================
void HelloWorld::goToRetryScene(cocos2d::Ref *pSender)
{
    auto scene = HelloWorld::createScene();
    removeObserver();
    Director::getInstance()->resume();
    Director::getInstance()->replaceScene(scene);

}
//==================================================
// Function Name: onTouchBegan
// Function Parameter:
// Function ReturnType:
// Function Purpose:
//==================================================
bool HelloWorld::onTouchBegan(Touch *touch, Event *unused_event)
{
   // CCLOG("x=%f,y=%f",heroPosition.x,    heroPosition.y);
    
   // CCLOG("real x=%f,real y=%f",hero->g,    heroPosition.y);
    if(hero->getPosition().y == heroPosition.y)
    {
    auto jump = JumpTo::create(1, Vec2(hero->getPositionX(), heroPosition.y), 100, 1);
    hero->runAction(jump);
    }
    return true;
    
}

void HelloWorld::onTouchEnded(Touch *touch, Event *unused_event)
{
    auto location = touch->getLocation();
    //addNewSpriteAtPosition(location);
}


void HelloWorld::update(float delta){
   // CCLOG("%f",delta);
    
    background1->setPositionX(background1->getPositionX() - (SCROLLING_BACKGROUND_SPEED*visibleSize.width));
    background2->setPositionX(background2->getPositionX() - (SCROLLING_BACKGROUND_SPEED*visibleSize.width));
    
    background3->setPositionX(background3->getPositionX() - (SCROLLING_BACKGROUND_SPEED*visibleSize.width));
    background4->setPositionX(background4->getPositionX() - (SCROLLING_BACKGROUND_SPEED*visibleSize.width));
    
    if (background1->getPositionX() <= -visibleSize.width)
    {
        background1->setPositionX(background2->getPositionX() + visibleSize.width);
        CCLOG("background 1 set");
    }

    if (background2->getPositionX() <= -visibleSize.width)
    {
        background2->setPositionX(background1->getPositionX() + visibleSize.width);
        CCLOG("background 2 set");
    }
    
    if (background3->getPositionX() <= -visibleSize.width)
    {
        background3->setPositionX(background4->getPositionX() + visibleSize.width);
                CCLOG("background 3 set");
    }
    
    if (background4->getPositionX() <= -visibleSize.width)
    {
        background4->setPositionX(background3->getPositionX() + visibleSize.width);
                CCLOG("background 4 set");
    }
    auto movePoint = visibleSize.width/2.272;
    auto position = sprite->getPosition();
    position.x -= movePoint * delta;

    if(position.x < this->getBoundingBox().getMidX() && position.x > this->getBoundingBox().getMidX() - 250* delta)
    {
        score += 5;
        char text[255];
        sprintf(text,"%05.0f", score);
        lblScore->setString(text);
        jump++;
        CCLOG("%f",level);
        if(jump == 10*level)
        {
            reward->setVisible(true);
            //convert into character
            char c[10];
            int lvl = int(level);
            sprintf(c,"alphabets/%c.png",lvl+96);
            reward->setTexture(c);
            this->pause();
            hero->pause();
            this->showParticles();
        }
        if(level>26)
        {
             auto label = Label::createWithTTF("Game Over", "fonts/Marker Felt.ttf", 22);
            label->setPosition(Vec2(visibleSize.width/2,visibleSize.height/2));
            this->addChild(label);
            this->pause();
            hero->pause();

            
        }
        if(score > highscore)
        {
            highscore = score;
            UserDefault::getInstance()->setIntegerForKey(USER_DEFAULT_HIGH_SCORE, highscore);
            char text[255];
            sprintf(text,"%5.0f", highscore);
            lblHighScore->setString(text);
        }

    }
    if (position.x  < 0 - (sprite->getBoundingBox().size.width / 2))
    {
        position.x = this->getBoundingBox().getMaxX() + rand() % int(sprite->getBoundingBox().size.width * 1.5);
        
    }
        sprite->setPosition(position);
}

void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void HelloWorld::displayLevelInfo()
{
    char text[10];
    sprintf(text,"level %.0f", level);
    auto label = Label::createWithTTF(text, "fonts/Marker Felt.ttf", 22);
    
    cocos2d::Vector<cocos2d::FiniteTimeAction*> actions;
    // actions.pushBack(cocos2d::ScaleBy::create(1.5, 1.5));
    actions.pushBack(cocos2d::TintTo::create(1.5, 255, 220, 178));
    actions.pushBack(cocos2d::ScaleBy::create(1.01, 5));
    label->setPosition(Vec2(visibleSize.width/2, visibleSize.height/2-10));
    label->setTag(155);
    this->addChild(label, 2, 155);
    auto spawn = cocos2d::Spawn::create(actions);
    label->runAction(spawn);
    auto actions1 = Sequence::create(
                                     DelayTime::create(1),
                                     CallFunc::create(
                                                      [&]() {
                                                          
                                                          //label->removeFromParent();
                                                          this->removeChildByTag(155);
                                                      }
                                                      ),
                                     NULL
                                     );

    this->runAction(actions1);
    
    

}

void HelloWorld::addNewSpriteAtPosition(Point p)
{
    auto sprite = Sprite::create("i3.png");
    sprite->setTag(1);
    auto body = PhysicsBody::createCircle(sprite->getContentSize().width / 2);
    sprite->setPhysicsBody(body);
    sprite->setPosition(p);
    this->addChild(sprite);
}

void HelloWorld::delayCall()
{
    this->scheduleUpdate();
   
}
