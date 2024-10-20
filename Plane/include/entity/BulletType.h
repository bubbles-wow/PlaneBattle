#pragma once
#ifndef BULLET_TYPE_H
#define BULLET_TYPE_H

namespace Entity {
	/**
	 * @brief 子弹类型
	 * @param OWN 玩家子弹
	 * @param ENEMY 敌方子弹
	 */
	enum class BulletType {
		OWN,
		ENEMY
	};
}

#endif // BULLET_TYPE_H
