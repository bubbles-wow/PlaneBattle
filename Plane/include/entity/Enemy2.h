#pragma once
#ifndef ENEMY_2_H
#define ENEMY_2_H

#include <entity/Plane.h>

namespace Entity
{
	// 敌机2（该飞机为头部三角形，机身矩形的组合）
	class Enemy2 : public Plane
	{
	protected:
		static RECT splits[3];	// 贴图切割位置，展示不同状态
		POINT body[2];			// 表示机身的矩形两个顶点（左上右下）

		// 更新顶点（简化）
		void updatePoints();
	public:
		Enemy2();
		Enemy2(int x, int y);

		static bool initSplits;	// 是否初始化过贴图切割位置
		// 初始化贴图切割位置
		static void init();

		// 绘制
		void draw() const override;

		// 移动
		void move() override;

		/**
		 * @brief 判断是否在窗口内
		 * @return bool 是否在窗口内
		 */
		bool isInside() const override;

		/**
		 * @brief 判断是否与点(x, y)碰撞
		 * @param x x坐标
		 * @param y y坐标
		 * @return bool 是否碰撞
		 */
		bool isCollide(int x, int y) const override;
	};
}

#endif // ENEMY_2_H
