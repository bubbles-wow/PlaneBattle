#pragma once
#ifndef MUSIC_PLAYER_H
#define MUSIC_PLAYER_H

#include <string>

#include <fmod.hpp>

namespace Util
{
    /**
     * @brief 音乐播放器
     */
    class MusicPlayer
    {
    private:
        FMOD::System *system;
        FMOD::Sound *sound;
        FMOD::Channel *channel;
        
        std::string path;       // 音乐文件路径
        bool loop;              // 是否循环播放
    public:
        /**
         * @brief 构造函数
         */
        MusicPlayer();

        /**
         * @brief 构造函数
         * @param path 音乐文件路径
         */
        MusicPlayer(const std::wstring &path);

        /**
         * @brief 析构函数
         */
        ~MusicPlayer();

        /**
         * @brief 加载音乐
         * @param path 音乐文件路径
         * @return void
         */
        void load(const std::wstring &path);

        /**
         * @brief 播放音乐
         * @param loop 是否循环播放
         * @return void
         */
        void play(bool loop = false);

        /**
         * @brief 暂停音乐
         * @return void
         */
        inline void pause() {
            channel->setPaused(true);
        };

        /**
         * @brief 恢复音乐
         * @return void
         */
        inline void resume() {
            channel->setPaused(false);
            if (loop) {
                channel->setMode(FMOD_LOOP_NORMAL);
            }
        };

        /**
         * @brief 停止音乐
         * @return void
         */
        inline void stop() {
            channel->stop();
        };
    };
}

#endif // MUSIC_PLAYER_H