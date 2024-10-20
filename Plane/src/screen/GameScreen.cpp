#pragma once
#include <sys/timeb.h>
#include <sstream>
#include <cmath>

#include <screen/GameScreen.h>
#include <screen/PauseScreen.h>
#include <util/Globals.h>

namespace Screen
{
	GameScreen::GameScreen() : BaseScreen()
	{
		gameController = new Controller::GameController();
		pauseScreen = new PauseScreen((BaseScreen *)this);
		pauseScreen->pause();

		bgWidth = Util::gameBg.getwidth();
		bgHeight = Util::gameBg.getheight();
		bgX = (Util::windowConfig.width - bgWidth) / 2;
		bgY = 0;

		barWidth = Util::windowConfig.width;
#pragma warning(disable : 4244)
		barHeight = 30 * Util::windowConfig.scale;

		textSize = 20 * Util::windowConfig.scale;
		borderWidth = 3 * Util::windowConfig.scale;
#pragma warning(default : 4244)

		settextstyle(textSize, 0, L"GenKaimincho");
		healthHead = L"血量：";
		healthHeadWidth = textwidth(healthHead);
		healthHeadHeight = textheight(healthHead);
		healthHeadX = (barWidth - healthHeadWidth) / 2;
		healthHeadY = borderWidth;

		settextstyle(textSize * 3, 0, L"GenKaimincho");
		scoreHeadWidth = textwidth(L"0");
		scoreHeadHeight = textheight(L"0");
		scoreHeadX = (barWidth - scoreHeadWidth) / 2;
		scoreHeadY = barHeight + borderWidth;

		taskIndex = 0;
		initTaskList();

		timeb n;
		ftime(&n);
		startTime = n.time;
	}

	GameScreen::GameScreen(BaseScreen *startScreen) : GameScreen()
	{
		this->startScreen = startScreen;
	}

	void GameScreen::initTaskList()
	{
		// 随机生成敌机
		taskList.push_back([this]
		{ 
			gameController->generateEnemy();
			taskIndex++; 
		});
		// // 敌机发射子弹
		taskList.push_back([this]
		{
			gameController->generateEnemyBullet();
			taskIndex++; 
		});
		// 敌人碰撞检测
		taskList.push_back([this]
		{ 
			gameController->checkEnemyCollide();
			taskIndex++; 
		});
		// 玩家碰撞检测
		taskList.push_back([this]
		{ 
			gameController->checkPlayerCollide();
			taskIndex++;
		});
		// 游戏结束判断
		taskList.push_back([this]
		{ 
			if (gameController->getPlayerHealth() <= 0)
			{
				Util::boom.play();
				gameOver();
			}
			taskIndex = 0; 
		});
	}

	void GameScreen::draw()
	{
		BeginBatchDraw();

		// 绘制背景
		putimage(bgX, bgY - bgHeight, &Util::gameBg);
		putimage(bgX, bgY, &Util::gameBg);
		// 图片滚动
#pragma warning(disable : 4244)
		bgY += 1 * Util::windowConfig.scale;
#pragma warning(default : 4244)
		if (bgY > bgHeight)
		{
			bgY = 0;
		}

		// 绘制实体
		gameController->moveAndDraw();

		// 绘制玩家生命条
		setlinestyle(PS_SOLID, borderWidth);
		setlinecolor(WHITE);
		rectangle(0, 0, barWidth, barHeight);
		setfillcolor(YELLOW);
		solidrectangle(borderWidth, borderWidth, barWidth - borderWidth * 2, barHeight - borderWidth * 2);
		setfillcolor(RED);
		solidrectangle(borderWidth, borderWidth, barWidth * gameController->getPlayerHealth() / 100 - 6, barHeight - 6);

		// 绘制玩家生命信息
		setbkmode(TRANSPARENT);
		settextcolor(GREEN);
		settextstyle(textSize, 0, L"GenKaimincho");
		std::wstringstream ss;
		std::wstring healthStr = healthHead + std::to_wstring(gameController->getPlayerHealth());
		outtextxy(healthHeadX, healthHeadY, healthStr.c_str());

		// 绘制分数
		settextcolor(YELLOW);
		settextstyle(textSize * 3, 0, L"GenKaimincho");
		std::wstring scoreStr = std::to_wstring(gameController->getPlayerScore());
		outtextxy(scoreHeadX, scoreHeadY, scoreStr.c_str());

		EndBatchDraw();
	}

	void GameScreen::startNewGame()
	{
		delete gameController;
		gameController = new Controller::GameController();
	}

	void GameScreen::gameOver()
	{
		Util::bgm.stop();
		paused = false;
		ended = true;
		Util::log("Game over.", getClassName());
		timeb n;
		ftime(&n);

		data.playerScore = gameController->getPlayerScore();
#pragma warning(disable : 4244)
		data.elapsedTime = n.time - startTime;
#pragma warning(default : 4244)

		PostMessage(Util::window, WM_GAME_OVER, reinterpret_cast<WPARAM>(&data), 0);
	}

#pragma warning(disable : 4305)
	void GameScreen::keyListener()
	{
		if (!ended)
		{
			if (GetAsyncKeyState('W') & 0x8000)
			{
				if (GetAsyncKeyState('A') & 0x8000)
				{
					gameController->setPlayerDirection(-COS_45, -COS_45);
				}
				else if (GetAsyncKeyState('D') & 0x8000)
				{
					gameController->setPlayerDirection(COS_45, -COS_45);
				}
				else
				{
					gameController->setPlayerDirection(0, -1);
				}
			}
			else if (GetAsyncKeyState('S') & 0x8000)
			{
				if (GetAsyncKeyState('A') & 0x8000)
				{
					gameController->setPlayerDirection(-COS_45, COS_45);
				}
				else if (GetAsyncKeyState('D') & 0x8000)
				{
					gameController->setPlayerDirection(COS_45, COS_45);
				}
				else
				{
					gameController->setPlayerDirection(0, 1);
				}
			}
			else if (GetAsyncKeyState('A') & 0x8000)
			{
				if (GetAsyncKeyState('W') & 0x8000)
				{
					gameController->setPlayerDirection(-COS_45, -COS_45);
				}
				else if (GetAsyncKeyState('S') & 0x8000)
				{
					gameController->setPlayerDirection(-COS_45, COS_45);
				}
				else
				{
					gameController->setPlayerDirection(-1, 0);
				}
			}
			else if (GetAsyncKeyState('D') & 0x8000)
			{
				if (GetAsyncKeyState('W') & 0x8000)
				{
					gameController->setPlayerDirection(COS_45, -COS_45);
				}
				else if (GetAsyncKeyState('S') & 0x8000)
				{
					gameController->setPlayerDirection(COS_45, COS_45);
				}
				else
				{
					gameController->setPlayerDirection(1, 0);
				}
			}
			else
			{
				gameController->setPlayerDirection(0, 0);
			}
		}
	}
#pragma warning(default : 4305)

#pragma warning(disable : 4305)
	void GameScreen::keyListener(const ExMessage &msg)
	{
		if (paused || ended)
		{
			return;
		}
		if (msg.message == WM_KEYDOWN)
		{
			switch (msg.vkcode)
			{
			case VK_ESCAPE:
			{
				pause();
				pauseScreen->resume();
				break;
			}
			case 'W':
			{
				if (GetAsyncKeyState('A') & 0x8000)
				{
					gameController->setPlayerDirection(-COS_45, -COS_45);
				}
				else if (GetAsyncKeyState('D') & 0x8000)
				{
					gameController->setPlayerDirection(COS_45, -COS_45);
				}
				else
				{
					gameController->setPlayerDirection(0, -1);
				}
				break;
			}
			case 'S':
			{
				if (GetAsyncKeyState('A') & 0x8000)
				{
					gameController->setPlayerDirection(-COS_45, COS_45);
				}
				else if (GetAsyncKeyState('D') & 0x8000)
				{
					gameController->setPlayerDirection(COS_45, COS_45);
				}
				else
				{
					gameController->setPlayerDirection(0, 1);
				}
				break;
			}
			case 'A':
			{
				if (GetAsyncKeyState('W') & 0x8000)
				{
					gameController->setPlayerDirection(-COS_45, -COS_45);
				}
				else if (GetAsyncKeyState('S') & 0x8000)
				{
					gameController->setPlayerDirection(-COS_45, COS_45);
				}
				else
				{
					gameController->setPlayerDirection(-1, 0);
				}
				break;
			}
			case 'D':
			{
				if (GetAsyncKeyState('W') & 0x8000)
				{
					gameController->setPlayerDirection(COS_45, -COS_45);
				}
				else if (GetAsyncKeyState('S') & 0x8000)
				{
					gameController->setPlayerDirection(COS_45, COS_45);
				}
				else
				{
					gameController->setPlayerDirection(1, 0);
				}
				break;
			}
			default:
			{
				keyListener();
				break;
			}
			}
		}
		else if (msg.message == WM_KEYUP)
		{
			keyListener();
		}
	}
#pragma warning(default : 4305)

	void GameScreen::mouseListener(const ExMessage &msg)
	{
		if (paused || ended)
		{
			return;
		}
		switch (msg.message)
		{
		case WM_LBUTTONDOWN:
		{
			std::pair<int, int> playerPosition = gameController->getPlayerPosition();
			gameController->generateOwnBullet(playerPosition.first, playerPosition.second);
			break;
		}
		default:
			break;
		}
	}

	void GameScreen::start()
	{
		timeb n;
		ftime(&n);
		startTime = n.time;

		pauseScreen->pause();
		BaseScreen::start();
	}

	void GameScreen::pause()
	{
		Util::bgm.pause();
		pauseScreen->resume();
		BaseScreen::pause();
	}

	void GameScreen::resume()
	{
		Util::bgm.resume();
		pauseScreen->pause();
		BaseScreen::resume();
	}

	void GameScreen::stop()
	{
		pauseScreen->stop();
		BaseScreen::stop();
	}
}