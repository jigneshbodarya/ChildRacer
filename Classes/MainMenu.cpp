//
//  MainMenu.cpp
//  ChildRacer
//
//  Created by Admin on 8/23/15.
//
//

#include "MainMenu.h"
#include "HelloWorldScene.h"

USING_NS_CC;

Scene* MainMenu::createScene()
{
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_NONE);
 
    // 'layer' is an autorelease object
    auto layer = MainMenu::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    return scene;

}


// on "init" you need to initialize your instance
bool MainMenu::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Node::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    
    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.
    
    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(MainMenu::onMenuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));
    
    auto backGroundSprite  = Sprite::create("kidbg.png");
    backGroundSprite->setPosition(0, 0);
    backGroundSprite->setScale(visibleSize.width / backGroundSprite->getContentSize().width, visibleSize.height / backGroundSprite->getContentSize().height);
    backGroundSprite->setAnchorPoint(Vec2(0, 0));
    backGroundSprite->setPosition(Vec2(origin.x, origin.y));

    this->addChild(backGroundSprite);
    // create menu, it's an autorelease object
    auto closemenu = Menu::create(closeItem, NULL);
    closemenu->setPosition(Vec2::ZERO);
    this->addChild(closemenu, 1);
    
    // Create a Label to identify the sample
    auto label = LabelTTF::create("ChildRacer", "Marker Felt.ttf", 32);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));
    
    // add the label as a child to this layer
    this->addChild(label, 1);
    
    /////////////////////////////
    // 3. add main menu
    auto mainmenu = Menu::create();
    int index = 2;
    
    // TileMap
    auto itemlabel = LabelTTF::create("Play", "Marker Felt.ttf", 32);
    auto menuItem = MenuItemLabel::create(itemlabel);
    menuItem->setCallback([&](cocos2d::Ref *sender) {
//        Director::getInstance()->replaceScene(HelloWorld::createScene());
        this->goToGameScene(sender);
    });
    menuItem->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2).x,
                          (Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height).y - (++index) * 40));
    
    mainmenu->addChild(menuItem,2);
    
    // Particle
    itemlabel = LabelTTF::create("Particle", "Marker Felt.ttf", 32);
    menuItem = MenuItemLabel::create(itemlabel);
    menuItem->setCallback([&](cocos2d::Ref *sender) {
        Director::getInstance()->replaceScene(HelloWorld::createScene());
    });
    menuItem->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2).x,
                          (Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height).y - (++index) * 40));
    
    mainmenu->addChild(menuItem,2);
    
    // Parallax
    itemlabel = LabelTTF::create("Parallax", "Marker Felt.ttf", 32);
    menuItem = MenuItemLabel::create(itemlabel);
    menuItem->setCallback([&](cocos2d::Ref *sender) {
        
    });
    menuItem->setPosition(Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height/2).x,
                          (Vec2(origin.x+visibleSize.width/2, origin.y+visibleSize.height).y - (++index) * 40));
    
    mainmenu->addChild(menuItem,2);
    
    // add main menu
    mainmenu->setPosition(Vec2::ZERO);
    this->addChild(mainmenu);
    
    return true;
}


void MainMenu::goToGameScene(cocos2d::Ref *pSender)
{
    auto scene = HelloWorld::createScene();
    Director::getInstance()->replaceScene(scene);
}

void MainMenu::onMenuCloseCallback(Ref* sender)
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