#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "cocos2d.h"
#include "GameSprite.h"
#define DEFAULT_SPEED 10 // pixel / s


USING_NS_CC;

class Player : public GameSprite {

private:

public:

	CC_SYNTHESIZE(Point, _vector, Vector);
	CC_SYNTHESIZE(float, _speed, Speed);
	CC_SYNTHESIZE(Point, _target, Target);
	CC_SYNTHESIZE(Point, _pos, Pos);

	void reset (void);

	Player(void);
	virtual ~Player();

	static Player* create();

};



#endif
