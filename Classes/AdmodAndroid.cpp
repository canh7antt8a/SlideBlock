//
//  AdmodAndroid.cpp

#include "AdmodAndroid.h"
#include "cocos2d.h"

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
#include "jni/JniHelper.h"
extern "C"{
    void AdmodAndroid::showBanner(){

        JniMethodInfo methodInfo;
        bool b = JniHelper::getStaticMethodInfo(methodInfo,"org.cocos2dx.cpp.AppActivity","showAd","()V");
        if(b){
        	 log("aaaaaaaaaaaaaaaaaaaaaaaaaaa");
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
            
        }else{
            log("Error");
        }
    }
    void AdmodAndroid::hideBanner(){
        JniMethodInfo methodInfo;
        bool b = JniHelper::getStaticMethodInfo(methodInfo,"org.cocos2dx.cpp.AppActivity","hideAd","()V");
        if(b){
       	 log("bbbbbbbbbbbbbbbbbbbbbbbbbb");
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }else{
            log("Error");
        }
    }
    void AdmodAndroid::showFullAdvertiment(){
        JniMethodInfo methodInfo;
        bool b = JniHelper::getStaticMethodInfo(methodInfo,"org.cocos2dx.cpp.AppActivity","showInterstitialAd","()V");
        if(b)
        {
            methodInfo.env->CallStaticVoidMethod(methodInfo.classID, methodInfo.methodID);
            methodInfo.env->DeleteLocalRef(methodInfo.classID);
        }
        else{
            log("Error");
        }

    }
}
#endif
