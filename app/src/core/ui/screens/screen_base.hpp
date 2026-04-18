#pragma once

#include <lvgl.h>
#include <vector>
#include "event_machine.hpp"

class ScreenBase {
    public:
        virtual void show() {
            if (callback_tokens_.empty()) {
                update_callbacks();
            }
            lv_scr_load(screen);
            on_show();
        }

        virtual void on_show() {}

        void detach() {
            for (sys_event_token event_token : callback_tokens_) {
                EventMachine::get_machine().remove_callback(event_token);
            }
            callback_tokens_.clear();
        }

        virtual void update() = 0;
        virtual void update_callbacks() = 0;

        ScreenBase(const ScreenBase&) = delete;
        ScreenBase& operator=(const ScreenBase&) = delete;
    protected:
        ScreenBase() = default;

        static void set_label_text(lv_obj_t * label, const char* msg, ...) {
            char str[50];
            va_list ap;
            va_start(ap, msg);
            vsnprintk(str, sizeof(str), msg, ap);
            va_end(ap);
            lv_label_set_text(label, str);
        }

        #define DECLARE_EVENT(name, sys_event_e, default_value) \
            int name##_ = default_value; \
            static inline void name##_callback(sys_event_s event) { \
                if (instance && event.event_type == sys_event_e) { \
                    instance->on##name(event.payload.int_p); \
                } \
            } \
            virtual void on##name(int value) { \
                name##_ = value; \
            }

        void register_callback(sys_event_e event_type, void (*callback)(sys_event_s)) {
            sys_event_token event_token = EventMachine::get_machine().register_callback(event_type, callback);
            callback_tokens_.push_back(event_token);
        }
        
        lv_obj_t * screen = nullptr;
        std::vector<sys_event_token> callback_tokens_;
};