//
//  TrackScene.h
//  ChildRacer
//
//  Created by Admin on 8/11/15.
//
//

#ifndef __ChildRacer__TrackScene__
#define __ChildRacer__TrackScene__

#include <stdio.h>

#include "cocos2d.h"

USING_NS_CC;

enum PauseButtons
{
    kTagPauseResumeGame = 0,
    kTagPauseGoHome = 1,
    kTagPausePlayAgain = 2
};

class TrackScene : public cocos2d::LayerColor
{
public:
    TrackScene();
    
private:
    void _onOptionPressed(cocos2d::Ref* pSender);
};
#endif

/* defined(__ChildRacer__TrackScene__) */
