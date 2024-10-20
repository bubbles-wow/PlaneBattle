#pragma once
#ifndef ENEMY_BULLET_H
#define ENEMY_BULLET_H

#include <entity/Bullet.h>

namespace Entity
{
	// 敌方子弹类
	class EnemyBullet : public Bullet
	{
	public:
		// 构造函数，默认位置为(0, 0)
		EnemyBullet();

		// 构造函数，指定位置
		EnemyBullet(int x, int y);

		// 绘制
		void draw() const override;

		// 判断是否在窗口内（简化）
		bool isInside() const override;
	};
}

#endif