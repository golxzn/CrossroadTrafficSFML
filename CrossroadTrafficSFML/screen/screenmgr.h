#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "platform.h"
#include "GameConstants.h"
#include "singleton.h"
#include "eventhandler.h"

template<class T>
using GuardedObject = std::pair<std::mutex &, T>;

using DrawablePtr = std::shared_ptr<sf::Drawable>;
using GuardedScreen = GuardedObject<std::shared_ptr<sf::RenderWindow>>;
using GuardedTargets = GuardedObject<std::map<id_t, DrawablePtr> &>;

class ScreenManager : public singleton<ScreenManager>, public EventReceiver {
    SINGLETON_IMPL(ScreenManager);
public:
    ScreenManager() = default;
    void init(const sf::Vector2u &size, const sf::String &title = GameConstants::ScreenInfo::TITLE);
    void update(id_t id, DrawablePtr target);
    void removeTarget(id_t targetID);
    void start();
    void stop();
    void wait();

    GuardedScreen getScreen();
    GuardedTargets getTargets();

    bool isGamePaused() const;
private:
    std::mutex screenGuard;
    std::shared_ptr<sf::RenderWindow> screen;
    std::mutex targetsGuard;
    std::map<id_t, DrawablePtr> drawTargets;
    std::unique_ptr<std::thread> drawThread;
    std::unique_ptr<std::thread> eventThread;

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
    static void eventloop(ThreadHandler &handler);

    void onEvent(EventType type) override;
};

std::shared_ptr<ScreenManager> initScreenManager(const sf::Vector2u &size, const sf::String &title);
std::shared_ptr<ScreenManager> getScreenManager();

#endif // SCREENMANAGER_H
