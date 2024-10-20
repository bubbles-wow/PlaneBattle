#pragma once
#include <sstream>

#include <entity/Player.h>
#include <util/Globals.h>

#define PLAYER_WIDTH 50		// 玩家飞机宽度
#define PLAYER_HEIGHT 50	// 玩家飞机高度
#define PLAYER_SPEED 1.8	// 玩家飞机速度
#define PLAYER_COLOR BLUE	// 玩家飞机颜色
#define PLAYER_DIRECTION 1	// 玩家飞机方向
#define PLAYER_HEALTH 100	// 玩家飞机生命值

namespace Entity
{
#pragma warning(disable : 4305)
	Player::Player() : Plane(0, 0, PLAYER_WIDTH, PLAYER_HEIGHT,
							 PLAYER_SPEED, PLAYER_COLOR, PLAYER_DIRECTION, PLAYER_HEALTH)
	{
		flag = 1;
		updatePoints();
	}

	Player::Player(int x, int y) : Plane(x, y, PLAYER_WIDTH, PLAYER_HEIGHT,
										 PLAYER_SPEED, PLAYER_COLOR, PLAYER_DIRECTION, PLAYER_HEALTH)
	{
		flag = 1;
		updatePoints();
	}
#pragma warning(default : 4305)

	void Player::updatePoints()
	{
		this->Plane::updatePoints();
		points[1].y -= height / 2;
		points[2].y -= height / 2;
		body[0].x = points[0].x - width / 6;
		body[0].y = points[0].y + height / 2;
		body[1].x = points[0].x + width / 6;
		body[1].y = points[0].y + height;
	}

#pragma warning(disable : 4244)
	void Player::move()
	{
		BaseEntity::move();
		// 防止超出边界
		if (x > Util::windowConfig.width - width / 2)
		{
			x = Util::windowConfig.width - width / 2;
		}
		if (x < width / 2)
		{
			x = width / 2;
		}
		if (y > Util::windowConfig.height - height / 2)
		{
			y = Util::windowConfig.height - height / 2;
		}
		if (y < height / 2)
		{
			y = height / 2;
		}
		updatePoints();
	}
#pragma warning(default : 4244)

	void Player::draw() const
	{
		transparentimage3(int(points[0].x - width / 2), int(points[0].y), &Util::playerImg);

		// 碰撞箱绘制
		if (Util::debugFlag == 1)
		{
			Plane::draw();
			/*setlinestyle(PS_SOLID, 2);
			setlinecolor(color);*/
			rectangle(body[0].x, body[0].y, body[1].x, body[1].y);
		}
	}

	bool Player::isCollide(int x, int y) const
	{
		POINT p = {x, y};
		// 采用叉积判断点是否在三角形内，即点在每个向量的同一侧就是在三角形里面了
		int C1 = Util::cross(points[0], points[1], p);
		int C2 = Util::cross(points[1], points[2], p);
		int C3 = Util::cross(points[2], points[0], p);

		return true ? (C1 > 0 && C2 > 0 && C3 > 0) || (C1 < 0 && C2 < 0 && C3 < 0) :	 // 判断是否在三角形中
				   x >= body[0].x && x <= body[1].x && y >= body[0].y && y <= body[1].y; // 判断是否在矩形中
	}
}