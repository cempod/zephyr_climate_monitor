#pragma once
#include <stdint.h>
#include <functional>
#include <sys/_stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/kvss/nvs.h>

enum sys_param_e {
    PR_BRIGHTNESS = 0,
    PR_COUNT
};

typedef struct {
    sys_param_e param_type;
    union {
        int32_t int_p;
        uint32_t uint_p;
        float float_p;
    } payload;
} sys_param_s;

class ParamMachine {
    public:
        static ParamMachine& get_machine();

        /*PARAM MACRO*/
        #define DECLARE_PARAM(type, name, default_val) \
            private: \
                type p_##name = default_val; \
                uint16_t p_##name##_id = get_next_id(); \
                bool p_##name##_loaded = false; \
            public: \
                type get_##name() { \
                    k_mutex_lock(&p_mutex, K_FOREVER); \
                    if (!p_##name##_loaded) { \
                        load_param(p_##name##_id, &p_##name, sizeof(type)); \
                        p_##name##_loaded = true; \
                    } \
                    type val = p_##name; \
                    k_mutex_unlock(&p_mutex); \
                    return val; \
                } \
                void set_##name(type val) { \
                    k_mutex_lock(&p_mutex, K_FOREVER); \
                    p_##name = val; \
                    p_##name##_loaded = true; \
                    save_param(p_##name##_id, &p_##name, sizeof(type)); \
                    k_mutex_unlock(&p_mutex); \
                }
        /*PARAM MACRO*/

        DECLARE_PARAM(int32_t, brightness, 100);
        DECLARE_PARAM(uint32_t, startup_logo, 1);
    private:
        ParamMachine() {
            k_mutex_init(&p_mutex);
            init_complete = init_storage();
        };

        static uint16_t get_next_id() {
            static uint16_t counter = 0;
            return counter++;
        }

        bool init_storage();
        void load_param(uint16_t id, void* data, size_t size);
        void save_param(uint16_t id, const void* data, size_t size);
        
        struct k_mutex p_mutex;
        struct nvs_fs fs;
        bool init_complete = false;
};