#include <entity/BaseEntity.h>
#include <util/Globals.h>

namespace Entity
{
	BaseEntity::BaseEntity() : x(0), y(0), dx(0), dy(0),
							   moveX(0), moveY(0), speed(0) {}

	BaseEntity::BaseEntity(int x, int y) : x(x), y(y), dx(0), dy(0),
										   moveX(0), moveY(0), speed(0) {}

	void BaseEntity::setPosition(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	void BaseEntity::setDirection(float dx, float dy)
	{
		if (dx * dx + dy * dy - 1 > 0.001)
		{
			Util::log("Invalid direction.", getClassName(), Util::LogLevel::WARNING);
		}
		// 事先计算好增量，减少计算过程
		this->dx = dx * speed * Util::windowConfig.scale;
		this->dy = dy * speed * Util::windowConfig.scale;
	}

	void BaseEntity::setSpeed(float speed)
	{
#pragma warning(disable : 4244)
		this->dx = dx * speed / this->speed;
		this->dy = dy * speed / this->speed;
		this->speed = speed * Util::windowConfig.scale;
#pragma warning(default : 4244)
	}

	void BaseEntity::move()
	{
		moveX += dx;
		moveY += dy;

		int deltaX = static_cast<int>(moveX);
		int deltaY = static_cast<int>(moveY);

		if (deltaX != 0)
		{
			x += deltaX;
			moveX -= deltaX;
		}
		if (deltaY != 0)
		{
			y += deltaY;
			moveY -= deltaY;
		}
	}
}