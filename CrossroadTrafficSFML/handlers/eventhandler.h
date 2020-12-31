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
    MakeCarsSlower,
    MoreCars,
    LessCars,

    Update,
};

struct EventReceiver {
    virtual ~EventReceiver() {}
    virtual void onEvent(EventType event) = 0;
};

using EventReceiverPtr = std::shared_ptr<EventReceiver>;

class EventHandler : public singleton<EventHandler> {
    SINGLETON_IMPL(EventHandler);
public:
    EventHandler() = default;

    void pull(EventType event);
    void pull(sf::Event &event);
    void subscribe(EventReceiverPtr receiver);

private:
    std::vector<EventReceiverPtr> receivers;
    static void notifyAll(void *This, EventType event);
};

EventHandler &getEventHandler();

#endif // EVENTHANDLER_H
