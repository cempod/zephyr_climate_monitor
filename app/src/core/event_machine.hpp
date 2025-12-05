#pragma once
#include <stdint.h>
#include <sys/_stdint.h>
#include <unordered_map>
#include <functional>

enum sys_event_e {
    EV_BACKLIGHT = 0
};

typedef struct {
    sys_event_e event_type;
    union payload {
        int32_t int_p;
        uint32_t uint_p;
        float float_p;
    };
} sys_event_s;

using CallbackFunc = void(*)(sys_event_s);

class EventMachine {
    public:
        static EventMachine& get_machine();
        int register_callback(CallbackFunc);
    private:
        EventMachine();
        std::unordered_map<int, CallbackFunc> backlight_callbacks;
};