#pragma once
#ifndef GAME_SCREEN_H
#define GAME_SCREEN_H

#include <screen/BaseScreen.h>
#include <controller/GameController.h>

namespace Screen
{
	// 游戏界面
	class GameScreen : public BaseScreen
	{
	private:
		Controller::GameController *gameController;	// 游戏实体管理器
		BaseScreen *pauseScreen;					// 暂停界面（子界面）
		BaseScreen *startScreen;					// 开始界面（父界面）

		int bgWidth, bgHeight;						// 背景图片的宽高
		int bgX, bgY;								// 背景图片的坐标（左上角）

		const wchar_t *healthHead;					// 生命信息
		int healthHeadX, healthHeadY;				// 生命信息的坐标
		int healthHeadWidth, healthHeadHeight;		// 生命信息的宽高

		int scoreHeadX, scoreHeadY;					// 分数信息的坐标
		int scoreHeadWidth, scoreHeadHeight;		// 分数信息的宽高
		int barWidth, barHeight;					// 生命条的宽高

		int borderWidth;							// 边框宽度
		int textSize;								// 文字大小

		long long startTime;						// 游戏开始时间

		int taskIndex;								// 任务索引
		std::vector<std::function<void()>> taskList;// 任务列表

		Util::GameOverData data;					// 游戏结束数据，用于传递消息创建MessageBox，防止指针被销毁
	protected:
		// 界面绘制
		void draw() override;

		// 界面逻辑判断等
		inline void work() override
		{
			taskList[taskIndex]();
		}

		// 初始化任务列表
		void initTaskList();

		// 游戏结束
		void gameOver();

		// 键盘监听
		void keyListener();

		/**
		 * @brief 键盘监听
		 * @param msg 消息
		 * @return void
		 * @note 该方法用于监听键盘事件，根据键盘事件执行相应操作，用于在MessageListener中注册调用
		 */
		void keyListener(const ExMessage &msg) override;

		/**
		 * @brief 鼠标监听
		 * @param msg 消息
		 * @return void
		 * @note 该方法用于监听鼠标事件，根据鼠标事件执行相应操作，用于在MessageListener中注册调用
		 */
		void mouseListener(const ExMessage &msg) override;
	public:
		GameScreen();
		// 构造函数，指定开始界面指针
		GameScreen(BaseScreen *startScreen);

		// 开始新游戏
		void startNewGame();

		// 启动游戏
		void start();

		// 暂停游戏
		void pause();

		// 继续游戏
		void resume();

		// 停止游戏
		void stop();
	};
}

#endif // GAME_SCREEN_H
