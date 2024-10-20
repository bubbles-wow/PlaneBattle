#pragma once
#ifndef ENEMY_CONTROLLER_H
#define ENEMY_CONTROLLER_H

#include <vector>
#include <shared_mutex>

#include <controller/BaseController.h>
#include <entity/Enemy1.h>
#include <entity/Enemy2.h>

namespace Controller
{
	// 敌人管理器
	class EnemyController : BaseController
	{
	protected:
		std::vector<std::shared_ptr<Entity::Plane>> enemyPtrs; // 敌人列表
		mutable std::shared_mutex mutex;					   // 锁
	public:
		EnemyController();

		/**
		 * @brief 添加敌人
		 * @param enemy 敌人实体，可以是Enemy1或Enemy2
		 * @return void
		 */
		void addEnemy(const std::shared_ptr<Entity::Plane> &enemy);

		// 移动并绘制敌人
		void moveAndDraw() override;

		/**
		 * @brief 获取敌人列表
		 * @return std::vector<std::shared_ptr<Entity::Plane>>& 敌人列表
		 * @note 该方法用于获取敌人子弹列表，以便于在其他地方使用（如碰撞检测）
		 */
		inline std::vector<std::shared_ptr<Entity::Plane>> &getEnemyList()
		{
			return enemyPtrs;
		}
	};
}

#endif // ENEMY_CONTROLLER_H