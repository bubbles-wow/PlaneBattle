#pragma once
#ifndef BASE_CONTROLLER_H
#define BASE_CONTROLLER_H

#include <util/Base.h>

namespace Controller
{
	// 实体管理器基类
	class BaseController : public Base
	{
	public:
		// 控制实体移动
		virtual inline void move() {};

		// 控制实体绘制
		virtual inline void draw() const {};

		// 控制实体先移动后绘制
		virtual inline void moveAndDraw() {
			move();
			draw();
		}
	};
}

#endif // BASE_CONTROLLER_H