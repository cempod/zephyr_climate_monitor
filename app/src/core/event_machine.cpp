#include "event_machine.hpp"

EventMachine& EventMachine::get_machine() {
  static EventMachine machine;
  return machine;
}

int EventMachine::register_callback(sys_event_e type, CallbackFunc callback) {
  k_mutex_lock(&mutex, K_FOREVER);
  callbacks[type][next_cb_id] = callback;
  next_cb_id++;
  k_mutex_unlock(&mutex);

  return next_cb_id - 1;
}

bool EventMachine::remove_callback(sys_event_e type, int callback_id) {
  k_mutex_lock(&mutex, K_FOREVER);
  bool result = false;
  auto it = callbacks[type].find(callback_id);
  if (it != callbacks[type].end()) {
      callbacks[type].erase(it);
      result = true;
  }
  k_mutex_unlock(&mutex);

  return result;
}

void EventMachine::call(sys_event_s event) {
  k_mutex_lock(&mutex, K_FOREVER);
  bool result = false;
  for (auto& cb : callbacks[event.event_type]) {
    cb.second(event);
  }
  k_mutex_unlock(&mutex);
}