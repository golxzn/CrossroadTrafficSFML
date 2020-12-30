#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "platform.h"
#include "singleton.h"

enum class EventType {
    Nothing,
    CloseApplication,
    PauseGame,
    ShowFuturePosition,
    MakeCarsFaster,
    MakeCarsSlower
};

struct EventReceiver {
    virtual void update(EventType event) = 0;
};

using EventReceiverPtr = std::shared_ptr<EventReceiver>;

class EventHandler : public singleton<EventHandler> {
    SINGLETON_IMPL(EventHandler);
public:
    EventHandler() = default;

    void pull(sf::Event &event);
    void subscribe(EventReceiverPtr receiver);

private:
    std::vector<EventReceiverPtr> receivers;
    static void updateAll(void *This, EventType event);
};

EventHandler &getEventHandler();

#endif // EVENTHANDLER_H
