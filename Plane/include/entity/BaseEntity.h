#pragma once
#ifndef BASE_ENTITY_H
#define BASE_ENTITY_H

#include <util/Base.h>

namespace Entity
{
	// 实体基类
	class BaseEntity : public Base
	{
	protected:
		int x, y;			// 位置
		float dx, dy;		// 方向
		float moveX, moveY; // 移动距离
		float speed;		// 速度
	public:
		// 构造函数，默认位置为(0, 0)
		BaseEntity();
		/**
		 * @brief 构造函数
		 * @param x x坐标
		 * @param y y坐标
		 * @note 默认所有属性均为0
		 */
		BaseEntity(int x, int y);

		// 根据方向和速度移动
		virtual void move();

		// 绘制
		virtual void draw() const = 0;

		/**
		 * @brief 获取x坐标
		 * @return int x
		 */
		inline int getX() const {
			return x;
		};

		/**
		 * @brief 获取y坐标
		 * @return int y
		 */
		inline int getY() const {
			return y;
		};

		/**
		 * @brief 获取x方向增量
		 * @return float dx
		 */
		inline float getDx() const {
			return dx;
		};

		/**
		 * @brief 获取y方向增量
		 * @return float dy
		 */
		inline float getDy() const {
			return dy;
		};

		/**
		 * @brief 获取位置
		 * @return std::pair<int, int> 位置，包含x和y
		 */
		inline std::pair<int, int> getPosition() const {
			return std::make_pair(x, y);
		};

		/**
		 * @brief 获取方向
		 * @return std::pair<float, float> 方向，包含dx和dy
		 */
		inline std::pair<float, float> getDirection() const {
			return std::make_pair(dx, dy);
		};

		/**
		 * @brief 设置位置
		 * @param x x坐标
		 * @param y y坐标
		 */
		void setPosition(int x, int y);

		/**
		 * @brief 设置方向
		 * @param dx x方向增量
		 * @param dy y方向增量
		 */
		void setDirection(float dx, float dy);

		/**
		 * @brief 设置速度
		 * @param speed 速度
		 */
		void setSpeed(float speed);
	};
}

#endif // BASE_ENTITY_H