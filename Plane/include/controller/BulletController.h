#pragma once
#ifndef BULLET_CONTROLLER_H
#define BULLET_CONTROLLER_H

#include <vector>
#include <shared_mutex>

#include <controller/BaseController.h>
#include <entity/BulletType.h>
#include <entity/OwnBullet.h>
#include <entity/EnemyBullet.h>

namespace Controller
{
	// 子弹管理器
	class BulletController : public BaseController
	{
	private:
		std::vector<std::shared_ptr<Entity::OwnBullet>> ownBulletPtrs;		// 玩家子弹列表
		std::vector<std::shared_ptr<Entity::EnemyBullet>> enemyBulletPtrs;	// 敌人子弹列表
		mutable std::shared_mutex mutex;									// 互斥锁
	public:
		/**
		 * @brief 添加子弹
		 * @param bullet 子弹实体
		 * @param type 子弹类型
		 * @return void
		 */
		void addBullet(const std::shared_ptr<Entity::Bullet> &bullet, Entity::BulletType type);

		// 移动并绘制所有子弹
		void moveAndDraw() override;

		/**
		 * @brief 获取玩家子弹列表
		 * @return std::vector<std::shared_ptr<Entity::OwnBullet>> & 玩家子弹列表
		 * @note 该方法用于获取敌人子弹列表，以便于在其他地方使用（如碰撞检测）
		 */
		inline std::vector<std::shared_ptr<Entity::OwnBullet>> &getOwnBulletList()
		{
			return ownBulletPtrs;
		}

		/**
		 * @brief 获取敌人子弹列表
		 * @return std::vector<std::shared_ptr<Entity::EnemyBullet>> & 敌人子弹列表
		 * @note 该方法用于获取敌人子弹列表，以便于在其他地方使用（如碰撞检测）
		 */
		inline std::vector<std::shared_ptr<Entity::EnemyBullet>> &getEnemyBulletList()
		{
			return enemyBulletPtrs;
		}
	};
}

#endif // BULLET_CONTROLLER_H