#include "eventhandler.h"

EventHandler &getEventHandler() {
    return EventHandler::instance();
}

void EventHandler::pull(EventType event) {
    std::thread(&EventHandler::notifyAll, this, event).detach();
}

void EventHandler::pull(sf::Event &event) {
    EventType eventType = EventType::Nothing;

    if(event.type == sf::Event::Closed) {
        eventType = EventType::CloseApplication;
    }

    if(event.type == sf::Event::KeyPressed) {
        switch (event.key.code) {
            case sf::Keyboard::Escape:
                eventType = EventType::PauseGame;
                break;
            case sf::Keyboard::V:
                eventType = EventType::ShowFuturePosition;
                break;
            case sf::Keyboard::Up:
                eventType = EventType::MakeCarsFaster;
                 break;
            case sf::Keyboard::Down:
                eventType = EventType::MakeCarsSlower;
                 break;
            case sf::Keyboard::Add:
                eventType = EventType::MoreCars;
                break;
            case sf::Keyboard::Subtract:
                eventType = EventType::LessCars;
                break;
            default: break;
        }
    }

    std::thread(&EventHandler::notifyAll, this, eventType).detach();
}

void EventHandler::subscribe(EventReceiverPtr receiver) {
    receivers.emplace_back(receiver);
}

void EventHandler::notifyAll(void *This, EventType event) {
    if(event == EventType::Nothing || nullptr == This) {
        return;
    }
    EventHandler *me = static_cast<EventHandler *>(This);
    for(auto receiver : me->receivers) {
        receiver->onEvent(event);
    }
}

