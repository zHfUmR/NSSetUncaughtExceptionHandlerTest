//
//  MyUncaughtExceptionHandler.m
//  CocoapodsTest
//
//  Created by Hongfei Zhai on 2023/3/29.
//

#import "MyUncaughtExceptionHandler.h"
#import "AFNetworking.h"

//sandBox path
NSString *applicationDocumentsDirectory(void) {
    return [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
}

//崩溃时的回调函数
void UncaughtExceptionHandler(NSException * exception) {
    NSArray *arr = [exception callStackSymbols];
    NSString *reason = [exception reason];
    NSString *name = [exception name];
    NSString *url = [NSString stringWithFormat:@"========异常错误报告========\nname:%@\nreason:\n%@\ncallStackSymbols:\n%@",name,reason,[arr componentsJoinedByString:@"\n"]];
    NSString *path = [applicationDocumentsDirectory() stringByAppendingPathComponent:@"Exception.txt"];
    // 将一个txt文件写入沙盒
    [url writeToFile:path atomically:YES encoding:NSUTF8StringEncoding error:nil];
}

@implementation MyUncaughtExceptionHandler

//sandBox path
- (NSString *)applicationDocumentsDirectory {
    return [NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask, YES) lastObject];
}

+ (void)setDefaultHandler {
    NSSetUncaughtExceptionHandler(&UncaughtExceptionHandler);
}

+ (NSUncaughtExceptionHandler *)getHandler {
    return NSGetUncaughtExceptionHandler();
}

+ (void)TakeException:(NSException *)exception {
    NSArray * arr = [exception callStackSymbols];
    NSString * reason = [exception reason];
    NSString * name = [exception name];
    NSString * url = [NSString stringWithFormat:@"========异常错误报告========\nname:%@\nreason:\n%@\ncallStackSymbols:\n%@",name,reason,[arr componentsJoinedByString:@"\n"]];
    NSString * path = [applicationDocumentsDirectory() stringByAppendingPathComponent:@"Exception.txt"];
    [url writeToFile:path atomically:YES encoding:NSUTF8StringEncoding error:nil];
}


@end
