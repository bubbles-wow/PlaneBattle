#pragma once
#include <string>

#include <screen/PauseScreen.h>
#include <util/Globals.h>

namespace Screen {
	PauseScreen::PauseScreen() : BaseScreen() {
		#pragma warning(disable: 4244)
		textSize = 20 * Util::windowConfig.scale;
		#pragma warning(default: 4244)
		settextstyle(textSize * 3, 0, L"站酷快乐体2016修订版");
		pauseHead = L"游戏暂停";
		headWidth = textwidth(pauseHead);
		headHeight = textheight(pauseHead);
		headX = (Util::windowConfig.width - headWidth) / 2;
		headY = (Util::windowConfig.height - headHeight) / 4;

		settextstyle(textSize, 0, L"站酷快乐体2016修订版");
		pauseTips = L"按下\"空格\"键或点击屏幕回到游戏";
		tipsWidth = textwidth(pauseTips);
		tipsHeight = textheight(pauseTips);
		tipsX = (Util::windowConfig.width - tipsWidth) / 2;
		tipsY = (Util::windowConfig.height - tipsHeight) * 4 / 5;
		gameScreen = nullptr;
	}

	PauseScreen::PauseScreen(BaseScreen* gameScreen) : PauseScreen() {
		this->gameScreen = gameScreen;
	}

	void PauseScreen::mouseListener(const ExMessage& msg) {
		if (paused || ended) {
			return;
		}
		switch (msg.message) {
		case WM_LBUTTONDOWN: {
			// 如果鼠标左键按下，继续游戏
			pause();
			if (gameScreen != nullptr) {
				gameScreen->resume();
			}
			break;
		}
		default:
			break;
		}
	}

	void PauseScreen::keyListener(const ExMessage & msg) {
		if (paused || ended) {
			return;
		}
		if (msg.message == WM_KEYDOWN) {
			switch (msg.vkcode) {
			case VK_SPACE: {
				// 如果空格键按下，继续游戏
				pause();
				if (gameScreen != nullptr) {
					gameScreen->resume();
				}
				break;
			}
			default:
				break;
			}
		}
	}

	void PauseScreen::draw() {
		// 等待游戏界面绘制完成，防止绘制冲突
		while (gameScreen->getDrawStatus()) {
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
			continue;
		}

		BeginBatchDraw();

		// 绘制标题
		settextcolor(WHITE);
		#pragma warning(disable: 4244)
		settextstyle(textSize * 3, 0, L"站酷快乐体2016修订版");
		#pragma warning(default: 4244)
		int textWidth = textwidth(pauseHead);
		int textHeight = textheight(pauseHead);
		int x = (Util::windowConfig.width - textWidth) / 2;
		int y = (Util::windowConfig.height - textHeight) / 4;
		outtextxy(x, y, pauseHead);

		// 绘制提示信息
		#pragma warning(disable: 4244)
		settextstyle(textSize, 0, L"站酷快乐体2016修订版");
		#pragma warning(default: 4244)
		textWidth = textwidth(pauseTips);
		textHeight = textheight(pauseTips);
		x = (Util::windowConfig.width - textWidth) / 2;
		y = (Util::windowConfig.height - textHeight) * 4 / 5;
		outtextxy(x, y, pauseTips);
		EndBatchDraw();
	}
}