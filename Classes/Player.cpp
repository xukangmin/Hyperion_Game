#include "Player.h"

Player::Player(void)
{
}

Player::~Player(void){}

Player* Player::create () {
	auto sprite = new Player();

	if (sprite && sprite->initWithSpriteFrameName("space_ship.png")) {
				sprite->reset();
				sprite->autorelease();
        return sprite;
	}


	CC_SAFE_DELETE(sprite);
	return nullptr;
}

void Player::reset() {
	_speed = DEFAULT_SPEED;
	_pos.x = 0;
	_pos.y = 0;
}
