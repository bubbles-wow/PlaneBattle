#include <sys/timeb.h>

#include <controller/GameController.h>

namespace Controller
{
    GameController::GameController() : playerScore(0), generateEnemyTimer(0)
    {
        playerHealth = playerController.getPlayer()->getHealth();
        playerController.setPosition(Util::windowConfig.width / 2, Util::windowConfig.height / 2);
    }

    void GameController::moveAndDraw()
    {
        bulletController.moveAndDraw();
        enemyController.moveAndDraw();
        playerController.moveAndDraw();
    }

    void GameController::checkEnemyCollide()
    {
        std::vector<std::shared_ptr<Entity::Plane>> enemyPtrs = enemyController.getEnemyList();
        std::vector<std::shared_ptr<Entity::OwnBullet>> ownBullets = bulletController.getOwnBulletList();
        for (std::shared_ptr<Entity::Plane> &enemy : enemyPtrs)
        {
            for (std::shared_ptr<Entity::OwnBullet> &bullet : ownBullets)
            {
                if (enemy->isCollide(bullet->getX(), bullet->getY()))
                {
                    Util::log(
                        "Enemy hit. bullet[x=" + std::to_string(bullet->getX()) +
                            ", y=" + std::to_string(bullet->getY()) +
                            "], enemy[health=" + std::to_string(enemy->getHealth()),
                        getClassName(), Util::LogLevel::INFO);
                    enemy->changeHealth(-10);
                    // 移出画布
                    bullet->setPosition(-1, -1);
                    if (enemy->getHealth() <= 0)
                    {
                        playerScore += 10;
                    }
                    Util::boom.play();
                }
            }
        }
    }

    void GameController::checkPlayerCollide()
    {
        std::vector<std::shared_ptr<Entity::EnemyBullet>> enemyBullets = bulletController.getEnemyBulletList();
        std::shared_ptr<Entity::Player> player = playerController.getPlayer();
        for (std::shared_ptr<Entity::EnemyBullet> &bullet : enemyBullets)
        {
            if (player->isCollide(bullet->getX(), bullet->getY()))
            {
                Util::log(
                    "Player hit. bullet[x=" + std::to_string(bullet->getX()) +
                        ", y=" + std::to_string(bullet->getY()) +
                        "], enemy[health=" + std::to_string(player->getHealth()),
                    getClassName(), Util::LogLevel::INFO);
                player->changeHealth(-10);
                playerHealth = player->getHealth();
                // 移出画布
                bullet->setPosition(-1, Util::windowConfig.height + 100);
                Util::boom.play();
            }
        }
    }

    void GameController::generateEnemy()
    {
        timeb n;
        ftime(&n);
        long long now = n.time * 1000 + n.millitm;
        std::vector<std::shared_ptr<Entity::Plane>> &tmp = enemyController.getEnemyList();
        if (tmp.size() < 10)
        {
            if (now - generateEnemyTimer > ENEMY_GENERATE_INTERVAL)
            {
                int x = Util::randomInt(0, Util::windowConfig.width);
                if (Util::randomInt(0, 1) == 0)
                {
                    enemyController.addEnemy(std::make_unique<Entity::Enemy1>(x, 1));
                }
                else
                {
                    enemyController.addEnemy(std::make_unique<Entity::Enemy2>(x, 1));
                }
                generateEnemyTimer = now;
            }
        }
    }

    void GameController::generateOwnBullet(const int &x, const int &y)
    {
        bulletController.addBullet(
            std::make_unique<Entity::OwnBullet>(x, y),
            Entity::BulletType::OWN);
        Util::shot.play();
    }

    void GameController::generateEnemyBullet()
    {
        timeb n;
        ftime(&n);
        long long now = n.time * 1000 + n.millitm;
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        std::vector<std::shared_ptr<Entity::Plane>> &tmp = enemyController.getEnemyList();
        if (!tmp.empty())
        {
            for (std::shared_ptr<Entity::Plane> &enemy : tmp)
            {
                if (now - enemy->getLastShotTime() > ENEMY_BULLET_GENERATE_INTERVAL)
                {
                    int x = enemy->getX(), y = enemy->getY();
                    if (enemy->getFlag() == 10)
                    {
                        int width = enemy->getWidth();
                        bulletController.addBullet(
                            std::make_unique<Entity::EnemyBullet>(x - width / 4, y),
                            Entity::BulletType::ENEMY);
                        bulletController.addBullet(
                            std::make_unique<Entity::EnemyBullet>(x + width / 4, y),
                            Entity::BulletType::ENEMY);
                    }
                    else if (enemy->getFlag() == 11)
                    {
                        bulletController.addBullet(
                            std::make_unique<Entity::EnemyBullet>(x, y),
                            Entity::BulletType::ENEMY);
                    }
                    enemy->setLastShotTime(now);
                    Util::shot.play();
                }
            }
        }
    }
}