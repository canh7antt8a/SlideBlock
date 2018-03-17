//
//  AdmobIOS.H
//

#include <string>
enum class AdmobPosition {
    TopLeft = 1,
    TopCenter = 2,
    TopRight = 3,
    MiddleLeft = 4,
    MiddleCenter = 5,
    MiddleRight = 6,
    BottomLeft = 7,
    BottomCenter = 8,
    BottomRight = 9
};

class Admob {
public:
    static Admob* getInstance();
    
    void init(const std::string &bannerId, const std::string &interstitialId);
    
    void showBanner(AdmobPosition position);
    
    void hideBanner();
    
    void loadInterstitial();
    
    void showInterstitial();
    void showAdcolony();
    
};