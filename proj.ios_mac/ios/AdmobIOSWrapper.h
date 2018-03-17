//
//  AdmobIOSWrapper.h
//  PikachuSpace
//
//  Created by Hoang Nguyen on 1/27/17.
//
//

#include "cocos2d.h"

class AdmobIOSWrapper {
public:
    static AdmobIOSWrapper* getInstance();
    
    void init(const std::string &bannerId, const std::string &interstitialId);
    
    void showBanner(int position);
    
    void hideBanner();
    
    void loadInterstitial();
    
    void showInterstitial();
};

