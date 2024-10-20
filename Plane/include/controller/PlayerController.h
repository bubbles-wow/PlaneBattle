#pragma once
#ifndef PLAYER_CONTROLLER_H
#define PLAYER_CONTROLLER_H

#include <sstream>

#include <controller/BaseController.h>
#include <entity/Player.h>

namespace Controller
{
	// 玩家管理器
	class PlayerController : public BaseController
	{
	private:
		std::shared_ptr<Entity::Player> playerPtr;	// 玩家实体指针
		float dx, dy;								// 玩家方向
	public:
		PlayerController();

		/**
		 * @brief 设置玩家方向
		 * @param dx x轴方向
		 * @param dy y轴方向
		 */
		void setDirection(float dx, float dy);

		/**
		 * @brief 设置玩家位置
		 * @param x x轴坐标
		 * @param y y轴坐标
		 */
		void setPosition(int x, int y);

		// 移动并绘制玩家
		inline void moveAndDraw() override
		{
			playerPtr->move();
			playerPtr->draw();
		}

		/**
		 * @brief 获取玩家实体指针
		 * @return std::shared_ptr<Entity::Player> 玩家实体指针
		 * @note 该方法用于获取玩家实体指针，以便于在其他地方使用（判断游戏结束、碰撞检测等）
		 */
		inline std::shared_ptr<Entity::Player> getPlayer()
		{
			return playerPtr;
		}
	};
}

#endif // PLAYER_CONTROLLER_H