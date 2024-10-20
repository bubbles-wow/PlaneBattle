#pragma once
#include <random>
#include <util/Globals.h>

namespace Util
{
	int debugFlag = 0;
	HWND window = nullptr;
	bool isEnd = false;
	Log logFunc = nullptr;
	initLogStream initLogStreamFunc = nullptr;

	WINDOW_CONFIG windowConfig = preset;

	IMAGE gameBg;
	IMAGE playerImg;
	IMAGE ownBulletImg;
	IMAGE enemyBulletImg;
	IMAGE enemy1Img;
	IMAGE enemy2Img;

	MusicPlayer bgm;
	MusicPlayer shot;
	MusicPlayer boom;

	std::mt19937 rng(std::random_device{}());	// 随机数生成器

	std::vector<std::wstring> fontPaths;		// 已加载的字体路径

	int randomInt(int min, int max)
	{
		std::uniform_int_distribution<int> dist(min, max);
		return dist(rng);
	}

	int cross(const POINT &a, const POINT &b, const POINT &c)
	{
		return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
	}

	std::wstring getExeDirectory()
	{
		wchar_t path[MAX_PATH];
		GetModuleFileName(NULL, path, MAX_PATH); // 获取程序路径
		std::wstring exePath(path);
		return exePath.substr(0, exePath.find_last_of(L"\\"));
	}

	void loadRes()
	{
		std::wstring baseDir = getExeDirectory() + L"\\res\\";
		// 加载音效资源
		bgm.load((baseDir + L"bgm.mp3").c_str());
		shot.load((baseDir + L"shot.mp3").c_str());
		boom.load((baseDir + L"boom.mp3").c_str());

		// 加载图片资源
#pragma warning(disable : 4244)
		loadimage(&gameBg, (baseDir + L"gameBg.png").c_str(), 480 * windowConfig.scale, 1280 * windowConfig.scale);
		loadimage(&playerImg, (baseDir + L"playerImg.png").c_str(), 50 * windowConfig.scale, 50 * windowConfig.scale);
		loadimage(&ownBulletImg, (baseDir + L"ownBullet.png").c_str(), 8 * windowConfig.scale, 12 * windowConfig.scale);
		loadimage(&enemyBulletImg, (baseDir + L"enemyBullet.png").c_str(), 8 * windowConfig.scale, 12 * windowConfig.scale);
		loadimage(&enemy1Img, (baseDir + L"enemy1.png").c_str(), 45 * windowConfig.scale, 30 * 5 * windowConfig.scale);
		loadimage(&enemy2Img, (baseDir + L"enemy2.png").c_str(), 45 * windowConfig.scale, 30 * 3 * windowConfig.scale);
#pragma warning(default : 4244)
		// 加载自定义字体
		loadCustomTTF((baseDir + L"GenKaimincho.ttf").c_str());
		loadCustomTTF((baseDir + L"站酷快乐体.ttf").c_str());
	}

	bool loadCustomTTF(const std::wstring &fontPath)
	{
		int res = AddFontResourceEx(fontPath.c_str(), FR_PRIVATE, NULL);
		if (res == 0)
		{
			Util::log("Failed to load custom TTF font.", "Util::LoadCustomTTF", LogLevel::ERR);
			return false;
		}
		fontPaths.push_back(fontPath);
		return true;
	}

	// 清理字体缓存并移除已加载的 TTF
	void clearFont()
	{
		// 移除临时加载的 TTF 字体
		for (const std::wstring fontPath : fontPaths)
		{
			RemoveFontResourceEx(fontPath.c_str(), FR_PRIVATE, NULL);
		}
	}

	void log(const std::string &msg, const std::string &className, LogLevel level)
	{
		if (logFunc != nullptr)
		{
			if (debugFlag == SHOWCONSOLE || level == LogLevel::ERR)
				logFunc(msg, className, level);
		}
	}
}
