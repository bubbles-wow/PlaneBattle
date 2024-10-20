#include <sstream>

#include <entity/Enemy2.h>

#define ENEMY2_WIDTH 45		// 敌机2宽度
#define ENEMY2_HEIGHT 30	// 敌机2高度
#define ENEMY2_SPEED 1.4	// 敌机2速度
#define ENEMY2_COLOR RED	// 敌机2颜色
#define ENEMY2_DIRECTION -1	// 敌机2方向
#define ENEMY2_HEALTH 60	// 敌机2生命值

namespace Entity
{
	RECT Enemy2::splits[3] = {
		{0, ENEMY2_HEIGHT * 2, ENEMY2_WIDTH, ENEMY2_HEIGHT * 3},
		{0, ENEMY2_HEIGHT * 1, ENEMY2_WIDTH, ENEMY2_HEIGHT * 2},
		{0, ENEMY2_HEIGHT * 0, ENEMY2_WIDTH, ENEMY2_HEIGHT * 1}};

	bool Enemy2::initSplits = false;

#pragma warning(disable : 4305)
	Enemy2::Enemy2() : Plane(0, 0, ENEMY2_WIDTH, ENEMY2_HEIGHT,
							 ENEMY2_SPEED, ENEMY2_COLOR, ENEMY2_DIRECTION, ENEMY2_HEALTH)
	{
		flag = 11;
		setDirection(0, 1);
		updatePoints();
	}

	Enemy2::Enemy2(int x, int y) : Plane(x, y, ENEMY2_WIDTH, ENEMY2_HEIGHT,
										 ENEMY2_SPEED, ENEMY2_COLOR, ENEMY2_DIRECTION, ENEMY2_HEALTH)
	{
		flag = 11;
		setDirection(0, 1);
		updatePoints();
	}
#pragma warning(default : 4305)

#pragma warning(disable : 4244)
	void Enemy2::init()
	{
		for (int i = 0; i < 3; i++)
		{
			// 左上角恒为0
			// splits[i].left *= Util::windowConfig.scale;
			splits[i].top *= Util::windowConfig.scale;
			splits[i].right *= Util::windowConfig.scale;
			splits[i].bottom *= Util::windowConfig.scale;
		}
	}
#pragma warning(default : 4244)

	void Enemy2::updatePoints()
	{
		this->Plane::updatePoints();
		points[1].y += height / 3;
		points[2].y += height / 3;
		body[0].x = points[1].x;
		body[0].y = points[1].y - height / 3;
		body[1].x = points[2].x;
		body[1].y = points[1].y;
	}

	void Enemy2::draw() const
	{
		transparentimage3(
			points[0].x - width / 2, points[0].y - height,
			width, height,
			&Util::enemy2Img,
			0, splits[health / 20 - 1].top);

		// 碰撞箱
		if (Util::debugFlag == 1)
		{
			Plane::draw();
			rectangle(body[0].x, body[0].y, body[1].x, body[1].y);
		}
	}

	void Enemy2::move()
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

	bool Enemy2::isInside() const
	{
		return y - height < Util::windowConfig.height;
	}

	bool Enemy2::isCollide(int x, int y) const
	{
		POINT p = {x, y};

		int C1 = Util::cross(points[0], points[1], p);
		int C2 = Util::cross(points[1], points[2], p);
		int C3 = Util::cross(points[2], points[0], p);

		return true ? (C1 > 0 && C2 > 0 && C3 > 0) || (C1 < 0 && C2 < 0 && C3 < 0) : x >= body[0].x && x <= body[1].x && y >= body[0].y && y <= body[1].y;
	}
}