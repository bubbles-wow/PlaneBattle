#pragma once
#ifndef START_SCREEN_H
#define START_SCREEN_H

#include <screen/BaseScreen.h>

namespace Screen
{
	// 开始界面
	class StartScreen : public BaseScreen
	{
	protected:
		BaseScreen *gameScreen; // 游戏界面（子界面）

		const wchar_t *startHead;  // 开始界面标题
		int headWidth, headHeight; // 标题的宽高
		int headX, headY;		   // 标题的坐标

		const wchar_t *startTips;  // 开始提示
		int tipsWidth, tipsHeight; // 提示的宽高
		int tipsX, tipsY;		   // 提示的坐标

		int textSize; // 文字大小（默认标题为提示的两倍）

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

	public:
		// 构造函数
		StartScreen();

		// 析构函数，必须释放游戏界面指针
		~StartScreen();

		// 开始新游戏
		void startNewGame();

		// 开始界面
		void start();

		// 结束游戏
		void stop();

		// 暂停游戏
		inline void pauseGameScreen()
		{
			if (gameScreen != nullptr)
			{
				gameScreen->pause();
			}
		}

		// 继续游戏
		inline void resumeGameScreen()
		{
			if (gameScreen != nullptr)
			{
				gameScreen->resume();
			}
		}

		// 获取游戏界面指针
		inline BaseScreen *getGameScreen()
		{
			return gameScreen;
		}
	};
}

#endif // START_SCREEN_H
