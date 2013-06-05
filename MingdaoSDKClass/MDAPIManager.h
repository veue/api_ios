//
//  MDAPIManager.h
//  Mingdao
//
//  Created by Wee Tom on 13-4-26.
//
//

#import <Foundation/Foundation.h>
#import "MDAPIHandler.h"

@interface MDAPIManager : NSObject
+ (MDAPIManager *)sharedManager;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 设置私有部署API地址，默认为:https://api.mingdao.com/
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (void)setServerAddress:(NSString *)serverAddress;

#pragma mark - 登录/验证接口

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 通过用户名密码登陆，可能返回多个MDProject，如果只有一个，则登陆成功或失败
 @parmas:
 username - 用户登录名
 password - 用户登陆密码
 pHandler - 处理存在多网络的情况，返回包含多个MDProject的NSArray
 sHandler - 处理仅存在一个网络时登陆结果
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loginWithUsername:(NSString *)username
                 password:(NSString *)password
           projectHandler:(MDAPINSArrayHandler)pHandler
                  handler:(MDAPIBoolHandler)sHandler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 通过用户名密码以及选定的MDProject.objectID来登陆，projectID为必填
 @parmas:
 username  - 用户登录名
 password  - 用户登陆密码
 projectID - 登陆的网络ID，ID(MDProject.objectID)可从上方的方法获取
 handler   - 处理登陆结果
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loginWithUsername:(NSString *)username
                 password:(NSString *)password
                projectID:(NSString *)projectID
                  handler:(MDAPIBoolHandler)handler;

#pragma mark - 账号接口

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 获取当前登录用户的基本信息
 @parmas:
 handler - 处理MDUser结果
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadCurrentUserDetailWithHandler:(MDAPIObjectHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 获取当前登录用户的未读信息数量
 @parmas:
 handler - 处理NSDictionary结果（keys: updated, replyme, atme, message, task）
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#define MDAPIResultKeyUnreadUpdated @"updated"
#define MDAPIResultKeyUnreadReplyme @"replyme"
#define MDAPIResultKeyUnreadAtme    @"atme"
#define MDAPIResultKeyUnreadMessage @"message"
#define MDAPIResultKeyUnreadTask    @"task"
- (MDURLConnection *)loadCurrentUserUnreadCountWithHandler:(MDAPINSDictionaryHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 登出
 @parmas:
 handler - 处理登出后的结果
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)logoutWithHandler:(MDAPIBoolHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 保存新的用户信息到服务器
 @parmas:
 name必须 - 用户姓名
 dep必须  - 部门
 job必须 - 工作
 mpn可选  - 移动号码
 wpn可选  - 工作号码
 birthday可选 - 生日
 gender可选   - 性别
 handler - 处理修改后的结果
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)saveUserWithName:(NSString *)name
              department:(NSString *)dep
                     job:(NSString *)job
       mobilePhoneNumber:(NSString *)mpn
         workPhoneNumber:(NSString *)wpn
                birthday:(NSString *)birthday
                  gender:(NSInteger)gender
                 handler:(MDAPIBoolHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 保存新的用户头像
 @parmas:
 avatarImg - 头像图片，不超过5MB
 handler - 处理修改后的结果
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)saveUserWithAvatar:(UIImage *)avatarImg handler:(MDAPIBoolHandler)handler;

#pragma mark - 私信接口

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 获取当前登录用户私人消息列表（列举所有私信的发送人列表,按照最新消息时间排序）
 @parmas:
 handler - 处理获取到的包含多个MDMessageAll的NSArray
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadCurrentUserMessagesWithHandler:(MDAPINSArrayHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 获取当前登录用户与其它单个用户的私人消息列表
 @parmas:
 userID   - 私信来自这个userID的user
 pageSize - 每页包含的私信数量 默认20，最大100
 page     - 私信的页数
 handler  - 处理获取到的包含多个MDMessage的NSArray
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadMessagesWithUserID:(NSString *)userID
                      pageSize:(NSInteger)size
                          page:(NSInteger)pages
                       handler:(MDAPINSArrayHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 向某个用户发送一条私人消息
 @parmas:
 userID   - 私信来自这个userID的user
 text     - 私信内容
 type     - 默认为0；1表示接收消息者发送系统消息（仅限应用创建者）
 handler  - 处理发送成功后返回的私信ID
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)sendMessageToUserID:(NSString *)userID
                    message:(NSString *)text
                       type:(NSInteger)type
                    handler:(MDAPINSStringHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 删除当前登录用户的私人消息
 @parmas:
 mID      - 被删除的消息编号
 handler  - 处理删除的结果
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)deleteMessageWithMessageID:(NSString *)mID handler:(MDAPIBoolHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 标记某条消息已经阅读
 @parmas:
 mID      - 被阅读的消息编号
 handler  - 处理已读的结果
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)markMessageAsReadWithMessageID:(NSString *)mID handler:(MDAPIBoolHandler)handler;

#pragma mark - 群组接口

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 获取所有群组
 @parmas:
 keywords - 包含的关键词，可选
 handler  - 处理包含多个MDGroup的NSArray
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadAllGroupsWithKeywords:(NSString *)keywords handler:(MDAPINSArrayHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 获取所有当前用户创建的群组
 @parmas:
 handler  - 处理包含多个MDGroup的NSArray
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadCurrentUserCreatedGroupsWithHandler:(MDAPINSArrayHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 获取所有当前用户加入的群组
 @parmas:
 handler  - 处理包含多个MDGroup的NSArray
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadCurrentUserJoinedGroupsWithHandler:(MDAPINSArrayHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 获取单个群组详情
 @parmas:
 gID      - 群组ID
 handler  - 处理单个MDGroup
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadGroupsWithGroupID:(NSString *)gID handler:(MDAPIObjectHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 获取单个群组的所有成员
 @parmas:
 gID      - 群组ID
 handler  - 处理包含多个MDUser的NSArray
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadGroupMembersWithGroupID:(NSString *)gID handler:(MDAPINSArrayHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 群组操作（退出、加入、关闭、开启、删除）
 @parmas:
 gID      - 群组ID
 handler  - 处理操作结果
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)exitGroupWithGroupID:(NSString *)gID handler:(MDAPIBoolHandler)handler;
- (MDURLConnection *)joinGroupWithGroupID:(NSString *)gID handler:(MDAPIBoolHandler)handler;
- (MDURLConnection *)closeGroupWithGroupID:(NSString *)gID handler:(MDAPIBoolHandler)handler;
- (MDURLConnection *)openGroupWithGroupID:(NSString *)gID handler:(MDAPIBoolHandler)handler;
- (MDURLConnection *)deleteGroupWithGroupID:(NSString *)gID handler:(MDAPIBoolHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 创建群组
 @parmas:
 gName - 群组名称，必须
 isPub - 是否开放，可选
 handler - 处理修改后的结果
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)createGroupWithGroupName:(NSString *)gName
                        isPublic:(BOOL)isPub
                         handler:(MDAPIObjectHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 邀请用户（同事邮箱）加入群组
 @parmas:
 gID        - 群组ID，必须
 被邀请者邮箱 - 是否开放，必须
 handler    - 处理邀请结果
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)inviteUserToGroupWithGroupID:(NSString *)gID
                               email:(NSString *)email
                             handler:(MDAPIBoolHandler)handler;

#pragma mark - 用户接口

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 获取企业通讯录信息
 @parmas:
 handler - 处理包含多个MDUser的NSArray
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadAllUsersWithHandler:(MDAPINSArrayHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 根据筛选条件获取用户列表信息
 @parmas:
 keywords - 关键词 可选
 gID      - 所在群组ID 可选
 dep      - 所在部门 可选
 handler  - 处理包含多个MDUser的NSArray
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadUsersWithKeywords:(NSString *)keywords
                      groupID:(NSString *)gID
                   department:(NSString *)dep
                      handler:(MDAPINSArrayHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 根据用户编号获取用户的基本资料
 @parmas:
 uID      - 用户编号
 handler  - 处理MDUser
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadUserWithUserID:(NSString *)uID
                   handler:(MDAPIObjectHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 根据用户编号获取用户正在关注用户信息
 @parmas:
 uID      - 用户编号
 handler  - 处理包含多个MDUser的NSArray
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadUserFollowedByUserWithUserID:(NSString *)uID
                                 handler:(MDAPIObjectHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 获取企业所有部门列表信息
 @parmas:
 handler  - 处理包含多个NSString的NSArray
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadAllDepartmentsWithHandler:(MDAPINSArrayHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 关注，取消关注用户
 @parmas:
 userID   - 被关注，取消的用户编号
 handler  - 处理包含多个NSString的NSArray
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)followUserWithUserID:(NSString *)userID handler:(MDAPIBoolHandler)handler;
- (MDURLConnection *)unfollowUserWithUserID:(NSString *)userID handler:(MDAPIBoolHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 邀请用户（同事邮箱）加入企业网络
 @parmas:
 type -	邀请类型。默认值0，表示网络内有效邮箱域名邀请；1表示来宾邀请（仅限高级模式）可选
 email - 邀请的邮箱 必须
 fullname - 被邀请人姓名 必须
 msg - 邀请的消息 必须
 handler    - 处理邀请结果
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)inviteUserToCompanyWithEmail:(NSString *)email
                            fullname:(NSString *)fullname
                                 msg:(NSString *)msg
                                type:(NSInteger)type
                             handler:(MDAPIBoolHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 获取当前登录用户常用联系人列表
 @parmas:
 handler  - 处理包含多个MDUser的NSArray
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadFavouritedUsersWithHandler:(MDAPIObjectHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 当前登录用户添加/删除常用关系
 @parmas:
 uID     - 被操作对象编号
 handler - 处理包含多个MDUser的NSArray
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)favouriteUserWithUserID:(NSString *)uID handler:(MDAPIBoolHandler)handler;
- (MDURLConnection *)unfavouriteUserWithUserID:(NSString *)uID handler:(MDAPIBoolHandler)handler;

#pragma mark - 日程中心

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 获取当前用户日历订阅地址
 @parmas:
 handler - 处理返回的地址结果
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)subscribeCalendar:(MDAPINSStringHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 创建日程
 @parmas:
 name    - 日程名称
 sDateString - 日程开始时间，精确到分。如：2013-05-05 10:25
 eDateString - 日程结束时间，精确到分。如：2013-05-05 10:25
 isAllday - 是否全天日程。0表示非全天，1表示全天
 address - 日程地点
 des - 日程描述
 isPrivate - 是否私人日程。1表示私人，0表示非私人
 uIDs - 指定的日程成员 (多个成员用逗号隔开)。注：明道用户
 emails - 指定的日程成员邮件 (多个成员用逗号隔开)。注：非明道用户
 handler - 创建成功返回日程编号
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)createEventWithEventName:(NSString *)name
                 startDateString:(NSString *)sDateString
                   endDateString:(NSString *)eDateString
                        isAllDay:(BOOL)isAllday
                         address:(NSString *)address
                     description:(NSString *)des
                       isPrivate:(BOOL)isPrivate
                         userIDs:(NSArray *)uIDs
                          emails:(NSArray *)emails
                         handler:(MDAPINSStringHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 编辑日程
 @parmas:
 eID     - 被修改日程编号
 name    - 日程名称
 sDateString - 日程开始时间，精确到分。如：2013-05-05 10:25
 eDateString - 日程结束时间，精确到分。如：2013-05-05 10:25
 isAllday - 是否全天日程。0表示非全天，1表示全天
 address - 日程地点
 des - 日程描述
 isPrivate - 是否私人日程。1表示私人，0表示非私人
 handler - 处理编辑结果
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)saveEventWithEventID:(NSString *)eID
                        name:(NSString *)name
             startDateString:(NSString *)sDateString
               endDateString:(NSString *)eDateString
                    isAllDay:(BOOL)isAllday
                     address:(NSString *)address
                 description:(NSString *)des
                   isPrivate:(BOOL)isPrivate
                     handler:(MDAPIBoolHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 邀请/取消邀请/再次邀请用户加入日程
 @parmas:
 eIDs - 被邀请用户们的ID
 emails - 被邀请的用户们的email
 handler - 处理结果
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)addUsersWithUserIDs:(NSArray *)uIDs emails:(NSArray *)emails toEventID:(NSString *)eID handler:(MDAPIBoolHandler)handler;
- (MDURLConnection *)deleteUserWithUserIDs:(NSArray *)uIDs emails:(NSArray *)emails fromEventID:(NSString *)eID handler:(MDAPIBoolHandler)handler;
- (MDURLConnection *)reinviteUserWithUserIDs:(NSArray *)uIDs emails:(NSArray *)emails toEventID:(NSString *)eID handler:(MDAPIBoolHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 按需求获取日程列表
 @parmas:
 year - 日期年数字。默认值为当前年。如：2013 Int，最大值9999，最小值2000
 week - 某年第几周数。默认值为当前日期周数 Int，最大值54，最小值1
 yearAndMonth - 日期字符串。默认值为本月。如：2013-05。
 yearMonthAndDay - date	false	string	日期字符串。默认值为今天。如：2013-05-05。
 handler - 处理包含多个MDEvent的NSArray
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadEvents:(MDAPINSArrayHandler)handler;
- (MDURLConnection *)loadEventsForDay:(NSString *)yearMonthAndDay handler:(MDAPINSArrayHandler)handler;
- (MDURLConnection *)loadEventsForWeek:(NSInteger)week year:(NSInteger)year handler:(MDAPINSArrayHandler)handler;
- (MDURLConnection *)loadEventsForMonth:(NSString *)yearAndMonth handler:(MDAPINSArrayHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 根据日程编号获取单条日程内容
 @parmas:
 objectID - 日程编号
 handler - 处理MDEvent
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadEventWithObjectID:(NSString *)objectID handler:(MDAPIObjectHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 删除/接受/拒绝/退出日程
 @parmas:
 objectID - 日程编号
 handler - 处理结果
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)deleteEventWithObjectID:(NSString *)objectID handler:(MDAPIBoolHandler)handler;
- (MDURLConnection *)exitEventWithObjectID:(NSString *)objectID handler:(MDAPIBoolHandler)handler;
- (MDURLConnection *)acceptEventWithObjectID:(NSString *)objectID handler:(MDAPIBoolHandler)handler;
- (MDURLConnection *)rejectEventWithObjectID:(NSString *)objectID handler:(MDAPIBoolHandler)handler;

#pragma mark - 任务接口

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 获取当前登录用户参与/参与且已完成/托付/托付且已完成/负责/负责且已完成的任务列表
 @parmas:
 keywords - 任务中包含的关键词
 allOrUnfinished  - YES加载全部任务 NO加载未完成的任务
 size - 没次加载获取的任务书
 page - 任务所在页数
 handler - 包含多个MDTask的NSArray
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadCurrentUserJoinedTasksWithKeywords:(NSString *)keywords allOrUnfinished:(BOOL)allOrUnFinished handler:(MDAPINSArrayHandler)handler;
- (MDURLConnection *)loadCurrentUserJoinedFinishedTasksWithPageSize:(NSInteger)size
                                                         page:(NSInteger)page
                                                      handler:(MDAPINSArrayHandler)handler;

- (MDURLConnection *)loadCurrentUserAssignedTasksWithKeywords:(NSString *)keywords allOrUnfinished:(BOOL)allOrUnFinished handler:(MDAPINSArrayHandler)handler;
- (MDURLConnection *)loadCurrentUserAssignedFinishedTasksWithPageSize:(NSInteger)size
                                                         page:(NSInteger)page
                                                      handler:(MDAPINSArrayHandler)handler;

- (MDURLConnection *)loadCurrentUserChargedTasksWithKeywords:(NSString *)keywords allOrUnfinished:(BOOL)allOrUnFinished handler:(MDAPINSArrayHandler)handler;
- (MDURLConnection *)loadCurrentUserChargedFinishedTasksWithPageSize:(NSInteger)size
                                                         page:(NSInteger)page
                                                      handler:(MDAPINSArrayHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 获取当前网络所有任务隶属的项目
 @parmas:
 keywords - 任务中包含的关键词
 handler - 包含多个MDProject的NSArray
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadProjectsWithKeywords:(NSString *)keywords handler:(MDAPINSArrayHandler)handler;

/*-*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-
 @usage:
 根据任务编号获取单条任务内容
 @parmas:
 tID - 任务编号
 handler - 处理MDTask
 -*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*--*-*-*-*-*-*-*-*-*-*-*-*-*-*/
- (MDURLConnection *)loadTaskWithTaskID:(NSString *)tID handler:(MDAPIObjectHandler)handler;
@end