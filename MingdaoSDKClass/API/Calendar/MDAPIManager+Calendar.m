//
//  MDAPIManager+Calendar.m
//  MingdaoV2
//
//  Created by WeeTom on 14-5-26.
//  Copyright (c) 2014年 Mingdao. All rights reserved.
//

#import "MDAPIManager+Calendar.h"

@implementation MDAPIManager (Calendar)
#pragma mark - 日程中心
- (MDURLConnection *)subscribeCalendar:(MDAPINSStringHandler)handler
{
    
    NSString *urlStr = [NSString stringWithFormat:@"%@/calendar/todo?u_key=%@&rssCal=1&format=json"
                        , self.serverAddress
                        , self.accessToken];
    
    urlStr = [urlStr stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        if (error) {
            handler(nil, error);
            return ;
        }
        
        NSString *urlString = [[dic objectForKey:@"calendar_url"] mutableCopy];
        handler(urlString, nil);
    }];
    return connection;
}

- (MDURLConnection *)createEventWithEventName:(NSString *)name
                              startDateString:(NSString *)sDateString
                                endDateString:(NSString *)eDateString
                                   remindType:(NSInteger)remindType
                                   remindTime:(NSInteger)remindTime
                                   categoryID:(NSString *)categoryID
                                     isAllDay:(BOOL)isAllday
                                      address:(NSString *)address
                                  description:(NSString *)des
                                    isPrivate:(BOOL)isPrivate
                              visibleGroupIDs:(NSArray *)visibleGroupIDs
                                      userIDs:(NSArray *)uIDs
                                       emails:(NSArray *)emails
                                      isRecur:(BOOL)isRecur
                                    frequency:(NSInteger)frequency
                                     interval:(NSInteger)interval
                                     weekDays:(NSString *)weekDays
                                   recurCount:(NSInteger)recurCount
                                    untilDate:(NSString *)untilDate
                                      handler:(MDAPINSStringHandler)handler
{
    NSMutableString *urlString = [self.serverAddress mutableCopy];
    [urlString appendString:@"/calendar/create"];
    NSMutableArray *parameters = [NSMutableArray array];
    [parameters addObject:@{@"key":@"access_token", @"object":self.accessToken}];
    [parameters addObject:@{@"key":@"format", @"object":@"json"}];
    [parameters addObject:@{@"key":@"c_name", @"object":name}];
    [parameters addObject:@{@"key":@"c_stime", @"object":sDateString}];
    [parameters addObject:@{@"key":@"c_etime", @"object":eDateString}];
    [parameters addObject:@{@"key":@"c_remindType", @"object":@(remindType)}];
    [parameters addObject:@{@"key":@"c_remindTime", @"object":@(remindTime)}];
    [parameters addObject:@{@"key":@"c_categoryID", @"object":categoryID}];
    [parameters addObject:@{@"key":@"c_allday", @"object":isAllday?@1:@0}];
    [parameters addObject:@{@"key":@"c_private", @"object":isPrivate?@0:@1}];
    if (isPrivate) {
        NSString *groupIDsString = [visibleGroupIDs componentsJoinedByString:@","];
        if (groupIDsString) {
            [parameters addObject:@{@"key":@"g_ids", @"object":groupIDsString}];
        }
    }
    if (address && address.length > 0)
        [parameters addObject:@{@"key":@"c_address", @"object":address}];
    if (des && des.length > 0)
        [parameters addObject:@{@"key":@"c_des", @"object":des}];
    if (uIDs && uIDs.count > 0)
        [parameters addObject:@{@"key":@"c_mids", @"object":[uIDs componentsJoinedByString:@","]}];
    if (emails && emails.count > 0)
        [parameters addObject:@{@"key":@"c_memails", @"object":[emails componentsJoinedByString:@","]}];
    if (isRecur) {
        [parameters addObject:@{@"key":@"is_recur", @"object":@1}];
        [parameters addObject:@{@"key":@"frequency", @"object":@(frequency)}];
        [parameters addObject:@{@"key":@"interval", @"object":@(interval)}];
        if (frequency == 2) {
            NSString *finalWeekDays = [weekDays stringByReplacingOccurrencesOfString:@"0" withString:@"7"];
            [parameters addObject:@{@"key":@"week_day", @"object":finalWeekDays}];
        }
        if (recurCount > 0) {
            [parameters addObject:@{@"key":@"recur_count", @"object":@(recurCount)}];
        }
        if (untilDate && untilDate.length > 0) {
            [parameters addObject:@{@"key":@"until_date", @"object":untilDate}];
        }
    }
    
    NSMutableURLRequest *req = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:urlString]];
    [self postWithParameters:parameters withRequest:req];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:req handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        if (error) {
            handler(nil, error);
            return ;
        }
        
        NSString *eventID = [dic objectForKey:@"calendar"];
        handler(eventID, nil);
    }];
    return connection;
}

- (MDURLConnection *)saveEventWithEventID:(NSString *)eID
                                     name:(NSString *)name
                          startDateString:(NSString *)sDateString
                            endDateString:(NSString *)eDateString
                               remindType:(NSInteger)remindType
                               remindTime:(NSInteger)remindTime
                               categoryID:(NSString *)categoryID
                                 isAllDay:(BOOL)isAllday
                                  address:(NSString *)address
                              description:(NSString *)des
                                isPrivate:(BOOL)isPrivate
                                  isRecur:(BOOL)isRecur
                                frequency:(NSInteger)frequency
                                 interval:(NSInteger)interval
                                 weekDays:(NSString *)weekDays
                               recurCount:(NSInteger)recurCount
                                untilDate:(NSString *)untilDate
                                  handler:(MDAPIBoolHandler)handler
{
    NSMutableString *urlString = [self.serverAddress mutableCopy];
    [urlString appendString:@"/calendar/edit"];
    NSMutableArray *parameters = [NSMutableArray array];
    [parameters addObject:@{@"key":@"access_token", @"object":self.accessToken}];
    [parameters addObject:@{@"key":@"format", @"object":@"json"}];
    [parameters addObject:@{@"key":@"c_id", @"object":eID}];
    [parameters addObject:@{@"key":@"c_name", @"object":name}];
    [parameters addObject:@{@"key":@"c_stime", @"object":sDateString}];
    [parameters addObject:@{@"key":@"c_etime", @"object":eDateString}];
    [parameters addObject:@{@"key":@"c_remindType", @"object":@(remindType)}];
    [parameters addObject:@{@"key":@"c_remindTime", @"object":@(remindTime)}];
    [parameters addObject:@{@"key":@"c_categoryID", @"object":categoryID}];
    [parameters addObject:@{@"key":@"c_allday", @"object":isAllday?@1:@0}];
    [parameters addObject:@{@"key":@"c_private", @"object":isPrivate?@0:@1}];
    
    if (address && address.length > 0)
        [parameters addObject:@{@"key":@"c_address", @"object":address}];
    if (des && des.length > 0)
        [parameters addObject:@{@"key":@"c_des", @"object":des}];
    if (isRecur) {
        [parameters addObject:@{@"key":@"is_recur", @"object":@1}];
        [parameters addObject:@{@"key":@"frequency", @"object":@(frequency)}];
        [parameters addObject:@{@"key":@"interval", @"object":@(interval)}];
        if (frequency == 2) {
            NSString *finalWeekDays = [weekDays stringByReplacingOccurrencesOfString:@"0" withString:@"7"];
            [parameters addObject:@{@"key":@"week_day", @"object":finalWeekDays}];
        }
        if (recurCount > 0) {
            [parameters addObject:@{@"key":@"recur_count", @"object":@(recurCount)}];
        }
        if (untilDate && untilDate.length > 0) {
            [parameters addObject:@{@"key":@"until_date", @"object":untilDate}];
        }
    }
    
    NSMutableURLRequest *req = [NSMutableURLRequest requestWithURL:[NSURL URLWithString:urlString]];
    [self postWithParameters:parameters withRequest:req];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:req handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        [self handleBoolData:dic error:error URLString:urlString handler:handler];
    }];
    return connection;
}

- (MDURLConnection *)addUsersWithUserIDs:(NSArray *)uIDs
                                  emails:(NSArray *)emails
                               toEventID:(NSString *)eID
                                 handler:(MDAPIBoolHandler)handler
{
    NSString *urlStr = [NSString stringWithFormat:@"%@/calendar/add_member?u_key=%@&c_id=%@&c_mids=%@&c_memails=%@&format=json"
                        , self.serverAddress
                        , self.accessToken
                        , eID
                        , uIDs.count > 0 ? [uIDs componentsJoinedByString:@","] : @""
                        , emails.count > 0 ? [emails componentsJoinedByString:@","] : @""
                        ];
    urlStr = [urlStr stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        [self handleBoolData:dic error:error URLString:urlStr handler:handler];
    }];
    return connection;
}

- (MDURLConnection *)deleteUserWithUserIDs:(NSArray *)uIDs
                                    emails:(NSArray *)emails
                               fromEventID:(NSString *)eID
                                   handler:(MDAPIBoolHandler)handler
{
    NSString *urlStr = [NSString stringWithFormat:@"%@/calendar/delete_member?u_key=%@&c_id=%@&c_mids=%@&c_memails=%@&format=json"
                        , self.serverAddress
                        , self.accessToken
                        , eID
                        , uIDs.count > 0 ? [uIDs componentsJoinedByString:@","] : @""
                        , emails.count > 0 ? [emails componentsJoinedByString:@","] : @""
                        ];
    
    urlStr = [urlStr stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        [self handleBoolData:dic error:error URLString:urlStr handler:handler];
    }];
    return connection;
}

- (MDURLConnection *)reinviteUserWithUserIDs:(NSArray *)uIDs
                                      emails:(NSArray *)emails
                                   toEventID:(NSString *)eID
                                     handler:(MDAPIBoolHandler)handler
{
    NSString *urlStr = [NSString stringWithFormat:@"%@/calendar/reinvite_member?u_key=%@&c_id=%@&c_mids=%@&c_memails=%@&format=json"
                        , self.serverAddress
                        , self.accessToken
                        , eID
                        , uIDs.count > 0 ? [uIDs componentsJoinedByString:@","] : @""
                        , emails.count > 0 ? [emails componentsJoinedByString:@","] : @""
                        ];
    
    urlStr = [urlStr stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        [self handleBoolData:dic error:error URLString:urlStr handler:handler];
    }];
    return connection;
}

- (MDURLConnection *)loadEventsWithUserIDs:(NSArray *)userIDs
                            isWorkCalendar:(NSInteger)isWorkCalendar
                         isPrivateCalendar:(NSInteger)isPrivateCalendar
                            isTaskCalendar:(NSInteger)isTaskCalendar
                                 categorys:(NSString *)categorys
                                   handler:(MDAPINSArrayHandler)handler
{
    NSMutableString *urlString = [self.serverAddress mutableCopy];
    [urlString appendString:@"/calendar/todo?format=json"];
    [urlString appendFormat:@"&access_token=%@", self.accessToken];
    if (userIDs) {
        [urlString appendFormat:@"&u_ids=%@", [userIDs componentsJoinedByString:@","]];
    }
    [urlString appendFormat:@"&isWorkCalendar=%ld",(long)isWorkCalendar];
    [urlString appendFormat:@"&isPrivateCalendar=%ld",(long)isPrivateCalendar];
    [urlString appendFormat:@"&isTaskCalendar=%ld",(long)isTaskCalendar];
    if (categorys) {
        [urlString appendFormat:@"&categorys=%@",categorys];
    }

    NSString *urlStr = [urlString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        if (error) {
            handler(nil, error);
            return ;
        }
        
        NSMutableArray *returnEvents = [NSMutableArray array];
        for (NSDictionary *aDic in [dic objectForKey:@"calendars"]) {
            MDEvent *aEvent = [[MDEvent alloc] initWithDictionary:aDic];
            [returnEvents addObject:aEvent];
        }
        
        handler(returnEvents, error);
    }];
    return connection;
}

- (MDURLConnection *)loadEventsWithUserIDs:(NSArray *)userIDs
                                    forDay:(NSString *)yearMonthAndDay
                            isWorkCalendar:(NSInteger)isWorkCalendar
                         isPrivateCalendar:(NSInteger)isPrivateCalendar
                            isTaskCalendar:(NSInteger)isTaskCalendar
                                 categorys:(NSString *)categorys
                                   handler:(MDAPINSArrayHandler)handler
{
    NSMutableString *urlString = [self.serverAddress mutableCopy];
    [urlString appendString:@"/calendar/day?format=json"];
    [urlString appendFormat:@"&access_token=%@", self.accessToken];
    [urlString appendFormat:@"&date=%@", yearMonthAndDay];
    if (userIDs) {
        [urlString appendFormat:@"&u_ids=%@", [userIDs componentsJoinedByString:@","]];
    }
    [urlString appendFormat:@"&isWorkCalendar=%ld",(long)isWorkCalendar];
    [urlString appendFormat:@"&isPrivateCalendar=%ld",(long)isPrivateCalendar];
    [urlString appendFormat:@"&isTaskCalendar=%ld",(long)isTaskCalendar];
    if (categorys.length > 0) {
        [urlString appendFormat:@"&categorys=%@",categorys];
    }

    NSString *urlStr = [urlString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        if (error) {
            handler(nil, error);
            return ;
        }
        
        NSMutableArray *returnEvents = [NSMutableArray array];
        for (NSDictionary *aDic in [dic objectForKey:@"calendars"]) {
            if (![aDic isKindOfClass:[NSDictionary class]])
                continue;
            MDEvent *aEvent = [[MDEvent alloc] initWithDictionary:aDic];
            [returnEvents addObject:aEvent];
        }
        
        handler(returnEvents, error);
    }];
    return connection;
}

- (MDURLConnection *)loadEventsWithUserIDs:(NSArray *)userIDs
                                   forWeek:(NSInteger)week
                                      year:(NSInteger)year
                            isWorkCalendar:(NSInteger)isWorkCalendar
                         isPrivateCalendar:(NSInteger)isPrivateCalendar
                            isTaskCalendar:(NSInteger)isTaskCalendar
                                 categorys:(NSString *)categorys
                                   handler:(MDAPINSArrayHandler)handler
{
    NSMutableString *urlString = [self.serverAddress mutableCopy];
    [urlString appendString:@"/calendar/week?format=json"];
    [urlString appendFormat:@"&access_token=%@", self.accessToken];
    [urlString appendFormat:@"&year=%ld", (long)year];
    [urlString appendFormat:@"&week=%ld", (long)week];
    if (userIDs) {
        [urlString appendFormat:@"&u_ids=%@", [userIDs componentsJoinedByString:@","]];
    }
    [urlString appendFormat:@"&isWorkCalendar=%ld",(long)isWorkCalendar];
    [urlString appendFormat:@"&isPrivateCalendar=%ld",(long)isPrivateCalendar];
    [urlString appendFormat:@"&isTaskCalendar=%ld",(long)isTaskCalendar];
    if (categorys) {
        [urlString appendFormat:@"&categorys=%@",categorys];
    }
    NSString *urlStr = [urlString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        if (error) {
            handler(nil, error);
            return ;
        }
        
        NSMutableArray *returnEvents = [NSMutableArray array];
        for (NSDictionary *aDic in [dic objectForKey:@"calendars"]) {
            if (![aDic isKindOfClass:[NSDictionary class]])
                continue;
            MDEvent *aEvent = [[MDEvent alloc] initWithDictionary:aDic];
            [returnEvents addObject:aEvent];
        }
        
        handler(returnEvents, error);
    }];
    return connection;
}

- (MDURLConnection *)loadEventsWithUserIDs:(NSArray *)userIDs
                                  forMonth:(NSString *)yearAndMonth
                            isWorkCalendar:(NSInteger)isWorkCalendar
                         isPrivateCalendar:(NSInteger)isPrivateCalendar
                            isTaskCalendar:(NSInteger)isTaskCalendar
                                 categorys:(NSString *)categorys
                                   handler:(MDAPINSArrayHandler)handler
{
    NSMutableString *urlString = [self.serverAddress mutableCopy];
    [urlString appendString:@"/calendar/month?format=json"];
    [urlString appendFormat:@"&access_token=%@", self.accessToken];
    [urlString appendFormat:@"&date=%@", yearAndMonth];
    if (userIDs) {
        [urlString appendFormat:@"&u_ids=%@", [userIDs componentsJoinedByString:@","]];
    }
    [urlString appendFormat:@"&isWorkCalendar=%ld", (long)isWorkCalendar];
    [urlString appendFormat:@"&isPrivateCalendar=%ld", (long)isPrivateCalendar];
    [urlString appendFormat:@"&isTaskCalendar=%ld", (long)isTaskCalendar];
    if (categorys.length > 0) {
        [urlString appendFormat:@"&categorys=%@",categorys];
    }

    NSString *urlStr = [urlString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        if (error) {
            handler(nil, error);
            return ;
        }
        
        NSMutableArray *returnEvents = [NSMutableArray array];
        for (NSDictionary *aDic in [dic objectForKey:@"calendars"]) {
            if (![aDic isKindOfClass:[NSDictionary class]])
                continue;
            MDEvent *aEvent = [[MDEvent alloc] initWithDictionary:aDic];
            [returnEvents addObject:aEvent];
        }
        
        handler(returnEvents, error);
    }];
    return connection;
}

- (MDURLConnection *)loadUnconfirmedEventsWithPageSize:(int)pageSize
                                                  page:(int)page
                                               handler:(MDAPINSArrayHandler)handler
{
    NSMutableString *urlString = [self.serverAddress mutableCopy];
    [urlString appendString:@"/calendar/invitedCalendars?format=json"];
    [urlString appendFormat:@"&access_token=%@", self.accessToken];
    [urlString appendFormat:@"&pageindex=%d", page];
    [urlString appendFormat:@"&pagesize=%d", pageSize];
    
    NSString *urlStr = [urlString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        if (error) {
            handler(nil, error);
            return ;
        }
        
        NSMutableArray *returnEvents = [NSMutableArray array];
        for (NSDictionary *aDic in [dic objectForKey:@"calendars"]) {
            if (![aDic isKindOfClass:[NSDictionary class]])
                continue;
            MDEvent *aEvent = [[MDEvent alloc] initWithDictionary:aDic];
            [returnEvents addObject:aEvent];
        }
        
        handler(returnEvents, error);
    }];
    return connection;
}

- (MDURLConnection *)loadUpComingEventsForChatCardWithKeywors:(NSString *)keywords
                                                      handler:(MDAPINSArrayHandler)handler
{
    
    NSMutableString *urlString = [self.serverAddress mutableCopy];
    [urlString appendString:@"/calendar/getChatCalendars.aspx?format=json"];
    [urlString appendFormat:@"&access_token=%@", self.accessToken];
    if (keywords) {
        [urlString appendFormat:@"&keywords=%@", keywords];
    }
    
    NSString *urlStr = [urlString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        if (error) {
            handler(nil, error);
            return ;
        }
        
        NSMutableArray *returnEvents = [NSMutableArray array];
        for (NSDictionary *aDic in [dic objectForKey:@"calendars"]) {
            if (![aDic isKindOfClass:[NSDictionary class]])
                continue;
            MDEvent *aEvent = [[MDEvent alloc] initWithDictionary:aDic];
            [returnEvents addObject:aEvent];
        }
        
        handler(returnEvents, error);
    }];
    return connection;
}

- (MDURLConnection *)loadEventWithObjectID:(NSString *)objectID handler:(MDAPIObjectHandler)handler
{
    NSString *urlStr = [NSString stringWithFormat:@"%@/calendar/detail?u_key=%@&c_id=%@&format=json"
                        , self.serverAddress
                        , self.accessToken
                        , objectID];
    
    urlStr = [urlStr stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        if (error) {
            handler(nil, error);
            return ;
        }
        
        NSDictionary *aDic = [dic objectForKey:@"calendar"];
        MDEvent *returnEvent = [[MDEvent alloc] initWithDictionary:aDic];
        handler(returnEvent, error);
    }];
    return connection;
}

- (MDURLConnection *)deleteEventWithObjectID:(NSString *)objectID handler:(MDAPIBoolHandler)handler
{
    NSString *urlStr = [NSString stringWithFormat:@"%@/calendar/destroy?u_key=%@&c_id=%@&format=json"
                        , self.serverAddress
                        , self.accessToken
                        , objectID];
    
    urlStr = [urlStr stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        [self handleBoolData:dic error:error URLString:urlStr handler:handler];
    }];
    return connection;
}

- (MDURLConnection *)exitEventWithObjectID:(NSString *)objectID handler:(MDAPIBoolHandler)handler
{
    NSString *urlStr = [NSString stringWithFormat:@"%@/calendar/exit?u_key=%@&c_id=%@&format=json"
                        , self.serverAddress
                        , self.accessToken
                        , objectID];
    
    urlStr = [urlStr stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        [self handleBoolData:dic error:error URLString:urlStr handler:handler];
    }];
    return connection;
}

- (MDURLConnection *)acceptEventWithObjectID:(NSString *)objectID handler:(MDAPIBoolHandler)handler
{
    NSString *urlStr = [NSString stringWithFormat:@"%@/calendar/join?u_key=%@&c_id=%@&format=json"
                        , self.serverAddress
                        , self.accessToken
                        , objectID];
    
    urlStr = [urlStr stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        [self handleBoolData:dic error:error URLString:urlStr handler:handler];
    }];
    return connection;
}

- (MDURLConnection *)rejectEventWithObjectID:(NSString *)objectID handler:(MDAPIBoolHandler)handler
{
    NSString *urlStr = [NSString stringWithFormat:@"%@/calendar/deny?u_key=%@&c_id=%@&format=json"
                        , self.serverAddress
                        , self.accessToken
                        , objectID];
    
    urlStr = [urlStr stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        [self handleBoolData:dic error:error URLString:urlStr handler:handler];
    }];
    return connection;
}

- (MDURLConnection *)loadCurrentUserEventCategory:(MDAPINSArrayHandler)handler
{
    NSString *urlStr = [NSString stringWithFormat:@"%@/calendar/getUserAllCalCategories?u_key=%@&format=json"
                        , self.serverAddress
                        , self.accessToken];
    
    urlStr = [urlStr stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        if (error) {
            handler(nil, error);
            return ;
        }
        
        NSMutableArray *returnCalendars = [NSMutableArray array];
        for (NSDictionary *aDic in [dic objectForKey:@"categorys"]) {
            if (![aDic isKindOfClass:[NSDictionary class]])
                continue;
            MDCalendarCategory *calendar = [[MDCalendarCategory alloc]initWithDictionary:aDic];
            [returnCalendars addObject:calendar];
        }
        
        handler(returnCalendars, error);
    }];
    return connection;
}

- (MDURLConnection *)addCurrentUserEventCategoryWithCatName:(NSString *)catName color:(NSInteger)color handler:(MDAPIBoolHandler)handler
{
    NSMutableString *urlString = [NSMutableString stringWithFormat:@"%@/calendar/addUserCalCategory?u_key=%@&format=json"
                                  , self.serverAddress
                                  , self.accessToken];
    [urlString appendFormat:@"&catName=%@", catName];
    [urlString appendFormat:@"&color=%ld", (long)color];
    NSString *urlStr = [urlString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        [self handleBoolData:dic error:error URLString:urlStr handler:handler];
    }];
    return connection;
    

}

- (MDURLConnection *)editCurrentUserEventCategoryWithCatName:(NSString *)catName catID:(NSString *)catID color:(NSInteger)color handler:(MDAPIBoolHandler)handler
{
    NSMutableString *urlString = [NSMutableString stringWithFormat:@"%@/calendar/upUserCalCategory?u_key=%@&format=json"
                                  , self.serverAddress
                                  , self.accessToken];
    [urlString appendFormat:@"&catName=%@", catName];
    [urlString appendFormat:@"&catID=%@",catID];
    [urlString appendFormat:@"&color=%ld", (long)color];
    NSString *urlStr = [urlString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        [self handleBoolData:dic error:error URLString:urlStr handler:handler];
    }];
    return connection;
}

- (MDURLConnection *)deleteCurrentUserEventCategoryWithCatID:(NSString *)catID handler:(MDAPIBoolHandler)handler
{
    NSMutableString *urlString = [NSMutableString stringWithFormat:@"%@/calendar/delUserCalCategory?u_key=%@&format=json"
                                  , self.serverAddress
                                  , self.accessToken];
    [urlString appendFormat:@"&catID=%@",catID];
    NSString *urlStr = [urlString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        [self handleBoolData:dic error:error URLString:urlStr handler:handler];
    }];
    return connection;
}

- (MDURLConnection *)loadBusyEventsWithStartTime:(NSString *)startDateString endTime:(NSString *)endDateString handler:(MDAPINSArrayHandler)handler
{
    NSMutableString *urlString = [NSMutableString stringWithFormat:@"%@/calendar/getUserBusyCalendar?u_key=%@&format=json"
                        , self.serverAddress
                        , self.accessToken];
    [urlString appendFormat:@"&c_stime=%@", startDateString];
    [urlString appendFormat:@"&c_etime=%@", endDateString];
    NSString *urlStr = [urlString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];

    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        if (error) {
            handler(nil, error);
            return ;
        }
        
        NSMutableArray *returnEvents = [NSMutableArray array];
        for (NSDictionary *aDic in [dic objectForKey:@"Calendars"]) {
            if (![aDic isKindOfClass:[NSDictionary class]])
                continue;
            MDEvent *aEvent = [[MDEvent alloc] initWithDictionary:aDic];
            [returnEvents addObject:aEvent];
        }
        handler(returnEvents, error);
    }];
    return connection;
}

- (MDURLConnection *)modifyEventMemberRemindWithObjectID:(NSString *)objectID remindType:(NSInteger)remindType remindTime:(NSInteger)remindTime handler:(MDAPINSStringHandler)handler
{
    NSMutableString *urlString = [NSMutableString stringWithFormat:@"%@/calendar/upCalRemind?u_key=%@&format=json"
                                  , self.serverAddress
                                  , self.accessToken];
    [urlString appendFormat:@"&c_id=%@",objectID];
    [urlString appendFormat:@"&c_remindType=%ld", (long)remindType];
    [urlString appendFormat:@"&c_remindTime=%ld", (long)remindTime];
    NSString *urlStr = [urlString stringByAddingPercentEscapesUsingEncoding:NSUTF8StringEncoding];
    MDURLConnection *connection = [[MDURLConnection alloc] initWithRequest:[NSURLRequest requestWithURL:[NSURL URLWithString:urlStr]] handler:^(MDURLConnection *theConnection, NSDictionary *dic, NSError *error) {
        if (error) {
            handler(nil, error);
            return ;
        }
        
        NSString *urlstring = [[dic objectForKey:@"count"] mutableCopy];
        handler(urlstring, nil);
    }];
    return connection;

    
}


@end
