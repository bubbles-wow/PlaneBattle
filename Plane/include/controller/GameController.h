#pragma once

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include <vector>

#include <controller/BulletController.h>
#include <controller/EnemyController.h>
#include <controller/PlayerController.h>

#define ENEMY_GENERATE_INTERVAL 2000
#define ENEMY_BULLET_GENERATE_INTERVAL 1000

namespace Controller {
    // 游戏实体管理器，控制游戏中的所有实体
    class GameController : BaseController {
    protected:
        BulletController bulletController;  // 子弹实体管理器
        EnemyController enemyController;    // 敌人实体管理器
        PlayerController playerController;  // 玩家实体管理器

		int playerHealth;                   // 玩家生命值
		int playerScore;                    // 玩家分数

		long long generateEnemyTimer;       // 上次生成敌人的时间
    public:
        GameController();

        /**
         * @brief 获取玩家生命值
         * @return int 玩家生命值
         */
        inline int getPlayerHealth() const {
            return playerHealth;
        }

        /**
         * @brief 获取玩家分数
         * @return int 玩家分数
         */
        inline int getPlayerScore() const {
            return playerScore;
        }

        // 设置玩家移动方向
        inline void setPlayerDirection(const float &dx, const float &dy) {
            playerController.setDirection(dx, dy);
        }

        inline std::pair<int, int> getPlayerPosition() {
            return playerController.getPlayer()->getPosition();
        }

        // 移动并绘制所有实体
        void moveAndDraw() override;

        // 检测敌人与玩家子弹的碰撞
        void checkEnemyCollide();

        // 检测玩家与敌人子弹的碰撞
        void checkPlayerCollide();

        // 生成敌人
        void generateEnemy();

        /**
         * @brief 生成玩家子弹
         * @param x x轴坐标
         * @param y y轴坐标
         */
        void generateOwnBullet(const int &x, const int &y);
        
        // 生成敌人子弹
        void generateEnemyBullet();
    };
}

#endif // GAME_CONTROLLER_H