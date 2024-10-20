#pragma once
#ifndef PLAYER_H
#define PLAYER_H

#include <entity/PLane.h>
#include <util/Globals.h>

namespace Entity
{
	// 玩家飞机类（该飞机为头部三角形，机身矩形的组合）
	class Player : public Plane
	{
	protected:
		POINT body[2]; // 表示机身的矩形两个顶点（左上右下）
		
		// 更新顶点
		void updatePoints();
	public:
		Player();
		Player(int x, int y);

		// 移动
		void move() override;

		// 绘制
		void draw() const override;

		/**
		 * @brief 判断是否与点(x, y)碰撞
		 * @param x x坐标
		 * @param y y坐标
		 * @return bool 是否碰撞
		 */
		bool isCollide(int x, int y) const override;
	};
}

#endif // PLAYER_H