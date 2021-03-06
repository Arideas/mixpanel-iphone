//
// Mixpanel.h
// Mixpanel
//
// Copyright 2012 Mixpanel
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

@class    MixpanelPeople;
@protocol MixpanelDelegate;

/*!
 @class
 Mixpanel API.
 
 @abstract
 The primary interface for integrating Mixpanel with your app.
 
 @discussion
 Use the Mixpanel class to set up your project and track events in Mixpanel
 Engagement. It now also includes a <code>people</code> property for accesseing
 the Mixpanel People API.
 
 <pre>
 // Initialize the API
 Mixpanel *mixpanel = [Mixpanel sharedInstanceWithToken:@"YOUR API TOKEN"];
 
 // Track an event in Mixpanel Engagement
 [mixpanel track:@"Button Clicked"];
 
 // Set properties on a user in Mixpanel People
 [mixpanel.people identify:@"CURRENT USER DISTINCT ID"];
 [mixpanel.people set:@"Plan" to:@"Premium"];
 </pre>

 For more advanced usage, please see the <a
 href="https://mixpanel.com/docs/integration-libraries/iphone">Mixpanel iPhone
 Library Guide</a>.
 */
@interface Mixpanel : NSObject

/*!
 @property
 
 @abstract
 Accessor to the Mixpanel People API object.
 
 @discussion
 See the documentation for MixpanelDelegate below for more information.
 */
@property(nonatomic,readonly,retain) MixpanelPeople *people;

/*!
 @property
 
 @abstract
 Gets and sets the distinct ID of the current user.
 
 @discussion
 A distinct ID is a string that uniquely identifies one of your users.
 Typically, this is the user ID from your database. By default, we'll use a
 hash of the MAC address of the device.
 */
@property(nonatomic,setter=identify:,copy) NSString *distinctId;

/*!
 @property
 
 @abstract
 Gets and sets the current user's name in Mixpanel Streams.
 */
@property(nonatomic,copy) NSString *nameTag;

/*!
 @property
 
 @abstract
 Gets and sets the base URL used for Mixpanel API requests.
 
 @discussion
 Useful if you need to proxy Mixpanel requests. Defaults to 
 https://api.mixpanel.com.
 */
@property(nonatomic,copy) NSString *serverURL;

/*!
 @property
 
 @abstract
 Gets and sets the flush timer's interval.
 
 @discussion
 Setting a flush interval of 0 will turn off the flush timer.
 */
@property(nonatomic,assign) NSUInteger flushInterval;

/*!
 @property

 @abstract
 Control whether the library should flush data to Mixpanel when the app
 enters the background.

 @discussion
 Defaults to YES. Only affects apps targeted at iOS 4.0, when background 
 task support was introduced, and later.
 */
@property(nonatomic,assign) BOOL flushOnBackground;

/*!
 @property

 @abstract
 Controls whether to show spinning network activity indicator when flushing data to the Mixpanel servers.

 @discussion
 Defaults to YES.
 */
@property(nonatomic,assign) BOOL showNetworkActivityIndicator;

/*!
 @property
 
 @abstract
 Gets and sets the a MixpanelDelegate object that can be used to assert
 fine-grain control over Mixpanel network activity.
 
 @discussion
 Using a delegate is optional. See the documentation for MixpanelDelegate 
 below for more information.
 */
@property(nonatomic,assign) id<MixpanelDelegate> delegate; // allows fine grain control over uploading (optional)

/*!
 @method
 
 @abstract
 Initializes and returns a singleton instance of the API.
 
 @discussion
 If you are only going to send data to a single Mixpanel project from your app,
 as is the common case, then this is the easiest way to use the API. This
 method will set up a singleton instance of the <code>Mixpanel</code> class for
 you using the given project token. When you want to make calls to Mixpanel
 elsewhere in your code, you can use <code>sharedInstance</code>.
 
 <pre>
 [Mixpanel sharedInstance] track:@"Something Happened"]];
 </pre>
 
 If you are going to use this singleton approach,
 <code>sharedInstanceWithToken:</code> <b>must be the first call</b> to the
 <code>Mixpanel</code> class, since it performs important initializations to
 the API.
 
 @param apiToken        your project token
 */
+ (id)sharedInstanceWithToken:(NSString *)apiToken;

/*!
 @method
 
 @abstract
 Returns the previously instantiated singleton instance of the API.
 
 @discussion
 The API must be initialized with <code>sharedInstanceWithToken:</code> before
 calling this class method.
 */
+ (id)sharedInstance;

/*!
 @method
 
 @abstract
 Initializes an instance of the API with the given project token.
 
 @discussion
 Returns the a new API object. This allows you to create more than one instance
 of the API object, which is convenient if you'd like to send data to more than
 one Mixpanel project from a single app. If you only need to send data to one
 project, consider using <code>sharedInstanceWithToken:</code>.
 
 @param apiToken        your project token
 @param startFlushTimer whether to start the background flush timer
 */
- (id)initWithToken:(NSString *)apiToken andFlushInterval:(NSUInteger)flushInterval;

/*!
 @method
 
 @abstract
 Tracks an event.
 
 @param event           event name
 */
- (void)track:(NSString *)event;

/*!
 @method
 
 @abstract
 Tracks an event with properties.
 
 @discussion
 Properties will allow you to segment your events in your Mixpanel reports.
 Property keys must be <code>NSString</code> objects and values must be
 <code>NSString</code>, <code>NSNumber</code>, <code>NSNull</code>, 
 <code><NSDate</code>, <code>NSArray</code> or <code>NSDictionary</code>
 objects.
 
 @param event           event name
 @param properties      properties dictionary
 */
- (void)track:(NSString *)event properties:(NSDictionary *)properties;

/*!
 @method
 
 @abstract
 Registers super properties, overwriting ones that have already been set.
 
 @discussion
 Super properties, once registered, are automatically sent as properties for
 all event tracking calls. They save you having to maintain and add a common
 set of properties to your events.  Property keys must be <code>NSString</code> objects and values must be
 <code>NSString</code>, <code>NSNumber</code>, <code>NSNull</code>,
 <code><NSDate</code>, <code>NSArray</code> or <code>NSDictionary</code>
 objects.

 @param properties      properties dictionary
 */
- (void)registerSuperProperties:(NSDictionary *)properties;

/*!
 @method
 
 @abstract
 Registers super properties without overwriting ones that have already been
 set.
 
 @discussion
 Property keys must be <code>NSString</code> objects and values must be
 <code>NSString</code>, <code>NSNumber</code>, <code>NSNull</code>,
 <code><NSDate</code>, <code>NSArray</code> or <code>NSDictionary</code>
 objects.

 @param properties      properties dictionary
 */
- (void)registerSuperPropertiesOnce:(NSDictionary *)properties;

/*!
 @method
 
 @abstract
 Registers super properties without overwriting ones that have already been set
 unless the existing value is equal to defaultValue.
 
 @discussion
 Property keys must be <code>NSString</code> objects and values must be
 <code>NSString</code>, <code>NSNumber</code>, <code>NSNull</code>,
 <code><NSDate</code>, <code>NSArray</code> or <code>NSDictionary</code>
 objects.

 @param properties      properties dictionary
 @param defaultValue    overwrite existing properties that have this value
 */
- (void)registerSuperPropertiesOnce:(NSDictionary *)properties defaultValue:(id)defaultValue;

/*!
 @method
 
 @abstract
 Clears all currently set super properties.
 */
- (void)clearSuperProperties;

/*!
 @method

 @abstract
 Returns the currently set super properties.
 */
- (NSDictionary *)currentSuperProperties;

/*!
 @method
 
 @abstract
 Clears all stored properties and distinct IDs. Useful if your app's user logs out.
 */
- (void)reset;

/*!
 @method
 
 @abstract
 Uploads queued data to the Mixpanel server.
 
 @discussion
 This happens automatically every 60 seconds, or as specified by the
 flushInterval property. You only need to call this method manually if you want
 to force a flush at a particular moment.
 */
- (void)flush;

/*!
 @method

 @abstract
 Writes current project info, including distinct ID, super properties and pending event
 and People record queues to disk.

 @discussion
 This state will be recovered when the app is launched again if the Mixpanel library is
 initialized with the same project token. You do not need to call this method. For most
 use cases, the library listens for app state changes and handles persisting data as 
 needed. It can be useful in some special circumstances, though, for example, if you'd 
 like to track app crashes from main.m.
 */
- (void)archive;

@end

/*!
 @class
 Mixpanel People API.

 @abstract
 Access to the Mixpanel People API, available as a property on the main
 Mixpanel API.

 @discussion
 <b>You should not instantiate this object yourself.</b> An instance of it will
 be available as a property of the main Mixpanel object. Calls to Mixpanel
 People methods will look like this:
 
 <pre>
 [mixpanel.people increment:@"App Opens" by:1];
 </pre>
 
 Please note that the core <code>Mixpanel</code> and
 <code>MixpanelPeople</code> classes have separate <code>identify:<code>
 methods. The <code>Mixpanel</code> <code>identify:</code> affects the
 <code>distinct_id</code> property of events sent by <code>track:</code> and
 <code>track:properties:</code>. The <code>MixpanelPeople</code>
 <code>identify:</code> determines which Mixpanel People user record will be
 updated by <code>set:</code>, <code>increment:</code> and other
 <code>MixpanelPeople</code> methods.
 
 <b>If you are going to set your own distinct IDs for core Mixpanel event
 tracking, make sure to use the same distinct IDs when using Mixpanel
 People</b>.
 */
@interface MixpanelPeople : NSObject

/*!
 @property
 
 @abstract
 Sets the distinct ID for Mixpanel People calls.
 
 @discussion
 If calls are made to <code>set:</code>, <code>increment</code> or other
 <code>MixpanelPeople</code> methods prior to calling <code>identify:</code>,
 then they are queued up and flushed once <code>identify:</code> is called.
 
 This method only affects calls to Mixpanel People. To change the distinct ID
 of event tracking calls use the core Mixpanel @ref identify: method.
 
 A distinct ID is a string string that uniquely identifies a user. Typically,
 this is their user ID from your database.
 
 @param distinctId string that uniquely identifies the current user
 */
@property(nonatomic,setter=identify:,copy) NSString *distinctId;

/*!
 @method
 
 @abstract
 Register the given device to receive push notifications.
 
 @discussion
 This will associate the device token with the current user in Mixpanel People,
 which will allow you to send push notifications to the user from the Mixpanel
 People web interface.
 
 @param deviceToken     device token as returned <code>application:didRegisterForRemoteNotificationsWithDeviceToken:</code>
 */
- (void)addPushDeviceToken:(NSData *)deviceToken;

/*!
 @method
 
 @abstract
 Set properties on the current user in Mixpanel People.
 
 @discussion
 The properties will be set on the current user. The keys must be NSString
 objects and the values should be NSString, NSNumber, NSArray, NSDate, or
 NSNull objects. We use an NSAssert to enforce this type requirement. In
 release mode, the assert is stripped out and we will silently convert
 incorrect types to strings using [NSString stringWithFormat:@"%@", value]. You
 can override the default the current project token and distinct ID by
 including the special properties: $token and $distinct_id. If the existing
 user record on the server already has a value for a given property, the old
 value is overwritten. Other existing properties will not be affected.
 
 <pre>
 // applies to both Mixpanel Engagement track: AND Mixpanel People set: and
 // increment: calls
 [mixpanel identify:distinctId];
 
 // applies ONLY to Mixpanel People set: and increment: calls
 [mixpanel.people identify:distinctId];
 </pre>
 
 @param properties       properties dictionary
 
 */
- (void)set:(NSDictionary *)properties;

/*!
 @method
 
 @abstract
 Convenience method for setting a single property in Mixpanel People.
 
 @discussion
 Property keys must be <code>NSString</code> objects and values must be
 <code>NSString</code>, <code>NSNumber</code>, <code>NSNull</code>,
 <code><NSDate</code>, <code>NSArray</code> or <code>NSDictionary</code>
 objects.

 @param property        property name
 @param object          property value
 */
- (void)set:(NSString *)property to:(id)object;

/*!
 @method
 
 @abstract
 Increment the given numeric properties by the given values.
 
 @discussion
 Property keys must be NSString names of numeric properties. A property is
 numeric if its current value is a number. If a property does not exist, it
 will be set to the increment amount. Property values must be NSNumber objects.
 
 @param properties      properties dictionary
 */
- (void)increment:(NSDictionary *)properties;

/*!
 @method
 
 @abstract
 Convenience method for incrementing a single numeric property by the specified
 amount.

 @param property        property name
 @param amount          amount to increment by
 */
- (void)increment:(NSString *)property by:(NSNumber *)amount;

/*!
 @method
 
 @abstract
 Delete current user's record from Mixpanel People.
 */
- (void)deleteUser;

@end

/*!
 @protocol
 
 @abstract
 Delegate protocol for controlling the Mixpanel API's network behavior.
 
 @discussion
 Creating a delegate for the Mixpanel object is entirely optional. It is only
 necessary when you want full control over when data is uploaded to the server,
 beyond simply calling stop: and start: before and after a particular block of
 your code.
 */
@protocol MixpanelDelegate <NSObject>
@optional

/*!
 @method
 
 @abstract
 Asks the delegate if data should be uploaded to the server. 
 
 @discussion
 Return YES to upload now, NO to defer until later.
 
 @param mixpanel        Mixpanel API instance
 */
- (BOOL)mixpanelWillFlush:(Mixpanel *)mixpanel;

@end
