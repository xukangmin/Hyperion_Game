#ifndef __GAMELAYER_H__
#define __GAMELAYER_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "GameSprite.h"

USING_NS_CC;

using namespace CocosDenshion;

enum {
    kBackground,
    kMiddleground,
    kForeground
};

enum {
    kSpritePlayer,
    kSpritePlanet,
    kSpriteBoost,
    kSpriteStar,
    kSpriteBg
};

typedef enum gamestates {
    kGameIntro,
    kGamePaused,
    kGamePlay
}GameState;

class Player;

class GameLayer : public cocos2d::Scene
{
    Player * _player;
    SpriteBatchNode *_gameBatchNode;
    GameState _state;

    Size _screenSize;
    
	Vector<Sprite *> _bg;

	bool Check_bg_exists(Vec2 in_pt);

	void move_self(Vec2 vec);

	float target_dis;

	Vec2 target_dir;

	ParticleSystem * _jet;

	void createParticles(void);

	void initBG(void);

	void addBGs(Vec2 current_bg_pos, int top_left_point_covered, int top_right_point_covered, int bottom_left_point_covered, int bottom_right_point_covered);
public:
    static cocos2d::Scene* createScene();

    virtual bool init();

    void update (float dt);

    virtual bool onTouchBegan(Touch * touch, Event* event);
	  virtual void onTouchMoved(Touch * touch, Event* event);
	  virtual void onTouchEnded(Touch * touch, Event* event);
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(GameLayer);


};

#endif // __HELLOWORLD_SCENE_H__
