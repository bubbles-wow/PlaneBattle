#pragma once
#include <entity/Bullet.h>

#define RAD 5
#define BULLET_SPEED 1

namespace Entity
{
	Bullet::Bullet() : BaseEntity()
	{
		init(BULLET_SPEED, RAD, RED);
	}

	Bullet::Bullet(int x, int y) : BaseEntity(x, y)
	{
		init(BULLET_SPEED, RAD, RED);
	}

	Bullet::Bullet(int x, int y, float speed, int rad, COLORREF color) : BaseEntity(x, y)
	{
		init(speed, rad, color);
	}

	void Bullet::init(float speed, int rad, COLORREF color)
	{
#pragma warning(disable : 4244)
		this->speed = speed * Util::windowConfig.scale;
		this->rad = rad * Util::windowConfig.scale;
#pragma warning(default : 4244)
		this->color = color;
	}

	void Bullet::draw() const
	{
		// setfillcolor(color);
		setlinecolor(color);
		setlinestyle(PS_SOLID, 2);
		circle(x, y, rad);
	}

	bool Bullet::isInside() const
	{
		return this->x > -rad && this->y > -rad &&
			   this->x < Util::windowConfig.width + rad && this->y < Util::windowConfig.height + rad;
	}
}
