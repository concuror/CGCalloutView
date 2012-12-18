//    Copyright 2012 Andrii Titov
//
//    Licensed under the Apache License, Version 2.0 (the "License");
//    you may not use this file except in compliance with the License.
//    You may obtain a copy of the License at
//
//    http://www.apache.org/licenses/LICENSE-2.0
//
//    Unless required by applicable law or agreed to in writing, software
//    distributed under the License is distributed on an "AS IS" BASIS,
//    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//    See the License for the specific language governing permissions and
//    limitations under the License.

enum {
    SMCalloutArrowDirectionUp = 1UL << 0,
    SMCalloutArrowDirectionDown = 1UL << 1,
    SMCalloutArrowDirectionAny = SMCalloutArrowDirectionUp | SMCalloutArrowDirectionDown
};
typedef NSUInteger SMCalloutArrowDirection;

// when delaying our popup in order to scroll content into view, you can use this amount to match the
// animation duration of UIScrollView when using -setContentOffset:animated.
extern NSTimeInterval kCGCalloutViewRepositionDelayForUIScrollView;

@protocol CGCalloutViewDelegate;
@class CGCalloutViewBackground;

//
// Callout view.
//

@interface CGCalloutView : CCLayer
@property(nonatomic, unsafe_unretained) id <CGCalloutViewDelegate> delegate;
@property(nonatomic, copy) NSString *title, *subtitle; // title/titleView relationship mimics UINavigationBar.
@property(nonatomic, retain) CCNode<CCTextureProtocol> *titleView, *subtitleView; // if these are set, the respective title/subtitle properties will be ignored
@property(nonatomic, retain) CCNode<CCTextureProtocol> *leftAccessoryView, *rightAccessoryView;
@property(nonatomic, retain) CGCalloutViewBackground *background;

// calloutOffset is the offset in screen points from the top-middle of the annotation view, where the anchor of the callout should be shown.
@property(nonatomic, assign) CGPoint calloutOffset;

// Presents a callout view by adding it to "inView" and pointing at the given rect of inView's bounds.
// Constrains the callout to the bounds of the given view. Optionally scrolls the given rect into view (plus margins)
// if -delegate is set and responds to -delayForRepositionWithSize.
- (void)presentFromRect:(CGRect)rect inNode:(CCNode *)node constrainedToNode:(CCNode *)constrainedNode permittedArrowDirections:(SMCalloutArrowDirection)arrowDirections animated:(BOOL)animated;

- (void)dismissCalloutAnimated:(BOOL)animated;
@end
//
// Class for collating the various background images that are pieced together to form the overall background graphic with the pointy arrow.
//

@interface CGCalloutViewBackground : NSObject
@property(nonatomic, retain) CCTexture2D *leftCapImage, *rightCapImage, *topAnchorImage, *bottomAnchorImage, *backgroundImage;

+ (CGCalloutViewBackground *)systemBackground;
@end

@protocol CGCalloutViewDelegate <NSObject>
@optional

// Called when the callout view detects that it will be outside the constrained view when it appears,
// or if the target rect was already outside the constrained view. You can implement this selector to
// respond to this situation by repositioning your content first in order to make everything visible. The
// CGSize passed is the calculated offset necessary to make everything visible (plus a nice margin).
// It expects you to return the amount of time you need to reposition things so the popup can be delayed.
// Typically you would return kCGCalloutViewRepositionDelayForUIScrollView if you're repositioning by
// calling [UIScrollView setContentOffset:animated:].
- (NSTimeInterval)calloutView:(CGCalloutView *)calloutView delayForRepositionWithSize:(CGSize)offset;

// Called after the callout view appears on screen, or after the appearance animation is complete.
- (void)calloutViewDidAppear:(CGCalloutView *)calloutView;


@end


