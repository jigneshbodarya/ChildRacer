//
//  GameOverScene.h
//  ChildRacer
//
//  Created by Admin on 9/4/15.
//
//

#ifndef __ChildRacer__GameOverScene__
#define __ChildRacer__GameOverScene__

#include <stdio.h>

#include "cocos2d.h"

USING_NS_CC;

enum GameOverButtons
{
    kTagPlayAgain = 0,
    kTagGoHome = 1,
    kTagSendScore = 2
};

class GameOverScene : public cocos2d::LayerColor
{
public:
    GameOverScene();
    
private:
    void _onOptionPressed(cocos2d::Ref* pSender);
    
    const char* _leaderboardID;
    
    int _obstaclesAvoided;
    int _level;
    long _score;
    
    cocos2d::LabelTTF* _lblScore;
    cocos2d::LabelTTF* _lblMaxScore;
    cocos2d::Sprite* spBadge;
    bool disable;
};
#endif /* defined(__ChildRacer__GameOverScene__) */
