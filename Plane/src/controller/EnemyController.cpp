#include <sstream>
#include <execution>

#include <controller/EnemyController.h>
#include <util/Globals.h>

namespace Controller {
	EnemyController::EnemyController() : BaseController() {
		if (Entity::Enemy1::initSplits == false) {
			Entity::Enemy1::init();
			Entity::Enemy1::initSplits = true;
		}
		if (Entity::Enemy2::initSplits == false) {
			Entity::Enemy2::init();
			Entity::Enemy2::initSplits = true;
		}
	}

	void EnemyController::addEnemy(const std::shared_ptr<Entity::Plane>& enemy) {
		std::unique_lock<std::shared_mutex> lock(mutex);
		enemyPtrs.push_back(enemy);
		Util::log(
			"Add an enemy. [position=(" + std::to_string(enemy->getX()) +
			", " + std::to_string(enemy->getY()) + ")]",
			getClassName()
		);
	}

	void EnemyController::moveAndDraw() {
		std::unique_lock<std::shared_mutex> lock(mutex);
		std::erase_if(enemyPtrs, [this](const std::shared_ptr<Entity::Plane>& enemy) {
			if (!enemy->isInside() || enemy->getHealth() <= 0) {
				Util::log(
					"Remove an enemy. [position=(" + std::to_string(enemy->getX()) +
					", " + std::to_string(enemy->getY()) + ")]",
					getClassName()
				);
				return true;
			}
			enemy->move();
			enemy->draw();
			return false;
		});
	}
}