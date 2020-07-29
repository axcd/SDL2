###########################
#
# libSDL2main shared library
#
###########################

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := SDL2main

SDL_PATH := ../SDL

SDL_IMAGE_PATH := ../SDL2_image

SDL_TTF_PATH := ../SDL2_ttf

SDL_MIXER_PATH := ../SDL2_mixer

LOCAL_C_INCLUDES := $(LOCAL_PATH)/$(SDL_PATH)/include \
                    $(LOCAL_PATH)/$(SDL_IMAGE_PATH)  \
                    $(LOCAL_PATH)/$(SDL_MIXER_PATH) \
                    $(LOCAL_PATH)/$(SDL_TTF_PATH)

# Add your application source files here...
LOCAL_SRC_FILES := $(SDL_PATH)/src/main/android/SDL_android_main.c \
                   ttf.c
    
LOCAL_SHARED_LIBRARIES := SDL2 SDL2_image SDL2_mixer SDL2_ttf

LOCAL_LDLIBS := -lGLESv1_CM -lGLESv2 -llog

include $(BUILD_SHARED_LIBRARY)
