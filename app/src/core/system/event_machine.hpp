#pragma once
#include <stdint.h>
#include <sys/_stdint.h>
#include <vector>
#include <unordered_map>
#include <functional>
#include <zephyr/kernel.h>

enum sys_event_e {
    EV_BACKLIGHT = 0,
    EV_SPEED,
    EV_GEAR,
    EV_SHIFT,
    EV_RPM_PCT,
    EV_RPM,
    EV_HANDBRAKE,
    EV_ESP,
    EV_ABS,
    EV_TURN,
    EV_BEAM,
    EV_FUEL_PCT,
    EV_FUEL_ALARM,
    EV_FUEL_VALUE,
    EV_COUNT
};

typedef struct {
    sys_event_e event_type;
    union {
        int32_t int_p;
        uint32_t uint_p;
        float float_p;
    } payload;
} sys_event_s;

typedef struct {
    sys_event_e event_type;
    int event_id;
} sys_event_token;

using CallbackFunc = void(*)(sys_event_s);

class EventMachine {
    public:
        static EventMachine& get_machine();
        sys_event_token register_callback(sys_event_e type, CallbackFunc callback);
        bool remove_callback(sys_event_token event_token);
        void call(sys_event_s event);
    private:
        EventMachine(){
            k_mutex_init(&mutex);
        };
        struct k_mutex mutex;
        int next_cb_id = 1;
        std::vector<std::unordered_map<int, CallbackFunc>> callbacks = 
            std::vector<std::unordered_map<int, CallbackFunc>>(EV_COUNT);
        
        std::vector<int> free_ids;
};