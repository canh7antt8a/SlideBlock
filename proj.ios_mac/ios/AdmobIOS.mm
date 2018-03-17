//
//  AdmobIOS.m
//  PikachuSpace
//
//  Created by Hoang Nguyen on 1/27/17.
//
//

#import "AdmobIOS.h"


typedef enum : NSUInteger {
    TopLeft = 1,
    TopCenter = 2,
    TopRight = 3,
    MiddleLeft = 4,
    MiddleCenter = 5,
    MiddleRight = 6,
    BottomLeft = 7,
    BottomCenter = 8,
    BottomRight = 9
} AdPosition;

@interface AdmobIOS() <GADBannerViewDelegate, GADInterstitialDelegate>
@property (nonatomic, strong) GADBannerView* bannerView;
@property (nonatomic, strong) GADInterstitial* interstitialAd;

@end

@implementation AdmobIOS

+ (AdmobIOS*)sharedAdmob {
    static AdmobIOS* sAdmobManager = nil;
    @synchronized (self) {
        if (sAdmobManager == nil) {
            sAdmobManager = [[self alloc] init];
        }
    }
    return sAdmobManager;
}

- (void)showBannerInPostion:(int)postion {
    if (self.bannerId == nil || self.bannerId.length == 0) {
    }
    if (self.bannerView == nil) {
        GADAdSize size;
        if ([self isLandscape]) {
            size = kGADAdSizeSmartBannerLandscape;
        }
        else
        {
            size = kGADAdSizeSmartBannerPortrait;
        }
        _bannerView = [[GADBannerView alloc] initWithAdSize:size origin:CGPointMake(0, 0)];
        [_bannerView setAdUnitID:self.bannerId];
        [_bannerView setDelegate:self];
        [_bannerView setRootViewController:[self rootViewController]];
        [[self rootViewController].view addSubview:_bannerView];
        [self.bannerView setHidden:NO];
        
        GADRequest* request = [GADRequest request];
        [self.bannerView loadRequest:request];
    }
    
    [_bannerView setFrame:[self getFrameFromPostion:postion]];
    
    [self.bannerView setHidden:NO];
}

- (void)hideBanner {
    if (self.bannerView) {
        [self.bannerView setHidden:YES];
    }
}

- (void)loadInterstitial {
    if (self.interstitialId == nil || self.interstitialId.length == 0) {
        return;
    }
    
    if (self.interstitialAd == nil) {
        self.interstitialAd = [[GADInterstitial alloc] initWithAdUnitID:self.interstitialId];
        [_interstitialAd setDelegate:self];
    }
    GADRequest* request = [GADRequest request];
    [_interstitialAd loadRequest:request];
}

- (void)showInterstitial {
    if (_interstitialAd!= nil){
        if([_interstitialAd isReady]) {
            [_interstitialAd presentFromRootViewController:[self rootViewController]];
        }
    }
    else {
        [self loadInterstitial];
    }
}



- (BOOL)isLandscape {
    UIInterfaceOrientation orientation = [self getInterfaceOrientation];
    return UIInterfaceOrientationIsLandscape(orientation);
}

- (BOOL)isPortrait {
    UIInterfaceOrientation orientation = [self getInterfaceOrientation];
    return UIInterfaceOrientationIsPortrait(orientation);
}


- (UIInterfaceOrientation) getInterfaceOrientation {
    return [self getFixedOrientation:[UIApplication sharedApplication].statusBarOrientation];
}

- (UIInterfaceOrientation)getFixedOrientation:(UIInterfaceOrientation) statusBarOrientation
{
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 8.0)
    {
        //        statusBarOrientation = UIInterfaceOrientationPortrait;
    }
    return statusBarOrientation;
}

- (CGRect)getFrameFromPostion:(int)postion {
    CGRect frame = self.bannerView.frame;
    CGRect vFrame = [self rootViewController].view.frame;
    
    // fix if error
    if (([self isLandscape] && vFrame.size.width < vFrame.size.height) || ([self isPortrait] && vFrame.size.width > vFrame.size.height)) {
        CGFloat temp = vFrame.size.width;
        vFrame.size.width = vFrame.size.height;
        vFrame.size.height = temp;
    }
    
    CGPoint point;
    switch (postion) {
        case TopLeft:
            point = CGPointMake(0, 0);
            break;
        case TopCenter:
            point = CGPointMake((vFrame.size.width - frame.size.width) / 2, 0);
            break;
        case TopRight:
            point = CGPointMake(vFrame.size.width - frame.size.width, 0);
            break;
        case MiddleLeft:
            point = CGPointMake(0, (vFrame.size.height - frame.size.height) / 2);
            break;
        case MiddleCenter:
            point = CGPointMake((vFrame.size.width - frame.size.width) / 2, (vFrame.size.height - frame.size.height) / 2);
            break;
        case MiddleRight:
            point = CGPointMake(vFrame.size.width - frame.size.width, (vFrame.size.height - frame.size.height) / 2);
            break;
        case BottomLeft:
            point = CGPointMake(0, (vFrame.size.height - frame.size.height));
            break;
        case BottomCenter:
            point = CGPointMake((vFrame.size.width - frame.size.width) / 2, (vFrame.size.height - frame.size.height));
            break;
        case BottomRight:
            point = CGPointMake(vFrame.size.width - frame.size.width, (vFrame.size.height - frame.size.height));
            break;
        default:
            break;
    }
    
    frame.origin = point;
    return frame;
}

- (UIViewController*)rootViewController {
    UIWindow* window = [[UIApplication sharedApplication] keyWindow];
    if (!window) {
        NSArray* windows = [[UIApplication sharedApplication] windows];
        window = [windows objectAtIndex:0];
    }
    
    return [window rootViewController];
}

#pragma mark - InterstitialDelegate
- (void)interstitial:(GADInterstitial *)ad didFailToReceiveAdWithError:(GADRequestError *)error {
    [self.interstitialAd release];
    self.interstitialAd = nil;
}

- (void)interstitialDidDismissScreen:(GADInterstitial *)ad {
    [self.interstitialAd release];
    self.interstitialAd = nil;
    [self loadInterstitial];
    // show banner
    [self showBannerInPostion:TopCenter];
}

- (void)interstitialDidReceiveAd:(GADInterstitial *)ad {
    
}
@end
