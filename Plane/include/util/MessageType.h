#pragma once
#ifndef MESSAGE_TYPE_H
#define MESSAGE_TYPE_H

namespace Util
{
	enum class MessageType
	{
		// 鼠标消息
		MOUSE,
		// 键盘消息
		KEY,
		// 窗口消息
		WINDOW,
		// 其他消息
		OTHER
	};

	static const char* MessageTypeStr[] = {
		"MOUSE",
		"KEY",
		"WINDOW",
		"OTHER"
	};
}

#endif // MESSAGE_TYPE_H
