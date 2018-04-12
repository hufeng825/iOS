//
//  DrawUtils.h
//  NDL_Category
//
//  Created by dzcx on 2018/3/26.
//  Copyright © 2018年 ndl. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "NDLConstants.h"

@interface DrawUtils : NSObject

// 绘制虚线 还可以通过CAShapeLayer
+ (void)drawDashedLineInContext:(CGContextRef)context
                      lineWidth:(CGFloat)lineWidth // 线的粗细
                        lineCap:(CGLineCap)lineCap
                lineDashPattern:(CGFloat *)lengthArray
                lineStrokeColor:(CGColorRef)lineStrokeColor
                 lineBeginPoint:(CGPoint)lineBeginPoint
                   lineEndPoint:(CGPoint)lineEndPoint;

// 绘制闹钟
+ (void)drawClockInContext:(CGContextRef)context
                 lineWidth:(CGFloat)lineWidth
           lineStrokeColor:(CGColorRef)lineStrokeColor
                    radius:(CGFloat)radius
               centerPoint:(CGPoint)centerPoint
            hourHandLength:(CGFloat)hourHandLength// 时针长度
             hourHandValue:(CGFloat)hourHandValue// 时针数值 1-12
          minuteHandLength:(CGFloat)minuteHandLength
           minuteHandValue:(CGFloat)minuteHandValue;

// 绘制delete图案
+ (void)drawDeletePatternInContext:(CGContextRef)context
                         lineWidth:(CGFloat)lineWidth
                   lineStrokeColor:(CGColorRef)lineStrokeColor
                            radius:(CGFloat)radius
                       centerPoint:(CGPoint)centerPoint;

// 绘制圆点
+ (void)drawDotInContext:(CGContextRef)context
               fillColor:(CGColorRef)fillColor
             centerPoint:(CGPoint)centerPoint
                  radius:(CGFloat)radius;

// 绘制气泡框(三角)
+ (void)drawBubbleFrameWithTriangleInContext:(CGContextRef)context
                                        rect:(CGRect)rect
                                   lineWidth:(CGFloat)lineWidth
                             lineStrokeColor:(CGColorRef)lineStrokeColor
                                   fillColor:(CGColorRef)fillColor
                                cornerRadius:(CGFloat)cornerRadius
                              arrowDirection:(BubbleFrameArrowDirection)arrowDirection
                                 arrowHeight:(CGFloat)arrowHeight
                                controlPoint:(CGPoint)controlPoint
                      controlPointOffsetLeft:(CGFloat)controlPointOffsetLeft
                     controlPointOffsetRight:(CGFloat)controlPointOffsetRight;




@end