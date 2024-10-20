#include <entity/Plane.h>

namespace Entity {
	Plane::Plane() : BaseEntity() {
		init(30, 30, 2, WHITE, 1, 50);
	}

	Plane::Plane(int x, int y) : BaseEntity(x, y) {
		init(30, 30, 2, WHITE, 1, 50);
	}

	Plane::Plane(int x, int y, int width, int height, float speed, COLORREF color, int direction, int health) : BaseEntity(x, y) {
		init(width, height, speed, color, direction, health);
	}

	void Plane::init(int width, int height, float speed, COLORREF color, int direction, int health) {
		this->lastShotTime = 0;
		this->flag = 0;
		// 适配窗口缩放大小
		#pragma warning(disable:4244)
		this->width = width * Util::windowConfig.scale;
		this->height = height * Util::windowConfig.scale;
		this->speed = speed * Util::windowConfig.scale;
		#pragma warning(default:4244)
		this->color = color;
		this->direction = direction;
		this->health = health;
		updatePoints();
	}

	void Plane::setSize(int width, int height) {
		#pragma warning(disable:4244)
		this->width = width * Util::windowConfig.scale;
		this->height = height * Util::windowConfig.scale;
		#pragma warning(default:4244)
		updatePoints();
	}

	void Plane::draw() const {
		//setfillcolor(color);
		setlinestyle(PS_SOLID, 2);
		setlinecolor(color);
		polygon(points, 3);
	}

	void Plane::move() {
		BaseEntity::move();
		updatePoints();
	}

	void Plane::updatePoints() {
		points[0].x = x;
		points[0].y = y;
		points[1].x = x - direction * width / 2;
		points[1].y = y + direction * height;
		points[2].x = x + direction * width / 2;
		points[2].y = y + direction * height;
	}

	bool Plane::isInside() const {
		return x > 0 && y > 0 &&
			x - width < Util::windowConfig.width &&
			y - height < Util::windowConfig.height;
	}

	bool Plane::isCollide(int x, int y) const {
		return false;
	}
}