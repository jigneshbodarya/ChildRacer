//
//  TrackScene.cpp
//  ChildRacer
//
//  Created by Admin on 8/11/15.
//
//

#include "TrackScene.h"
#include "Constants.h"
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

 TrackScene::TrackScene()
{
    
    if(initWithColor(Color4B(Color4F(0, 0, 0, 100.0f / 255.0f))))
    {
        auto visibleSize = Director::getInstance()->getVisibleSize();
        auto visibleOrigin = Director::getInstance()->getVisibleOrigin();
        auto origin = Vec2(visibleOrigin.x + visibleSize.width * 0.5f, visibleOrigin.y + visibleSize.height* 0.5f);
        
        // BGWhite
        auto bg = Sprite::create("pause_screen.png");
        bg->setPosition(origin);
        addChild(bg);
        
        float w = bg->getContentSize().width;
        float h = bg->getContentSize().height;
        auto o = Vec2(w * 0.5f, h * 0.5f);
        
        // Buttons
        
        
        // Play again button
        auto itemPlayAgain = MenuItemImage::create("pause_replay.png", "pause_replay.png",CC_CALLBACK_1(TrackScene::_onOptionPressed,this));
       

        itemPlayAgain->setTag(kTagPausePlayAgain);
        itemPlayAgain->setPositionX(o.x - itemPlayAgain->getContentSize().width);
        itemPlayAgain->setPositionY(o.y - itemPlayAgain->getContentSize().height * 0.9f);
        
        auto* itemResume = MenuItemImage::create("pause_play_off.png", "pause_play_off.png", CC_CALLBACK_1(TrackScene::_onOptionPressed,this));
        itemResume->setTag(kTagPauseResumeGame);
        itemResume->setPositionX(itemPlayAgain->getPositionX() + itemResume->getContentSize().width * 1.1f);
        itemResume->setPositionY(itemPlayAgain->getPositionY());
        
        // Home button
        auto itemHome = MenuItemImage::create("pause_home.png", "pause_home.png", CC_CALLBACK_1(TrackScene::_onOptionPressed,this));
        itemHome->setTag(kTagPauseGoHome);
        itemHome->setPositionX(itemResume->getPositionX() + itemResume->getContentSize().width * 1.1f);
        itemHome->setPositionY(itemResume->getPositionY());
        
        itemPlayAgain->setPositionY(itemPlayAgain->getPositionY() - itemPlayAgain->getContentSize().height * 0.3f);
        itemResume->setPositionY(itemResume->getPositionY() - itemResume->getContentSize().height * 0.15f);
        
        
        // Menu
        auto menu = Menu::create();
        menu->setAnchorPoint(Vec2(0, 0));
        menu->setPosition(Point::ZERO);
        
        menu->addChild(itemResume);
        menu->addChild(itemHome);
        menu->addChild(itemPlayAgain);
        
        bg->addChild(menu);
    }
    
}

void TrackScene::_onOptionPressed(Ref *pSender)
{
    auto item = (MenuItem*) pSender;
  //  SimpleAudioEngine::sharedEngine()->playEffect(SFX_BUTTON);
    
    switch (item->getTag()) {
        case kTagPauseResumeGame:
          //  CCNotificationCenter::sharedNotificationCenter()->postNotification(NOTIFICATION_RESUME_GAME);
            Director::getInstance()->resume();

        NotificationCenter::getInstance()->postNotification(NOTIFICATION_RESUME_GAME);
            
            break;
            
        case kTagPausePlayAgain:
            NotificationCenter::getInstance()->postNotification(NOTIFICATION_PLAY_AGAIN);
            break;
            
        case kTagPauseGoHome:
            NotificationCenter::getInstance()->postNotification(NOTIFICATION_GO_HOME);
            break;
            
    }
    
    
}

