//
//  MapScene.hpp
//  pudding
//
//  Created by Atsushi Yoshida on 2015/12/11.
//
//

#ifndef MapScene_h
#define MapScene_h

#include "cocos2d.h"

using namespace cocos2d;

class MapScene : public cocos2d::Layer
{
public:
    static Scene* createScene();
    bool init();
    CREATE_FUNC(MapScene);
    Node* _csb;
};

#endif /* MapScene_h */
