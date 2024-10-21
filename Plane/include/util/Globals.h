#pragma once
#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>
#include <vector>

#include <easyx/easyx_own.h>		// 引入easyx库，包含子实现
#include <util/MessageListener.h> 	// 引入消息监听器
#include <util/MusicPlayer.h>		// 引入音乐播放器

#define COS_45 0.7071				// 45度角的余弦值
#define WM_GAME_OVER (WM_USER + 1)	// 自定义游戏结束消息类型

namespace Util
{
	/**
	 * @brief 游戏结束数据
	 * @param playerScore 玩家分数
	 * @param elapsedTime 游戏时长
	 */
	struct GameOverData
	{
		int playerScore; // 玩家分数
		int elapsedTime; // 游戏时长
	};

	/**
	 * @brief 日志级别
	 * @param INFO 信息
	 * @param WARNING 警告
	 * @param ERR 错误
	 */
	enum class LogLevel
	{
		INFO,
		WARNING,
		ERR
	};

	/**
	 * @brief 日志函数
	 * @param msg 日志信息
	 * @param className 类名
	 * @param level 日志级别
	 * @return int
	 */
	typedef int (*Log)(const std::string &, const std::string &, LogLevel);

	/**
	 * @brief 初始化日志流
	 * @param std::ostream & 输出流
	 * @return void
	 */
	typedef void (*InitLogStream)(std::ostream &);

	/**
	 * @brief 释放日志函数
	 * @return void
	 */
	typedef void (*ReleaseLogger)();

	typedef struct
	{
		int width;
		int height;
		float scale;
	} WINDOW_CONFIG;

	// 预设窗口配置
	static WINDOW_CONFIG preset = {
		480,
		640,
		1};

	extern ReleaseLogger releaseLogger;		// 释放日志函数
	extern Log logFunc;						// 日志函数
	extern InitLogStream initLogStreamFunc;	// 初始化日志流函数

	extern int debugFlag;					// 调试标志	0: 不显示调试信息	1: 显示调试信息
	extern HWND window;						// 窗口句柄
	extern bool isEnd;						// 游戏是否结束
	extern WINDOW_CONFIG windowConfig;		// 窗口配置

	extern IMAGE gameBg;					// 游戏背景
	extern IMAGE playerImg;					// 玩家飞机
	extern IMAGE ownBulletImg;				// 玩家子弹
	extern IMAGE enemyBulletImg;			// 敌人子弹
	extern IMAGE enemy1Img;					// 敌人1
	extern IMAGE enemy2Img;					// 敌人2

	extern MusicPlayer bgm;					// 背景音乐
	extern MusicPlayer shot;				// 射击音效
	extern MusicPlayer boom;				// 爆炸音效

	/**
	 * @brief 加载资源文件
	 * @return void
	 */
	void loadRes();

	/**
	 * @brief 加载自定义字体
	 * @param fontPath 字体路径
	 * @return bool
	 */
	bool loadCustomTTF(const std::wstring &fontPath);

	/**
	 * @brief 清除加载的字体
	 * @return void
	 */
	void clearFont();

	/**
	 * @brief 随机整数
	 * @param min 最小值
	 * @param max 最大值
	 * @return int
	 */
	int randomInt(int min, int max);

	/**
	 * @brief 叉乘，用于判断点c在向量ab的左侧还是右侧
	 * @param a 点a
	 * @param b 点b
	 * @param c 点c
	 * @return int
	 */
	int cross(const POINT &a, const POINT &b, const POINT &c);

	/**
	 * @brief 获取程序目录的绝对路径
	 * @return std::wstring
	 */
	std::wstring getExeDirectory();

	/**
	 * @brief 日志输出
	 * @param msg 日志信息
	 * @param className 类名
	 * @param level 日志级别
	 * @return void
	 */
	void log(const std::string &msg, const std::string &className, LogLevel level = LogLevel::INFO);
}

#endif // GLOBALS_H