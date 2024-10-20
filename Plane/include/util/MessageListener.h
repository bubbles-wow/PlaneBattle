#pragma once
#ifndef MESSAGE_LISTENER_H
#define MESSAGE_LISTENER_H

#include <mutex>
#include <vector>
#include <thread>
#include <functional>
#include <condition_variable>

#include <util/Globals.h>
#include <util/MessageType.h>

namespace Util
{
	// 消息处理函数类型
	typedef std::function<void(const ExMessage &)> MessageHandler;

	// 消息监听器
	class MessageListener
	{
	protected:
		std::map<int, MessageHandler> mouseHandlers;	// 鼠标消息处理函数列表
		std::map<int, MessageHandler> keyHandlers;		// 键盘消息处理函数列表
		std::map<int, MessageHandler> windowHandlers;	// 窗口消息处理函数列表
		int handlerId;									// 记录处理函数id，用于删除

		std::thread worker;								// 监听线程
		mutable std::mutex mutex;						// 互斥锁
		std::condition_variable cv;						// 条件变量
		bool isPause;									// 暂停标志位
		bool isEnd;										// 结束标志位

		/**
		 * @brief 选择处理函数
		 * @param type 消息类型
		 * @return std::map<int, MessageHandler>*
		 */
		std::map<int, MessageHandler> *selectHandlers(MessageType type);

		/**
		 * @brief 监听消息
		 * @return void
		 */
		void listener();

		/**
		 * @brief 处理消息
		 * @param msg 消息
		 * @return void
		 */
		void onMessage(const ExMessage &msg);

		/**
		 * @brief 处理键盘消息
		 * @param msg 消息
		 * @return void
		 */
		void onKeyMessage(const ExMessage &msg);

		/**
		 * @brief 处理鼠标消息
		 * @param msg 消息
		 * @return void
		 */
		void onMouseMessage(const ExMessage &msg);

		/**
		 * @brief 处理窗口消息
		 * @param msg 消息
		 * @return void
		 */
		void onWindowMessage(const ExMessage &msg);

	public:
		MessageListener();

		/**
		 * @brief 添加消息处理函数
		 * @param handler 消息处理函数
		 * @param type 消息类型
		 * @return int 处理函数id
		 */
		int addHandler(const MessageHandler &handler, MessageType type);

		/**
		 * @brief 移除消息处理函数
		 * @param id 处理函数id
		 * @return void
		 */
		void removeHandler(int id);

		// 启动监听线程
		inline void start()
		{
			isPause = false;
			worker = std::thread(&MessageListener::listener, this);
		}

		// 暂停监听线程
		inline void pause()
		{
			isPause = true;
		}

		// 恢复监听线程
		inline void resume()
		{
			isPause = false;
		}

		// 停止监听线程
		inline void stop()
		{
			isPause = false;
			this->isEnd = true;
			worker.join();
		}
	};

	extern MessageListener listener;
}

#endif // MESSAGE_LISTENER_H
