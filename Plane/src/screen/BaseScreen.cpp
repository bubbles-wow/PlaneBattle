#pragma once
#include <screen/BaseScreen.h>
#include <util/Globals.h>

namespace Screen {
	BaseScreen::BaseScreen() : paused(true), ended(false) {
		// 注册监听器
		handlerId[0] = Util::listener.addHandler(
			[this](const ExMessage& msg) { mouseListener(msg); },
			Util::MessageType::MOUSE);
		handlerId[1] = Util::listener.addHandler(
			[this](const ExMessage& msg) { keyListener(msg); },
			Util::MessageType::KEY);
		drawing = false;
		main = std::thread(&BaseScreen::loop, this);
	}
	BaseScreen::~BaseScreen() {
		paused = false;
		ended = true;
		cv.notify_all();

		if (main.joinable()) {
			main.join();
		}
		Util::listener.removeHandler(handlerId[0]);
		Util::listener.removeHandler(handlerId[1]);
	}

	// 鼠标监听
	void BaseScreen::mouseListener(const ExMessage& msg) {
		if (paused || ended) {
			return;
		}
	}

	// 键盘监听
	void BaseScreen::keyListener(const ExMessage& msg) {
		if (paused || ended) {
			return;
		}
	}

	// 主循环
	void BaseScreen::loop() {
		while (true) {
			std::unique_lock<std::mutex> lock(mtx);
			cv.wait(lock, [this]() {return !paused || ended; });
			drawing = true;
			if (ended) {
				break;
			}

			// 执行任务
			try {
				work();
				draw();
			}
			catch (const std::exception& e) {
				if (!ended) {
					Util::log("An error occurred in loop()! " + std::string(e.what()), getClassName(), Util::LogLevel::ERR);
				}
				else {
					std::unique_lock<std::mutex> unlock(mtx);
					break;
				}
			}
			drawing = false;
			std::this_thread::sleep_for(std::chrono::milliseconds(10));
		}
	}

	// 初始化并展示界面
	void BaseScreen::start() {
		paused = false;
		ended = false;
		cv.notify_all();
		Util::log("Screen started.", getClassName());
	}

	// 暂停界面绘制
	void BaseScreen::pause() {
		paused = true;
		Util::log("Screen paused.", getClassName());
	}

	// 恢复界面绘制
	void BaseScreen::resume() {
		paused = false;
		cv.notify_all();
		Util::log("Screen resumed.", getClassName());
	}

	// 停止界面绘制
	void BaseScreen::stop() {
		paused = false;
		ended = true;
		cv.notify_all();

		if (main.joinable()) {
			main.join();
		}
		Util::log("Screen stopped.", getClassName());
	}
}