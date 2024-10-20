#include <sstream>
#include <map>

#include <util/MessageListener.h>

namespace Util
{
	MessageListener listener;

	MessageListener::MessageListener() : isPause(false), handlerId(0) {}

	std::map<int, MessageHandler> *MessageListener::selectHandlers(MessageType type)
	{
		std::map<int, MessageHandler> *handlers = nullptr;
		switch (type)
		{
		case MessageType::MOUSE:
		{
			handlers = &mouseHandlers;
			break;
		}
		case MessageType::KEY:
		{
			handlers = &keyHandlers;
			break;
		}
		case MessageType::WINDOW:
		{
			handlers = &windowHandlers;
			break;
		}
		default:
			break;
		}
		return handlers;
	}

	void MessageListener::listener()
	{
		while (true)
		{
			// std::unique_lock<std::mutex> lock(mutex);
			// cv.wait(lock, [this]
			// 		{ return !isPause; });
			if (this->isEnd)
			{
				break;
			}
			if (isPause) {
				continue;
			}

			

			ExMessage msg;
			if (peekmessage(&msg, EX_KEY | EX_MOUSE))
			{
				onMessage(msg);
			}

			MSG winMsg;
			if (PeekMessage(&winMsg, window, WM_NULL, WM_WININICHANGE, PM_REMOVE))
			{
				ExMessage windowMsg;
				TranslateMessage(&winMsg);
				DispatchMessage(&winMsg);

				windowMsg.message = winMsg.message;
				windowMsg.wParam = winMsg.wParam;
				windowMsg.lParam = winMsg.lParam;
				onWindowMessage(windowMsg);

				if (winMsg.message == WM_QUIT || winMsg.message == WM_DESTROY)
				{
					break;
				}
			}
		}
	}

	int MessageListener::addHandler(const MessageHandler &handler, MessageType type)
	{
		std::lock_guard<std::mutex> lock(mutex);
		std::map<int, MessageHandler> *handlers = selectHandlers(type);
		int id = handlerId++;
		if (handler != nullptr)
		{
			(*handlers)[id] = handler;
			return id;
		}
		else
		{
			std::stringstream ss;
			ss << "Cannot add handler " << handler.target_type().name() << " to " << MessageTypeStr[static_cast<int>(type)];
			Util::log(ss.str(), "Util::MessageListener", LogLevel::ERR);
			return -1;
		}
	}

	void MessageListener::removeHandler(int id)
	{
		std::lock_guard<std::mutex> lock(mutex);
		if (mouseHandlers.erase(id) || keyHandlers.erase(id) || windowHandlers.erase(id))
		{
			return;
		}
		else
		{
			std::stringstream ss;
			ss << "Cannot remove handler with id " << id;
			Util::log(ss.str(), "Util::MessageListener", LogLevel::ERR);
		}
	}

	void MessageListener::onMessage(const ExMessage &msg)
	{
		// MOUSE
		if (msg.message >= 0x200 && msg.message < 0x20f)
		{
			// 过滤鼠标移动事件
			/*if (msg.message != WM_MOUSEMOVE) {
				std::stringstream ss;
				ss << "Mouse message: " << msg.message;
				log(ss.str(), "Util::MessageListener", LogLevel::INFO);
			}*/
			onMouseMessage(msg);
		}
		// KEY
		else if (msg.message == 0x100 || msg.message == 0x101)
		{
			/*std::stringstream ss;
			ss << "Key message: " << msg.message << ", key=" << msg.vkcode;
			log(ss.str(), "Util::MessageListener", LogLevel::INFO);*/
			onKeyMessage(msg);
		}
		// CHAR
		else if (msg.message == 0x102)
		{
			return;
		}
		// WINDOW
		else if (msg.message >= 0x0000 || msg.message <= 0x001A)
		{
			/*std::stringstream ss;
			ss << "Window message: " << msg.message;
			log(ss.str(), "Util::MessageListener", LogLevel::INFO);*/
			onWindowMessage(msg);
		}
		// OTHER
		else
		{
			return;
		}
	}

	void MessageListener::onKeyMessage(const ExMessage &msg)
	{
		for (const auto &[key, func] : keyHandlers)
		{
			if (func)
			{
				func(msg);
			}
		}
	}

	void MessageListener::onMouseMessage(const ExMessage &msg)
	{
		for (const auto &[key, func] : mouseHandlers)
		{
			if (func)
			{
				func(msg);
			}
		}
	}

	void MessageListener::onWindowMessage(const ExMessage &msg)
	{
		for (const auto &[key, func] : windowHandlers)
		{
			if (func)
			{
				func(msg);
			}
		}
	}
}