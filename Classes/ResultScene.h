//
//  ResultScene.hpp
//  pudding
//
//  Created by Atsushi Yoshida on 2015/12/13.
//
//

#ifndef ResultScene_h
#define ResultScene_h

#include "cocos2d.h"

using namespace cocos2d;

class ResultScene : public cocos2d::Layer
{
public:
    static Scene* createScene();
    bool init();
    void onEnter();
    CREATE_FUNC(ResultScene);
    Node* _csb;
};


#endif /* ResultScene_h */
