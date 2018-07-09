//
//  TestModel.m
//  NDL_Category
//
//  Created by dzcx on 2018/7/9.
//  Copyright © 2018年 ndl. All rights reserved.
//

#import "TestModel.h"

@implementation TestModel

#pragma mark - NSCoding
// runtime 归档 && 解档
- (void)encodeWithCoder:(NSCoder *)coder
{
    unsigned int count = 0;
    Ivar *ivars = class_copyIvarList([TestModel class], &count);
    for (int i = 0; i < count; i++) {
        Ivar ivar = ivars[i];
        const char *name = ivar_getName(ivar);// 获取到属性的C字符串名称
        NSString *key = [NSString stringWithUTF8String:name];// 转成对应的OC字符串名称
        [coder encodeObject:[self valueForKey:key] forKey:key];
    }
    free(ivars);//在OC中使用了Copy、Creat、New类型的函数，需要释放指针！！（注：ARC管不了C函数）
}

- (instancetype)initWithCoder:(NSCoder *)coder
{
    self = [super init];
    if (self) {
        unsigned int count = 0;
        Ivar *ivars = class_copyIvarList([TestModel class], &count);
        for (int i = 0; i < count; i++) {
            Ivar ivar = ivars[i];
            const char *name = ivar_getName(ivar);
            NSString *key = [NSString stringWithUTF8String:name];
            id value = [coder decodeObjectForKey:key];
            [self setValue:value forKey:key];
        }
        free(ivars);
    }
    return self;
}

@end