//
//  MainMenu.h
//  ChildRacer
//
//  Created by Admin on 8/23/15.
//
//

#ifndef __ChildRacer__MainMenu__
#define __ChildRacer__MainMenu__

#include "cocos2d.h"

USING_NS_CC;

class MainMenu : public cocos2d::Node
{

    // there's no 'id' in cpp, so we recommend returning the class instance pointer
public:
    static cocos2d::Scene* createScene();
    
    virtual bool init();
    
    // a selector callback
    void onMenuCloseCallback(cocos2d::Ref* sender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(MainMenu);
    void goToGameScene(Ref *pSender);
    
};



#endif /* defined(__ChildRacer__MainMenu__) */
