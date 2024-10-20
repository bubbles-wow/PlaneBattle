#include <entity/EnemyBullet.h>
#include <util/Globals.h>

#define ENEMY_BULLET_RAD 4
#define ENEMY_BULLET_SPEED 2
#define ENEMY_BULLET_COLOR RED

namespace Entity {
	EnemyBullet::EnemyBullet() : Bullet(0, 0, ENEMY_BULLET_SPEED, ENEMY_BULLET_RAD, ENEMY_BULLET_COLOR) {
		setDirection(0, 1);
	}

	EnemyBullet::EnemyBullet(int x, int y) : Bullet(x, y, ENEMY_BULLET_SPEED, ENEMY_BULLET_RAD, ENEMY_BULLET_COLOR) {
		setDirection(0, 1);
	}

	void EnemyBullet::draw() const {
		transparentimage3(x - rad, y - rad, &Util::enemyBulletImg);
		if (Util::debugFlag == 1) {
			Bullet::draw();
		}
	}

	bool EnemyBullet::isInside() const {
		return y - rad < Util::windowConfig.height;
	}
}