#include <util/Globals.h>
#include <entity/OwnBullet.h>

#define OWN_BULLET_RAD 4
#define OWN_BULLET_SPEED 2
#define OWN_BULLET_COLOR BLUE

namespace Entity {
	#pragma warning(disable: 4305)
	OwnBullet::OwnBullet() : Bullet(0, 0, OWN_BULLET_SPEED, OWN_BULLET_RAD, OWN_BULLET_COLOR) {
		setDirection(0, -1);
	}

	OwnBullet::OwnBullet(int x, int y) : Bullet(x, y, OWN_BULLET_SPEED, OWN_BULLET_RAD, OWN_BULLET_COLOR) {
		setDirection(0, -1);
	}
	#pragma warning(default: 4305)

	void OwnBullet::draw() const {
		transparentimage3(x - rad, y - rad, &Util::ownBulletImg);
		if (Util::debugFlag == 1) {
			Bullet::draw();
		}
	}

	bool OwnBullet::isInside() const {
		return y - rad > 0;
	}
}