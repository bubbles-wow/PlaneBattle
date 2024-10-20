#pragma once
#ifndef PAUSE_SCREEN_H
#define PAUSE_SCREEN_H

#include <screen/BaseScreen.h>

namespace Screen
{
	// 暂停界面
	class PauseScreen : public BaseScreen
	{
	protected:
		BaseScreen *gameScreen;		// 游戏界面

		const wchar_t *pauseHead;	// 暂停界面标题
		int headWidth, headHeight; 	// 标题的宽高
		int headX, headY;		   	// 标题的坐标
		const wchar_t *pauseTips;  	// 暂停提示
		int tipsWidth, tipsHeight; 	// 提示的宽高
		int tipsX, tipsY;		   	// 提示的坐标

		int textSize; 				// 文字大小（默认标题为提示的两倍）

		// 界面绘制
		void draw() override;

		/**
		 * @brief 鼠标监听
		 * @param msg 消息
		 * @return void
		 * @note 该方法用于监听鼠标事件，根据鼠标事件执行相应操作，用于在MessageListener中注册调用
		 */
		void mouseListener(const ExMessage &msg) override;

		/**
		 * @brief 键盘监听
		 * @param msg 消息
		 * @return void
		 * @note 该方法用于监听键盘事件，根据键盘事件执行相应操作，用于在MessageListener中注册调用
		 */
		void keyListener(const ExMessage &msg) override;

		// 构造函数，一般不用这个
		PauseScreen();
	public:
		// 构造函数，必须指定游戏界面指针
		PauseScreen(BaseScreen *gameScreen);
	};
}

#endif // PAUSE_SCREEN_H
