//
//  GameOverScene.cpp
//  ChildRacer
//
//  Created by Admin on 9/4/15.
//
//

#include "GameOverScene.h"
#include "Constants.h"
#include "cocos2d.h"
USING_NS_CC;

GameOverScene::GameOverScene()
{
    if(initWithColor(Color4B(Color4F(0, 0, 0, 100.0f / 255.0f))))
    {
        _leaderboardID = "";
        
        _score = 0;
        disable = false;
        
        auto visibleSize = CCDirector::getInstance()->getVisibleSize();
        auto visibleOrigin = CCDirector::getInstance()->getVisibleOrigin();
        auto origin = Vec2(visibleOrigin.x + visibleSize.width * 0.5f, visibleOrigin.y + visibleSize.height* 0.5f);
        
        // BGWhite
        auto bg = CCSprite::create("gameover_screen.png");
        bg->setPosition(origin);
        addChild(bg);
        
        float w = bg->getContentSize().width;
        float h = bg->getContentSize().height;
        auto o = Vec2(w * 0.5f, h * 0.5f);
        
        // Badge and record
        spBadge = Sprite::create("bicho_0004.png");
        spBadge->setPosition(Vec2(o.x, o.y + spBadge->getContentSize().height * 0.5f));
        bg->addChild(spBadge, 10);
        
        _lblScore = LabelTTF::create("", FONT_GAME, SIZE_RATE_END, Size(w * 0.5f, h * 0.15f), TextHAlignment::LEFT, TextVAlignment::CENTER);
        _lblScore->setPosition(Vec2(o.x + spBadge->getContentSize().width * 0.8f, o.y - spBadge->getContentSize().height * 0.1f));
        _lblScore->setColor(Color3B::WHITE);
        _lblScore->setRotation(-3);
        bg->addChild(_lblScore);
        
        _lblMaxScore = LabelTTF::create("", FONT_GAME, _lblScore->getFontSize(), Size(w * 0.5f, h * 0.15f), TextHAlignment::LEFT, TextVAlignment::CENTER);
        _lblMaxScore->setPosition(Vec2(_lblScore->getPositionX(), _lblScore->getPositionY() - spBadge->getContentSize().height * 0.28f));
        _lblMaxScore->setColor(Color3B::WHITE);
        _lblMaxScore->setRotation(_lblScore->getRotation());
        bg->addChild(_lblMaxScore);
        
        // Send score button
        auto itemScore = MenuItemImage::create("fb-icon.png", "fb-icon.png",CC_CALLBACK_1(GameOverScene::_onOptionPressed,this));
        itemScore->setTag(kTagSendScore);
        itemScore->setPositionX(o.x - itemScore->getContentSize().width * 1.5f);
        itemScore->setPositionY(o.y - itemScore->getContentSize().height * 1.7f);
        
        // Home button
        
        auto itemHome = MenuItemImage::create("pause_home.png", "pause_home.png", CC_CALLBACK_1(GameOverScene::_onOptionPressed,this));
        
        itemHome->setTag(kTagGoHome);
        itemHome->setPositionX(itemScore->getPositionX() + itemScore->getContentSize().width * 1.5f);
        itemHome->setPositionY(itemScore->getPositionY());
        
        // Play again button
        auto itemPlayAgain = CCMenuItemImage::create("pause_replay.png", "pause_replay.png", CC_CALLBACK_1(GameOverScene::_onOptionPressed,this));
        
        itemPlayAgain->setTag(kTagPlayAgain);
        itemPlayAgain->setPositionX(itemHome->getPositionX() + itemScore->getContentSize().width * 1.5f);
        itemPlayAgain->setPositionY(itemScore->getPositionY());
        
        itemPlayAgain->setPositionY(itemPlayAgain->getPositionY() + itemScore->getContentSize().height * 0.2f);
        itemHome->setPositionY(itemHome->getPositionY() + itemScore->getContentSize().height * 0.1f);
        
        // Menu
        auto menu = Menu::create();
        menu->setAnchorPoint(Vec2(0, 0));
        menu->setPosition(Point::ZERO);
        
        menu->addChild(itemScore);
        menu->addChild(itemHome);
        menu->addChild(itemPlayAgain);
        
        bg->addChild(menu);
    
    }
}


void GameOverScene::_onOptionPressed(Ref *pSender)
{
    if(disable)
        return;
    
    auto item = (MenuItem*) pSender;
//    SimpleAudioEngine::sharedEngine()->playEffect(SFX_BUTTON);
    
    switch (item->getTag()) {
        case kTagPlayAgain:
            
            NotificationCenter::getInstance()->postNotification(NOTIFICATION_PLAY_AGAIN);
            break;
            
        case kTagSendScore:
            
            
            break;
            
        case kTagGoHome:
            
            
            
//            CCScene* scene = HomeScene::scene(kGameModeHome);
//            CCDirector::sharedDirector()->replaceScene(CCTransitionFade::create(0.5f, scene));
            
            break;
            
    }
    
    
}
