#pragma once
#include <execution>

#include <controller/BulletController.h>
#include <util/Globals.h>

namespace Controller {
	void BulletController::addBullet(const std::shared_ptr<Entity::Bullet>& bullet, Entity::BulletType type) {
		std::unique_lock<std::shared_mutex> lock(mutex);
		if (type == Entity::BulletType::ENEMY) {
			enemyBulletPtrs.push_back((const std::shared_ptr<Entity::EnemyBullet>&)bullet);
			Util::log(
				"Add a EnemyBullet. [position=(" + std::to_string(bullet->getX()) + 
				", " + std::to_string(bullet->getY()) + ")]", getClassName()
			);
		}
		else if (type == Entity::BulletType::OWN) {
			ownBulletPtrs.push_back((const std::shared_ptr<Entity::OwnBullet>&)bullet);
			Util::log(
				"Add a OwnBullet. [position=(" + std::to_string(bullet->getX()) +
				", " + std::to_string(bullet->getY()) + ")]", getClassName()
			);
		}
	}

	void BulletController::moveAndDraw() {
		std::unique_lock<std::shared_mutex> lock(mutex);
		std::erase_if(enemyBulletPtrs, [this](const std::shared_ptr<Entity::EnemyBullet>& bullet) {
			if (!bullet->isInside()) {
				Util::log(
					"Remove an EnemyBullet. [position=(" + std::to_string(bullet->getX()) +
					", " + std::to_string(bullet->getY()) + ")]",
					getClassName()
				);
				// 移除场景外的实体
				return true;
			}
			// 不需要移除的实体继续移动和绘制
			bullet->move();
			bullet->draw();
			return false;
		});
		std::erase_if(ownBulletPtrs, [this](const std::shared_ptr<Entity::OwnBullet>& bullet) {
			if (!bullet->isInside()) {
				Util::log(
					"Remove an own. [position=(" + std::to_string(bullet->getX()) +
					", " + std::to_string(bullet->getY()) + ")]",
					getClassName()
				);
				return true;
			}
			bullet->move();
			bullet->draw();
			return false;
		});
	}
}