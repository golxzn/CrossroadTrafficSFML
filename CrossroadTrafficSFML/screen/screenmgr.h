#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "platform.h"
#include "GameConstants.h"
#include "singleton.h"
#include "eventhandler.h"

template<class T>
using GuardedObject = std::pair<std::mutex &, T&>;

using DrawablePtr = std::shared_ptr<sf::Drawable>;
using GuardedScreen = GuardedObject<sf::RenderWindow &>;
using GuardedTargets = GuardedObject<std::map<id_t, DrawablePtr>>;

class ScreenManager : public singleton<ScreenManager>, public EventReceiver {
    SINGLETON_IMPL(ScreenManager);
public:
    ScreenManager() = default;
    void init(const sf::Vector2u &size, const sf::String &title);
    void update(id_t id, DrawablePtr target);
    void removeTarget(id_t targetID);
    void start();
    void end();

    GuardedScreen getScreen();
    GuardedTargets getTargets();

private:
    std::mutex screenGuard;
    sf::RenderWindow screen;
    std::mutex targetsGuard;
    std::map<id_t, DrawablePtr> drawTargets;
    std::unique_ptr<std::thread> drawThread;

    std::map<id_t, DrawablePtr>::const_iterator find(id_t id) const;

    struct ThreadHandler {
        void start();
        void stop();
        void pause();
        void resume();
        bool isRunning() const;
        bool isPaused() const;

    private:
        std::atomic<bool> running{ false };
        std::atomic<bool> paused{ false };
    } handler;

    static void drawloop(ThreadHandler &handler);

    void update(EventType type) override;
};

ScreenManager &initScreenManager(const sf::Vector2u &size, const sf::String &title);
ScreenManager &getScreenManager();

#endif // SCREENMANAGER_H
