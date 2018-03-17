//
//  Admob.cpp


#include "Admob.h"
#include "cocos2d.h"
using namespace std;
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
#include "AdmobIOSWrapper.h"
#endif

static Admob _sAdmobManager;

Admob* Admob::getInstance() {
    return &_sAdmobManager;
}

void Admob::init(const std::string &bannerId, const std::string &interstitialId) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    AdmobIOSWrapper::getInstance()->init(bannerId, interstitialId);
#endif
}

void Admob::showBanner(AdmobPosition position) {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    AdmobIOSWrapper::getInstance()->showBanner((int)position);
#endif
}

void Admob::hideBanner() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    AdmobIOSWrapper::getInstance()->hideBanner();
#endif
}

void Admob::loadInterstitial() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    AdmobIOSWrapper::getInstance()->loadInterstitial();
#endif
}

void Admob::showInterstitial() {
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    AdmobIOSWrapper::getInstance()->showInterstitial();
#endif
}