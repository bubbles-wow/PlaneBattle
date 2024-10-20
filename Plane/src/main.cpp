#pragma once
#include <iostream>
#include <windows.h>
#include <commctrl.h>
#include <imm.h> // 包含输入法相关的头文件

#include <screen/StartScreen.h>
#include <util/Globals.h>
#include <util/MessageListener.h>

#pragma comment(lib, "Imm32.lib") // 显式链接 Imm32.lib 库
#pragma comment(lib, "Winmm.lib") // 显式链接 Winmm.lib 库

static HIMC himc;
static WNDPROC originalWndProc = nullptr;
static Screen::StartScreen *startScreen = nullptr;

// 禁用输入法
static inline void disableIme(HWND hwnd)
{
	himc = ImmAssociateContext(hwnd, NULL);
}

// 启用输入法
static inline void enableIme(HWND hwnd)
{
	ImmAssociateContext(hwnd, himc);
}

// 窗口事件处理
static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	// 窗口关闭事件
	case WM_CLOSE:
	{
		Util::log("Close window message received.", "Main", Util::LogLevel::INFO);
		if (startScreen != nullptr)
		{
			startScreen->pauseGameScreen();
		}
		// 播放系统声音
		if (!PlaySound(TEXT("SystemAsterisk"), NULL, SND_ALIAS | SND_ASYNC))
		{
			Util::log("Failed to play system sound.", "Main", Util::LogLevel::ERR);
		}
		// 弹出提示框，询问是否关闭窗口
		int result = MessageBox(hwnd, L"是否退出游戏？", L"退出游戏", MB_YESNO | MB_ICONQUESTION);
		if (result == IDYES)
		{
			DestroyWindow(hwnd); // 销毁窗口
			PostQuitMessage(0);
		}
		else
		{
			if (startScreen != nullptr)
			{
				startScreen->resumeGameScreen();
			}
		}
		return 0;
	}
	// 游戏结束事件
	case WM_GAME_OVER:
	{
		Util::GameOverData *data = reinterpret_cast<Util::GameOverData *>(wParam);

		if (data != nullptr)
		{
			// 播放系统声音
			if (!PlaySound(TEXT("SystemAsterisk"), NULL, SND_ALIAS | SND_ASYNC))
			{
				Util::log("Failed to play system sound.", "Main", Util::LogLevel::ERR);
			}
			std::wstring content = L"你的得分: " + std::to_wstring(data->playerScore) +
								   L"\n存活时间: " + std::to_wstring(data->elapsedTime) + L" 秒\n\n" +
								   L"点击“是”重新开始游戏，点击“否”返回到标题。";
			int result = MessageBox(hwnd, content.c_str(), L"游戏结束", MB_YESNO | MB_ICONQUESTION);
			if (result == IDYES)
			{
				startScreen->startNewGame();
			}
			else
			{
				startScreen->start();
			}
		}
		return 0;
	}
	default:
		// 转发其他事件
		return CallWindowProc(originalWndProc, hwnd, msg, wParam, lParam);
	}
}

// 加载Logger.dll
static void loadLogger()
{
	HMODULE hModule = LoadLibrary(L"Logger.dll");
	if (hModule == nullptr)
	{
		Util::logFunc = nullptr;
		std::cout << "Error: Cannot load Logger.dll" << std::endl;
		return;
	}
	Util::logFunc = (Util::Log)GetProcAddress(hModule, "logFunc");
	if (Util::logFunc == nullptr)
	{
		std::cout << "Error: Cannot load log function in Logger.dll" << std::endl;
		return;
	}
	Util::initLogStreamFunc = (Util::initLogStream)GetProcAddress(hModule, "initLogStream");
	if (Util::initLogStreamFunc == nullptr)
	{
		std::cout << "Error: Cannot load initLogStream function in Logger.dll" << std::endl;
		return;
	}
}

// 设置窗口配置
static void setupWindowConfig()
{
	// 获取屏幕分辨率
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	float scale;
	int type;

	// 计算缩放比例
	if (screenWidth >= screenHeight)
	{
		scale = float(screenHeight - 100) / Util::preset.height;
	}
	else
	{
		scale = float(screenWidth - 100) / Util::preset.width;
	}

	// 设置窗口配置
#pragma warning(disable : 4244)
	type = (scale - 1) / 0.25;
	if (type >= 0)
	{
		Util::windowConfig.scale = 1 + type * 0.25;
	}
	Util::windowConfig.width = Util::preset.width * Util::windowConfig.scale;
	Util::windowConfig.height = Util::preset.height * Util::windowConfig.scale;
#pragma warning(default : 4244)

	Util::log(
		"Set window config. [width=" + std::to_string(Util::windowConfig.width) +
			", height=" + std::to_string(Util::windowConfig.height) +
			", scale=" + std::to_string(Util::windowConfig.scale) + "]",
		"Main");
}

// 主函数，由于用WinMain不能弹出控制台，所以用main函数
int main(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// 设置DPI感知，使得高DPI上不会模糊显示
	SetProcessDpiAwarenessContext(DPI_AWARENESS_CONTEXT_PER_MONITOR_AWARE_V2);
	// 加载Logger.dll
	loadLogger();
	// 解析命令行参数
	int argc;
	LPWSTR *argv = CommandLineToArgvW(GetCommandLineW(), &argc);
	if (argv == nullptr)
	{
		MessageBox(nullptr, L"无法解析命令行参数！", L"错误", MB_ICONERROR);
	}
	else
	{
		// 是否显示控制台
		for (int i = 1; i < argc; i++)
		{
			std::wstring arg(argv[i]);
			if (arg == L"--debug-mode")
			{
				Util::debugFlag = SHOWCONSOLE;
				AllocConsole();
			}
		}
	}
	if (Util::debugFlag != SHOWCONSOLE)
	{
		FreeConsole();
	}

	// 初始化窗口
	setupWindowConfig();
	Util::loadRes();
	Util::window = initgraph(Util::windowConfig.width, Util::windowConfig.height, NULL);
	if (Util::window == nullptr)
	{
		return -1;
	}

	// 设置窗口事件处理函数
	originalWndProc = (WNDPROC)SetWindowLongPtr(Util::window, GWLP_WNDPROC, (LONG_PTR)WndProc);
	// 关闭输入法
	disableIme(Util::window);
	// 开启监听
	Util::listener.start();

	// 进入游戏
	startScreen = new Screen::StartScreen();
	startScreen->start();
	// 检查窗口是否已关闭
	while (1)
	{
		if (!IsWindow(Util::window))
		{
			Util::log("Main window closed.", "Main");
			Util::isEnd = true;
			startScreen->stop();
			Util::listener.stop();
			break;
		}
		else
		{
			if (Util::isEnd)
			{
				break;
			}
		}
		Sleep(1000);
	}
	// 关闭窗口
	// closegraph();
	startScreen->stop();
	delete startScreen;
	Util::log("Process ended.", "Main");
	return 0;
}
