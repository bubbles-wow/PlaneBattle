#include <screen/StartScreen.h>
#include <screen/GameScreen.h>

namespace Screen
{

	StartScreen::StartScreen() : BaseScreen() {
		#pragma warning(disable: 4244)
		textSize = 30 * Util::windowConfig.scale;
		#pragma warning(default: 4244)

		settextstyle(textSize * 2, 0, L"站酷快乐体2016修订版");
		startHead = L"飞机大战";
		headWidth = textwidth(startHead);
		headHeight = textheight(startHead);
		headX = (Util::windowConfig.width - headWidth) / 2;
		headY = (Util::windowConfig.height - headHeight) / 4;

		settextstyle(textSize, 0, L"站酷快乐体2016修订版");
		startTips = L"按任意位置开始游戏";
		tipsWidth = textwidth(startTips);
		tipsHeight = textheight(startTips);
		tipsX = (Util::windowConfig.width - tipsWidth) / 2;
		tipsY = (Util::windowConfig.height - tipsHeight) * 4 / 5;
		gameScreen = nullptr;
	}

	StartScreen::~StartScreen()
	{
		if (gameScreen != nullptr)
			delete gameScreen;
	}
	
	void StartScreen::startNewGame() {
		pause();
		if (gameScreen != nullptr) {
			gameScreen->stop();
			delete gameScreen;
			gameScreen = new GameScreen();
			gameScreen->start();
		}
		else {
			gameScreen = new GameScreen();
			gameScreen->start();
		}
	}

	void StartScreen::start() {
		Util::bgm.play(true);
		BaseScreen::start();
	}

	void StartScreen::stop() {
		if (gameScreen != nullptr) {
			gameScreen->stop();
		}
		BaseScreen::stop();
	}

	void StartScreen::draw() {
		BeginBatchDraw();

		putimage(0, 0, &Util::gameBg);

		setbkmode(TRANSPARENT);
		// 画一个开始的界面
		settextcolor(YELLOW);
		settextstyle(textSize * 2, 0, L"站酷快乐体2016修订版");
		outtextxy(headX, headY, startHead);

		settextcolor(WHITE);
		settextstyle(textSize, 0, L"站酷快乐体2016修订版");
		outtextxy(tipsX, tipsY, startTips);
		EndBatchDraw();
	}

	void StartScreen::mouseListener(const ExMessage& msg) {
		if (paused || ended) {
			return;
		}
		switch (msg.message) {
		case WM_LBUTTONDOWN: {
			// 如果鼠标左键按下，开始游戏
			startNewGame();
			break;
		}
		default:
			break;
		}
	}

	void StartScreen::keyListener(const ExMessage& msg) {
		if (paused || ended) {
			return;
		}
		//if (msg.message == WM_KEYDOWN) {
		//	switch (msg.vkcode) {
		//	case VK_SPACE: {
		//		// 如果空格键按下，开始游戏
		//		startNewGame();
		//		break;
		//	}
		//	default:
		//		break;
		//	}
		//}
	}
}