#include "event_machine.hpp"

EventMachine& EventMachine::get_machine() {
  static EventMachine machine;
  return machine;
}

int EventMachine::register_callback(CallbackFunc) {
  
}