#include "GameLayer.h"
#include "SimpleAudioEngine.h"
#include "Player.h"

USING_NS_CC;

Scene* GameLayer::createScene()
{
    return GameLayer::create();
}

// Print useful error message instead of segfaulting when files are not there.
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

// on "init" you need to initialize your instance
bool GameLayer::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    _screenSize = Director::getInstance()->getVisibleSize();

    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(GameLayer::menuCloseCallback, this));

    if (closeItem == nullptr ||
        closeItem->getContentSize().width <= 0 ||
        closeItem->getContentSize().height <= 0)
    {
        problemLoading("'CloseNormal.png' and 'CloseSelected.png'");
    }
    else
    {
        float x = origin.x + _screenSize.width - closeItem->getContentSize().width/2;
        float y = origin.y + closeItem->getContentSize().height/2;
        closeItem->setPosition(Vec2(x,y));
    }

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...
    auto bg = Sprite::create("star_bg.jpg");
    bg->setPosition(Vec2(_screenSize.width/2 + origin.x, _screenSize.height/2 + origin.y));
    this->addChild(bg, kBackground, kSpriteBg);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_sheet.plist");
    _gameBatchNode = SpriteBatchNode::create("sprite_sheet.png", 100);

    this->addChild(_gameBatchNode, kForeground);

    _player = Player::create();
    _player->setScale(_screenSize.height*0.05/_player->getContentSize().height);
    _player->setPosition(Vec2(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    _gameBatchNode->addChild(_player, kForeground, kSpritePlayer);

//    auto voidNode = ParallaxNode::create();

//    voidNode->addChild(bg, -1, Vec2(0.5f,0.5f), Vec2::ZERO);

  //  this->addChild(voidNode, kBackground, kSpriteBg);

    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //create main loop
    this->scheduleUpdate();

    return true;
}

void GameLayer::update (float dt) {

  //  if (_player.getPos().x - _player.)

}

bool GameLayer::onTouchBegan(Touch *touch, Event *event){

  Point tap = touch->getLocation();

  CCLOG("onTouchBegan tap.x=%f,tap.y=%f", tap.x, tap.y);

    return true;
}

void GameLayer::onTouchMoved(Touch *touch, Event *event){
    Point tap = touch->getLocation();

    CCLOG("onTouchMoved tap.x=%f,tap.y=%f", tap.x, tap.y);
    auto node = getChildByTag(kSpriteBg);
    auto currentPos = node->getPosition();

    CCLOG("currentPos.x=%f,currentPos.y=%f:",currentPos.x,currentPos.y);

    currentPos.x -= (tap.x - _screenSize.width / 2) / 100;
    currentPos.y -= (tap.y - _screenSize.height / 2) / 100;

    CCLOG("currentPos.x=%f,currentPos.y=%f:",currentPos.x,currentPos.y);
    node->setPosition(currentPos);

}

void GameLayer::onTouchEnded(Touch *touch, Event *event){

  Point tap = touch->getLocation();

  CCLOG("onTouchEnded tap.x=%f,tap.y=%f", tap.x, tap.y);

  Point cur_pos = _player->getPos();

  Vec2 target = Vec2(cur_pos.x + tap.x - _screenSize.width / 2, cur_pos.y + tap.y - _screenSize.height / 2);

  CCLOG("target .x=%f,.y=%f", target.x, target.y);

  _player->setTarget(target);

}

void GameLayer::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif

    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/

    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);


}
