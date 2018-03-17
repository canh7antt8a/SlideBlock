LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../cocos2d/cocos)

LOCAL_MODULE := cocos2dcpp_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := hellocpp/main.cpp \
../../Classes/AppDelegate.cpp \
                   ../../Classes/AndroidScene.cpp \
../../Classes/DataGame.cpp \
../../Classes/GameBoard.cpp \
../../Classes/GameObject.cpp \
../../Classes/GameScene.cpp \
../../Classes/HelpScene.cpp \
../../Classes/LevelScene.cpp \
../../Classes/HomeScene.cpp \
../../Classes/LevelGame.cpp \
../../Classes/BFSSildeBlock.cpp \
../../Classes/ModeGameScene.cpp \
../../Classes/ProgressBarCustom.cpp \
../../Classes/Admob.cpp \
../../Classes/AdmodAndroid.cpp \
                   ../../Classes/SettingScene.cpp

LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../Classes

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END
