#include <sstream>

#include <entity/Enemy1.h>

#define ENEMY1_WIDTH 45		// 敌机1宽度
#define ENEMY1_HEIGHT 30	// 敌机1高度
#define ENEMY1_SPEED 1.4	// 敌机1速度
#define ENEMY1_COLOR RED	// 敌机1颜色
#define ENEMY1_DIRECTION -1	// 敌机1方向
#define ENEMY1_HEALTH 50	// 敌机1生命值

namespace Entity
{
	RECT Enemy1::splits[5] = {
		{0, ENEMY1_HEIGHT * 4, ENEMY1_WIDTH, ENEMY1_HEIGHT * 5},
		{0, ENEMY1_HEIGHT * 3, ENEMY1_WIDTH, ENEMY1_HEIGHT * 4},
		{0, ENEMY1_HEIGHT * 2, ENEMY1_WIDTH, ENEMY1_HEIGHT * 3},
		{0, ENEMY1_HEIGHT * 1, ENEMY1_WIDTH, ENEMY1_HEIGHT * 2},
		{0, ENEMY1_HEIGHT * 0, ENEMY1_WIDTH, ENEMY1_HEIGHT * 1}};

	bool Enemy1::initSplits = false;

#pragma warning(disable : 4305)
	Enemy1::Enemy1() : Plane(0, 0, ENEMY1_WIDTH, ENEMY1_HEIGHT, ENEMY1_SPEED,
							 ENEMY1_COLOR, ENEMY1_DIRECTION, ENEMY1_HEALTH)
	{
		flag = 10;
		setDirection(0, 1);
		updatePoints();
	}

	Enemy1::Enemy1(int x, int y) : Plane(x, y, ENEMY1_WIDTH, ENEMY1_HEIGHT, ENEMY1_SPEED,
										 ENEMY1_COLOR, ENEMY1_DIRECTION, ENEMY1_HEALTH)
	{
		flag = 10;
		setDirection(0, 1);
		updatePoints();
	}
#pragma warning(default : 4305)

#pragma warning(disable : 4244)
	void Enemy1::init()
	{
		for (int i = 0; i < 5; i++)
		{
			// 左上角恒为0
			// splits[i].left *= Util::windowConfig.scale;
			splits[i].top *= Util::windowConfig.scale;
			splits[i].right *= Util::windowConfig.scale;
			splits[i].bottom *= Util::windowConfig.scale;
		}
	}
#pragma warning(default : 4244)

	void Enemy1::move()
	{
		moveY += dy;
		int deltaY = static_cast<int>(moveY);

		if (deltaY != 0)
		{
			y += deltaY;
			moveY -= deltaY;
		}
		updatePoints();
	}

	void Enemy1::updatePoints()
	{
		this->Plane::updatePoints();
		body[0].x = x - width / 2;
		body[0].y = y - height;
		body[1].x = x + width / 2;
		body[1].y = y;
	}

	void Enemy1::draw() const
	{
		transparentimage3(
			body[0].x, body[0].y,
			width, height,
			&Util::enemy1Img,
			0, splits[health / 10 - 1].top);
		if (Util::debugFlag == 1)
		{
			setlinestyle(PS_SOLID, 2);
			setlinecolor(color);
			rectangle(body[0].x, body[0].y, body[1].x, body[1].y);
		}
	}

	bool Enemy1::isInside() const
	{
		return y - height < Util::windowConfig.height;
	}

	bool Enemy1::isCollide(int x, int y) const
	{
		return x >= body[0].x && x <= body[1].x && y >= body[0].y && y <= body[1].y;
	}
}