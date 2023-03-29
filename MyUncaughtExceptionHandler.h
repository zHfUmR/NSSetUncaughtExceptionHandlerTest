//
//  MyUncaughtExceptionHandler.h
//  CocoapodsTest
//
//  Created by Hongfei Zhai on 2023/3/29.
//

#import <Foundation/Foundation.h>
/**
 崩溃日志 - iOS SDK中提供了一个现成的函数NSSetUncaughtExceptionHandler
 用来做异常处理利用NSSetUncaughtExceptionHandler，当程序异常退出的时候，可以先进行处理，然后做一些自定义的动作,并通知开发者，是大多数软件都选择的方法。
 */
NS_ASSUME_NONNULL_BEGIN

@interface MyUncaughtExceptionHandler : NSObject

+ (void)setDefaultHandler;

+ (NSUncaughtExceptionHandler *)getHandler;

+ (void)TakeException:(NSException *)exception;

@end

NS_ASSUME_NONNULL_END
/**
 AppDelegate使用：
 --
 [MyUncaughtExceptionHandler setDefaultHandler];
 //push crash log
 NSString *path = [NSSearchPathForDirectoriesInDomains(NSDocumentationDirectory, NSUserDomainMask, YES) lastObject];
 NSString *dataPath = [path stringByAppendingPathComponent:@"Exception.txt"];
 NSData *data = [NSData dataWithContentsOfFile:dataPath];
 if (data != nil) {
 [self sendExceptionLogWithData:data path:path];
 }
 --
 - (void)sendExceptionLogWithData:(NSData *)data path:(NSString *)path {
 
 AFHTTPSessionManager *manager = [AFHTTPSessionManager manager];
 manager.requestSerializer.timeoutInterval = 5.0f;
 //告诉AFN 支持接受text/xml的数据
 [AFJSONResponseSerializer serializer].acceptableContentTypes = [NSSet setWithObject:@"text/plain"];
 NSString *urlStr = @"后台地址";
 
 [manager POST:urlStr parameters:nil headers:nil constructingBodyWithBlock:^(id<AFMultipartFormData>  _Nonnull formData) {
 [formData appendPartWithFileData:data name:@"file" fileName:@"Exception.txt" mimeType:@"txt"];
 } progress:^(NSProgress * _Nonnull uploadProgress) {
 
 } success:^(NSURLSessionDataTask * _Nonnull task, id  _Nullable responseObject) {
 
 } failure:^(NSURLSessionDataTask * _Nullable task, NSError * _Nonnull error) {
 
 }];
 }
 
 */
