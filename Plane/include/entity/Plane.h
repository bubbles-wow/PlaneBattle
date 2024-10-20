#pragma once
#ifndef PLANE_H
#define PLANE_H

#include <entity/BaseEntity.h>
#include <util/Globals.h>

namespace Entity
{
	// 飞机基类
	class Plane : public BaseEntity
	{
	protected:
		int width, height;			// 宽高
		int direction;				// 方向，1为向上，-1为向下
		int flag;					// 标记飞机类型，1为玩家，10、11为敌机
		long long lastShotTime;		// 上次射击时间
		int health;					// 生命值
		COLORREF color;				// 颜色
		POINT points[3];			// 三角形三个顶点（作为三角形处理）

		/**
		 * @brief 初始化
		 * @param width 宽
		 * @param height 高
		 * @param speed 速度
		 * @param color 颜色
		 * @param direction 方向
		 * @param health 生命值
		 */
		void init(int width, int height, float speed,
				  COLORREF color, int direction, int health);

		/**
		 * @brief 更新三角形顶点
		 */
		void updatePoints();
	public:
		Plane();
		Plane(int x, int y);
		Plane(int x, int y, int width, int height, float speed,
			  COLORREF color, int direction, int health);

		virtual ~Plane() = default;

		// 绘制
		virtual void draw() const override;

		// 移动
		virtual void move() override;

		/**
		 * @brief 获取上次射击时间
		 * @return long long 上次射击时间
		 */
		inline long long getLastShotTime()
		{
			return lastShotTime;
		}

		/**
		 * @brief 获取飞机标记
		 * @return int 标记
		 */
		inline int getFlag()
		{
			return flag;
		}

		/**
		 * @brief 获取飞机的宽度
		 * @return int 宽度
		 */
		inline int getWidth()
		{
			return width;
		}

		/**
		 * @brief 获取飞机的生命值
		 * @return int 生命值
		 */
		inline int getHealth()
		{
			return health;
		}

		/**
		 * @brief 设置飞机的颜色
		 * @param color 颜色
		 */
		inline void setColor(COLORREF color) {
			this->color = color;
		};

		/**
		 * @brief 设置飞机的大小
		 * @param width 宽度
		 * @param height 高度
		 */
		void setSize(int width, int height);

		/**
		 * @brief 设置飞机的方向
		 * @param direction 方向
		 */
		inline void setPlaneDirection(int direction) {
			this->direction = direction;
		};

		/**
		 * @brief 设置上次射击时间
		 * @param time 时间
		 */
		inline void setLastShotTime(long long time) {
			this->lastShotTime = time;
		};

		/**
		 * @brief 设置生命值
		 * @param health 生命值
		 */
		inline void setHealth(int health) {
			this->health = health;
		};

		/**
		 * @brief 改变生命值
		 * @param diff 变化值
		 */
		inline void changeHealth(int diff) {
			health += diff;
		};

		/**
		 * @brief 判断是否在窗口内
		 * @return bool 是否在窗口内
		 */
		virtual bool isInside() const;

		/**
		 * @brief 判断是否与点(x, y)碰撞
		 * @param x x坐标
		 * @param y y坐标
		 * @return bool 是否碰撞
		 */
		virtual bool isCollide(int x, int y) const;
	};
}

#endif // PLANE_H
