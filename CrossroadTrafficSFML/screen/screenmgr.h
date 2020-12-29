#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include "platform.h"

using DrawablePtr = std::shared_ptr<std::pair<id_t, sf::Drawable>>;

class ScreenManager {
public:
    explicit ScreenManager(const sf::Vector2u &size, const sf::String &title);
    void addTarget(DrawablePtr target);
    void removeTarget(id_t targetID);
    void start();
    void end();

    std::mutex &getScreenGuard();

private:
    std::mutex screenGuard;
    sf::RenderWindow screen;
    std::vector<DrawablePtr> drawTargets;
    std::unique_ptr<std::thread> drawThread;

    std::vector<DrawablePtr>::const_iterator find(id_t id) const;

    struct ThreadHandler {
        ThreadHandler();
        void rmTarget(std::vector<DrawablePtr>::const_iterator rmTarget);
        void update(DrawablePtr drawTarget);
        void start();
        void stop();
        bool isRunning() const;
        std::vector<DrawablePtr> getTargets() const;

    private:
        bool running;
        std::mutex targetsGuard;
        std::vector<DrawablePtr> targets;
    } handler;

    static void drawloop(ThreadHandler &handler);
};

#endif // SCREENMANAGER_H
