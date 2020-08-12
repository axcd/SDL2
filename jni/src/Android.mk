LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS) 

LOCAL_MODULE := SDL2
# 模块名
LOCAL_SRC_FILES := libs/libSDL2.so 
# 模块的文件路径（相对于 LOCAL_PATH）
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS) 

LOCAL_MODULE := hidapi
# 模块名
LOCAL_SRC_FILES := libs/libhidapi.so 
# 模块的文件路径（相对于 LOCAL_PATH）
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS) 

LOCAL_MODULE := SDL2_image
# 模块名
LOCAL_SRC_FILES := libs/libSDL2_image.so 
# 模块的文件路径（相对于 LOCAL_PATH）
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS) 

LOCAL_MODULE := SDL2_mixer
# 模块名
LOCAL_SRC_FILES := libs/libSDL2_mixer.so 
# 模块的文件路径（相对于 LOCAL_PATH）
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS) 

LOCAL_MODULE := SDL2_net
# 模块名
LOCAL_SRC_FILES := libs/libSDL2_net.so 
# 模块的文件路径（相对于 LOCAL_PATH）
include $(PREBUILT_SHARED_LIBRARY)


include $(CLEAR_VARS) 

LOCAL_MODULE := SDL2_ttf
# 模块名
LOCAL_SRC_FILES := libs/libSDL2_ttf.so 
# 模块的文件路径（相对于 LOCAL_PATH）
include $(PREBUILT_SHARED_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := main

SDL_PATH := ../SDL
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(SDL_PATH)/include

SDL_IMAGE_PATH := ../SDL_image
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(SDL_IMAGE_PATH)

SDL_MIXER_PATH := ../SDL_mixer
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(SDL_MIXER_PATH)

SDL_TTF_PATH := ../SDL_ttf
LOCAL_C_INCLUDES += $(LOCAL_PATH)/$(SDL_TTF_PATH)


# Add your application source files here...
LOCAL_SRC_FILES := run2.c

LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer SDL2_net SDL2_ttf hidapi

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)

