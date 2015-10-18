#include "MainScene.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "CocosGUI.h"
#include "Bubble.h"
#include <array>
USING_NS_CC;
using namespace cocostudio;
using namespace cocos2d::ui;

const static int NEXT_STONE_NUM = 5;

const int WIDTH_NUM = 5;
const int HEIGHT_NUM = 5;

std::array<std::shared_ptr<Bubble>, WIDTH_NUM * HEIGHT_NUM> BUBBLES;

Scene* MainScene::createScene()
{
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init()
{
    if ( !Layer::init() )
    {
        return false;
    }
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Image/sweets.plist");
    auto csb = CSLoader::createNode("Scene/MainScene.csb");
    this->addChild(csb);
    
    auto nextArea = csb->getChildByName("NextArea");
    for(int i = 0; i < NEXT_STONE_NUM; i++){
        auto image = ImageView::create("sweets/item_cake.png", ImageView::TextureResType::PLIST);
        image->setScale(0.5f);
        nextArea->addChild(image);
    }
    
    auto board = csb->getChildByName("Board");
    for(int y = 0; y < HEIGHT_NUM; y++){
        for(int x = 0; x < WIDTH_NUM; x++){
            auto bubble = Bubble::create(board, x, y);
        }
        
    }
    
    return true;
}
