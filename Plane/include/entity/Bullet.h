#pragma once
#ifndef BULLET_H
#define BULLET_H

#include <util/Globals.h>
#include <entity/BaseEntity.h>

namespace Entity
{
	// 子弹基类
	class Bullet : public BaseEntity
	{
	protected:
		int rad;		// 半径（子弹当作圆处理）
		COLORREF color;	// 颜色
		
		/**
		 * @brief 初始化
		 * @param speed 速度
		 * @param rad 半径
		 * @param color 颜色
		 */
		void init(float speed, int rad, COLORREF color);
	public:
		// 构造函数，默认半径为0，颜色为红色
		Bullet();
		// 构造函数，指定位置
		Bullet(int x, int y);
		// 构造函数，指定位置、速度、半径和颜色
		Bullet(int x, int y, float speed, int rad, COLORREF color);

		// 绘制
		void draw() const override;

		// 判断是否在窗口内
		virtual bool isInside() const;
	};
}

#endif // BULLET_H
