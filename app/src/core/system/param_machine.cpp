#include "param_machine.hpp"

#include <zephyr/drivers/flash.h>
#include <zephyr/storage/flash_map.h>

#define NVS_PARTITION		storage_partition
#define NVS_PARTITION_DEVICE	PARTITION_DEVICE(NVS_PARTITION)
#define NVS_PARTITION_OFFSET	PARTITION_OFFSET(NVS_PARTITION)

ParamMachine& ParamMachine::get_machine() {
    static ParamMachine machine;
    return machine;
}

bool ParamMachine::init_storage() {
    fs.flash_device = NVS_PARTITION_DEVICE;
	if (!device_is_ready(fs.flash_device)) {
		return false;
	}
    struct flash_pages_info info;
    int rc = 0;
    fs.offset = NVS_PARTITION_OFFSET;
    rc = flash_get_page_info_by_offs(fs.flash_device, fs.offset, &info);
	if (rc) {
		return false;
	}
	fs.sector_size = info.size;
	fs.sector_count = 3U;

	rc = nvs_mount(&fs);
	if (rc) {
		return false;
	}
    return true;
}

void ParamMachine::load_param(uint16_t id, void* data, size_t size) {
    int rc = nvs_read(&fs, id, data, size);
        if (rc != (int)size) {
            save_param(id, data, size);
        }
}

void ParamMachine::save_param(uint16_t id, const void* data, size_t size) {
    nvs_write(&fs, id, data, size);
}