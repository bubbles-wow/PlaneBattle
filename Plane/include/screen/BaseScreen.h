#pragma once
#ifndef BASE_SCREEN_H
#define BASE_SCREEN_H

#include <thread>
#include <mutex>
#include <condition_variable>
#include <string>

#include <util/Base.h>
#include <util/MessageListener.h>

namespace Screen
{
	// 界面基类
	class BaseScreen : public Base
	{
	protected:
		int handlerId[2];			// [0] mouse, [1] key
		mutable std::mutex mtx;		// 锁
		std::condition_variable cv; // 信号量，用于暂停和终止线程
		bool paused;				// 暂停标志位
		bool ended;					// 结束标志位
		bool drawing;				// 是否正在绘制，用于防止绘制冲突（EasyX不是线程安全的）
		std::thread main;			// 主线程（逻辑和绘制绑定了）

		// 绘制屏幕
		virtual void draw() = 0;

		// 界面逻辑判断等
		inline virtual void work() {};

		/**
		 * @brief 鼠标监听
		 * @param msg 消息
		 * @return void
		 * @note 该方法用于监听鼠标事件，根据鼠标事件执行相应操作，用于在MessageListener中注册调用
		 */
		virtual void mouseListener(const ExMessage &msg);

		/**
		 * @brief 键盘监听
		 * @param msg 消息
		 * @return void
		 * @note 该方法用于监听键盘事件，根据键盘事件执行相应操作，用于在MessageListener中注册调用
		 */
		virtual void keyListener(const ExMessage &msg);
		// 主线程循环
		void loop();

	public:
		BaseScreen();
		~BaseScreen();

		// 获取绘制状态
		inline bool getDrawStatus()
		{
			return drawing;
		}

		// 启动工作线程
		void start();

		// 暂停所有线程
		void pause();

		// 恢复所有线程
		void resume();

		// 停止所有线程
		void stop();
	};
}

#endif // BASE_SCREEN_H
