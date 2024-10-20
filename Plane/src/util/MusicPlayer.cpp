#include <Windows.h>
#include <locale>
#include <codecvt>

#include <util/MusicPlayer.h>

namespace Util
{
    MusicPlayer::MusicPlayer()
    {
        FMOD::System_Create(&system);
        system->init(32, FMOD_INIT_NORMAL, 0);
    }

    MusicPlayer::MusicPlayer(const std::wstring &path) : MusicPlayer()
    {
        load(path);
    }

    MusicPlayer::~MusicPlayer()
    {
        sound->release();
        system->close();
        system->release();
    }

    void MusicPlayer::load(const std::wstring &path)
    {
        // 将宽字符串转换为std::string
        int size = WideCharToMultiByte(CP_UTF8, 0, path.c_str(), (int)path.size(), NULL, 0, NULL, NULL);
        std::string target(size, 0);
        WideCharToMultiByte(CP_UTF8, 0, path.c_str(), (int)path.size(), &target[0], size, NULL, NULL);
        this->path = target;
        system->createSound(this->path.c_str(), FMOD_DEFAULT, 0, &sound);
    }

    void MusicPlayer::play(bool loop)
    {
        this->loop = loop;
        system->playSound(sound, 0, false, &channel);
        if (loop)
        {
            channel->setMode(FMOD_LOOP_NORMAL);
        }
    }
}