#pragma once
#ifndef OWN_BULLET_H
#define OWN_BULLET_H

#include <entity/Bullet.h>

namespace Entity
{
	// 玩家子弹类
	class OwnBullet : public Bullet
	{
	public:
		// 构造函数，默认位置为(0, 0)
		OwnBullet();
		// 构造函数，指定位置
		OwnBullet(int x, int y);

		// 绘制
		void draw() const;

		// 判断是否在窗口内（简化）
		bool isInside() const override;
	};
}

#endif // OWN_BULLET_H