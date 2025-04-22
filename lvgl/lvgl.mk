LVGL_PATH ?= ${shell pwd}/lvgl

LVGL_ABS_PATH := $(shell cd $(LVGL_PATH) && pwd)
LVGL_ASRCS := $(addprefix lvgl/, \
	$(shell find $(LVGL_PATH)/src -type f -name '*.S' | sed "s|$(LVGL_ABS_PATH)/||"))
LVGL_CSRCS := $(addprefix lvgl/, \
	$(shell find $(LVGL_PATH)/src -type f -name '*.c' | sed "s|$(LVGL_ABS_PATH)/||"))

LVGL_AFLAGS += "-I$(LVGL_PATH)"
LVGL_CFLAGS += "-I$(LVGL_PATH)"
CXXFLAGS += "-I$(LVGL_PATH)"
