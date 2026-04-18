#include "event_machine.hpp"

EventMachine& EventMachine::get_machine() {
    static EventMachine machine;
    return machine;
}

sys_event_token EventMachine::register_callback(sys_event_e type, CallbackFunc callback) {
    k_mutex_lock(&mutex, K_FOREVER);
    int new_id;
    if (!free_ids.empty()) {
        new_id = free_ids.back();
        free_ids.pop_back();
    } else {
        new_id = next_cb_id++;
    }
    callbacks[type][new_id] = callback;
    k_mutex_unlock(&mutex);

    return {type, new_id};
}

bool EventMachine::remove_callback(sys_event_token event_token) {
    k_mutex_lock(&mutex, K_FOREVER);
    bool result = false;
    auto it = callbacks[event_token.event_type].find(event_token.event_id);
    if (it != callbacks[event_token.event_type].end()) {
        callbacks[event_token.event_type].erase(it);
        free_ids.push_back(event_token.event_id);
        result = true;
    }
    k_mutex_unlock(&mutex);

    return result;
}

void EventMachine::call(sys_event_s event) {
    k_mutex_lock(&mutex, K_FOREVER);
    for (auto& cb : callbacks[event.event_type]) {
        cb.second(event);
    }
    k_mutex_unlock(&mutex);
}