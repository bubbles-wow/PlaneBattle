#pragma once
#include <sstream>

#include <controller/PlayerController.h>
#include <util/Globals.h>

namespace Controller {
	PlayerController::PlayerController() : 
		playerPtr(std::make_shared<Entity::Player>(
			Util::windowConfig.width / 2, Util::windowConfig.height)) {}

	void PlayerController::setDirection(float dx, float dy) {
		if (std::abs(this->dx - dx) > 0.01 || std::abs(this->dy - dy) > 0.01) {
			this->dx = dx;
			this->dy = dy;
			playerPtr->setDirection(dx, dy);
			Util::log(
				"Set Player direction=(" + std::to_string(dx) + ", " + std::to_string(dy) + ")",
				getClassName()
			);
		}
	}

	void PlayerController::setPosition(int x, int y) {
		playerPtr->setPosition(x, y);
		Util::log(
			"Set Player position=(" + std::to_string(x) + ", " + std::to_string(y) + ")", 
			getClassName()
		);
	}
}