//
//  AdmobIOS.h
//  PikachuSpace
//
//  Created by Hoang Nguyen on 1/27/17.
//
//

#import <Foundation/Foundation.h>
#import <GoogleMobileAds/GADBannerView.h>
#import <GoogleMobileAds/GADInterstitial.h>

@interface AdmobIOS: NSObject
@property (nonatomic, strong) NSString* bannerId;
@property (nonatomic, strong) NSString* interstitialId;

+ (AdmobIOS*)sharedAdmob;

- (void)showBannerInPostion:(int)postion;

- (void)hideBanner;

- (void)loadInterstitial;

- (void)showInterstitial;

@end
