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
	if (!Scene::init())
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
		float x = origin.x + _screenSize.width - closeItem->getContentSize().width / 2;
		float y = origin.y + closeItem->getContentSize().height / 2;
		closeItem->setPosition(Vec2(x, y));
	}

	// create menu, it's an autorelease object
	auto menu = Menu::create(closeItem, NULL);
	menu->setPosition(Vec2::ZERO);
	this->addChild(menu, 1);

	auto bg = Sprite::create("star_bg.jpg");
	bg->setPosition(Vec2(_screenSize.width / 2 + origin.x, _screenSize.height / 2 + origin.y));
	this->addChild(bg, kBackground, kSpriteBg);

	_bg.pushBack(bg);

    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("sprite_sheet.plist");
    _gameBatchNode = SpriteBatchNode::create("sprite_sheet.png", 100);

    this->addChild(_gameBatchNode, kForeground);

    _player = Player::create();
    _player->setScale(_screenSize.height*0.05/_player->getContentSize().height);
    _player->setPosition(Vec2(_screenSize.width * 0.5f, _screenSize.height * 0.5f));
    _gameBatchNode->addChild(_player, kForeground, kSpritePlayer);


    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(GameLayer::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

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


}


bool GameLayer::Check_bg_exists(Vec2 in_pt) {
	bool exist = false;
	for (auto bg : _bg) {
		if (in_pt == bg->getPosition()) {
			exist = true;
			CCLOG("exists");
		}
	}
	return exist;
}

void GameLayer::onTouchEnded(Touch *touch, Event *event){

  Point tap = touch->getLocation();

  CCLOG("onTouchEnded tap.x=%f,tap.y=%f", tap.x, tap.y);

  Point cur_pos = _player->getPos();

  Vec2 target = Vec2(cur_pos.x + tap.x - _screenSize.width / 2, cur_pos.y + tap.y - _screenSize.height / 2);

  CCLOG("target .x=%f,.y=%f", target.x, target.y);

  _player->setTarget(target);

  float x_add = - (tap.x - _screenSize.width / 2) / 10;
  float y_add = - (tap.y - _screenSize.height / 2) / 10;

  int all_in = 0;
  int top_left_point_covered = 0;
  int top_right_point_covered = 0;
  int bottom_left_point_covered = 0;
  int bottom_right_point_covered = 0;

  float current_bg_x = 0;
  float current_bg_y = 0;

  float all_in_bg_pos_x = 0;
  float all_in_bg_pos_y = 0;

  std::vector<Vec2> pt_to_erase;

  for (auto bg : _bg) {
	  all_in = 0;
	  if (fabs(bg->getPositionX() + x_add) <= bg->getBoundingBox().size.width / 2 &&
		  fabs(bg->getPositionY() + y_add - _screenSize.height) <= bg->getBoundingBox().size.height / 2) {
		  top_left_point_covered = 1;
		  all_in++;
	  }

	  if (fabs(bg->getPositionX() + x_add - _screenSize.width) <= bg->getBoundingBox().size.width / 2 &&
		  fabs(bg->getPositionY() + y_add - _screenSize.height) <= bg->getBoundingBox().size.height / 2) {
		  top_right_point_covered = 1;
		  all_in++;
	  }

	  if (fabs(bg->getPositionX() + x_add) <= bg->getBoundingBox().size.width / 2 &&
		  fabs(bg->getPositionY() + y_add) <= bg->getBoundingBox().size.height / 2) {
		  bottom_left_point_covered = 1;
		  all_in++;
	  }

	  if (fabs(bg->getPositionX() + x_add - _screenSize.width) <= bg->getBoundingBox().size.width / 2 &&
		  fabs(bg->getPositionY() + y_add) <= bg->getBoundingBox().size.height / 2) {
		  bottom_right_point_covered = 1;
		  all_in++;
	  }

	  if (fabs(bg->getPositionX() - _screenSize.width / 2 ) <= bg->getBoundingBox().size.width / 2 &&
		  fabs(bg->getPositionY() - _screenSize.height / 2) <= bg->getBoundingBox().size.height / 2) {
		  current_bg_x = bg->getPositionX();
		  current_bg_y = bg->getPositionY();
	  }
	  CCLOG("all_in=%d", all_in);

//	  if (all_in == 4) {
//		all_in_bg_pos_x = bg->getPositionX();
//		all_in_bg_pos_y = bg->getPositionY();
//	  }
	  if (all_in == 0) {
		  pt_to_erase.push_back(bg->getPosition());
	  }
  }
  
	for (int i = 0; i < _bg.size(); i++) {
		for (auto v : pt_to_erase) {
			if (v == _bg.at(i)->getPosition()) {
				_bg.erase(i);
				break;
			}
		}
	}

  // if all in, remove other bgs
  //if (all_in_bg_pos_x != 0 && all_in_bg_pos_y != 0)
  //{
	 // for (int i = 0; i < _bg.size(); i++) {
		//  if (!(all_in_bg_pos_x == _bg.at(i)->getPositionX() && all_in_bg_pos_y == _bg.at(i)->getPositionY())) {
		//	  _bg.erase(i);
		//  }
	 // }
  //}

  float _to_add_x;
  float _to_add_y;

  if (top_left_point_covered == 0) {
	  _to_add_x = current_bg_x;
	  _to_add_y = current_bg_y + _bg.at(0)->getBoundingBox().size.height;

	  if (Check_bg_exists(Vec2(_to_add_x, _to_add_y)) == false) {
		  auto bg = Sprite::create("star_bg.jpg");
		  bg->setPosition(Vec2(_to_add_x, _to_add_y));
		  this->addChild(bg, kBackground, kSpriteBg);
		  _bg.pushBack(bg);
	  }

	  _to_add_x = current_bg_x - _bg.at(0)->getBoundingBox().size.width;
	  _to_add_y = current_bg_y;

	  if (Check_bg_exists(Vec2(_to_add_x, _to_add_y)) == false) {
		  auto bg = Sprite::create("star_bg.jpg");
		  bg->setPosition(Vec2(_to_add_x, _to_add_y));
		  this->addChild(bg, kBackground, kSpriteBg);
		  _bg.pushBack(bg);
	  }

	  _to_add_x = current_bg_x - _bg.at(0)->getBoundingBox().size.width;
	  _to_add_y = current_bg_y + _bg.at(0)->getBoundingBox().size.height;

	  if (Check_bg_exists(Vec2(_to_add_x, _to_add_y)) == false) {
		  auto bg = Sprite::create("star_bg.jpg");
		  bg->setPosition(Vec2(_to_add_x, _to_add_y));
		  this->addChild(bg, kBackground, kSpriteBg);
		  _bg.pushBack(bg);
	  }
  }

  if (top_right_point_covered == 0) {
	  _to_add_x = current_bg_x;
	  _to_add_y = current_bg_y + _bg.at(0)->getBoundingBox().size.height;

	  if (Check_bg_exists(Vec2(_to_add_x, _to_add_y)) == false) {
		  auto bg = Sprite::create("star_bg.jpg");
		  bg->setPosition(Vec2(_to_add_x, _to_add_y));
		  this->addChild(bg, kBackground, kSpriteBg);
		  _bg.pushBack(bg);
	  }

	  _to_add_x = current_bg_x + _bg.at(0)->getBoundingBox().size.width;
	  _to_add_y = current_bg_y;

	  if (Check_bg_exists(Vec2(_to_add_x, _to_add_y)) == false) {
		  auto bg = Sprite::create("star_bg.jpg");
		  bg->setPosition(Vec2(_to_add_x, _to_add_y));
		  this->addChild(bg, kBackground, kSpriteBg);
		  _bg.pushBack(bg);
	  }

	  _to_add_x = current_bg_x + _bg.at(0)->getBoundingBox().size.width;
	  _to_add_y = current_bg_y + _bg.at(0)->getBoundingBox().size.height;

	  if (Check_bg_exists(Vec2(_to_add_x, _to_add_y)) == false) {
		  auto bg = Sprite::create("star_bg.jpg");
		  bg->setPosition(Vec2(_to_add_x, _to_add_y));
		  this->addChild(bg, kBackground, kSpriteBg);
		  _bg.pushBack(bg);
	  }
  }


  if (bottom_right_point_covered == 0) {
	  _to_add_x = current_bg_x;
	  _to_add_y = current_bg_y - _bg.at(0)->getBoundingBox().size.height;

	  if (Check_bg_exists(Vec2(_to_add_x, _to_add_y)) == false) {
		  auto bg = Sprite::create("star_bg.jpg");
		  bg->setPosition(Vec2(_to_add_x, _to_add_y));
		  this->addChild(bg, kBackground, kSpriteBg);
		  _bg.pushBack(bg);
	  }

	  _to_add_x = current_bg_x + _bg.at(0)->getBoundingBox().size.width;
	  _to_add_y = current_bg_y;

	  if (Check_bg_exists(Vec2(_to_add_x, _to_add_y)) == false) {
		  auto bg = Sprite::create("star_bg.jpg");
		  bg->setPosition(Vec2(_to_add_x, _to_add_y));
		  this->addChild(bg, kBackground, kSpriteBg);
		  _bg.pushBack(bg);
	  }

	  _to_add_x = current_bg_x + _bg.at(0)->getBoundingBox().size.width;
	  _to_add_y = current_bg_y - _bg.at(0)->getBoundingBox().size.height;

	  if (Check_bg_exists(Vec2(_to_add_x, _to_add_y)) == false) {
		  auto bg = Sprite::create("star_bg.jpg");
		  bg->setPosition(Vec2(_to_add_x, _to_add_y));
		  this->addChild(bg, kBackground, kSpriteBg);
		  _bg.pushBack(bg);
	  }
  }

  if (bottom_left_point_covered == 0) {
	  _to_add_x = current_bg_x;
	  _to_add_y = current_bg_y - _bg.at(0)->getBoundingBox().size.height;

	  if (Check_bg_exists(Vec2(_to_add_x, _to_add_y)) == false) {
		  auto bg = Sprite::create("star_bg.jpg");
		  bg->setPosition(Vec2(_to_add_x, _to_add_y));
		  this->addChild(bg, kBackground, kSpriteBg);
		  _bg.pushBack(bg);
	  }

	  _to_add_x = current_bg_x - _bg.at(0)->getBoundingBox().size.width;
	  _to_add_y = current_bg_y;

	  if (Check_bg_exists(Vec2(_to_add_x, _to_add_y)) == false) {
		  auto bg = Sprite::create("star_bg.jpg");
		  bg->setPosition(Vec2(_to_add_x, _to_add_y));
		  this->addChild(bg, kBackground, kSpriteBg);
		  _bg.pushBack(bg);
	  }

	  _to_add_x = current_bg_x - _bg.at(0)->getBoundingBox().size.width;
	  _to_add_y = current_bg_y - _bg.at(0)->getBoundingBox().size.height;

	  if (Check_bg_exists(Vec2(_to_add_x, _to_add_y)) == false) {
		  auto bg = Sprite::create("star_bg.jpg");
		  bg->setPosition(Vec2(_to_add_x, _to_add_y));
		  this->addChild(bg, kBackground, kSpriteBg);
		  _bg.pushBack(bg);
	  }
  }

  CCLOG("tf=%d, tr=%d, bl=%d, br=%d", top_left_point_covered, top_right_point_covered, bottom_left_point_covered, bottom_right_point_covered);
  CCLOG("bg.size=%d", _bg.size());

  for (auto bg : _bg) {
	  bg->setPosition(bg->getPositionX() + x_add, bg->getPositionY() + y_add);
  }
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
