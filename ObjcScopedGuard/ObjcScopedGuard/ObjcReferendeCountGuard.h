#import <Foundation/Foundation.h>
#include <ObjcScopedGuard/ObjcGuardBlocks.h>



/**
 A C++ class to dispose raw resources using ARC. The resource disposal block will be invoked in the [ObjcReferendeCountGuard dealloc] method.
 
  If you are using legacy garbage collection, resource disposal will happen once the object is released either manually or by the autorelease pool.
 
 
 By raw resources we mean :
 
 * CoreFoundation objects that do not support bridge casting
 * GCD primitives that require dispatch_release() call
 * Pure C API
 * File IO
 * BSD sockets
 * etc.
 
 This class does not support NSCopying protocol.
 */
@interface ObjcReferendeCountGuard : NSObject


/**
 Unsupported initializer
 
 @return Never happens. An exception is thrown.
 */
-(instancetype)init __attribute__(( noreturn, unavailable("Not supported initializer") ));

/**
 Unsupported initializer
 
 @return Never happens. An exception is thrown.
 */
+(instancetype)new  __attribute__(( noreturn, unavailable("Not supported initializer") ));

/**
 Initializes a guard object with the guard disposal block.
 
 @param block_ A user defined block that performs resource cleanup.
 
 @return A properly initialized object.
 */
-(instancetype)initWithBlock:( GuardCallbackBlock )block_ __attribute__(( nonnull ));

/**
 Tells the guard object to not run the guard disposal block.
 
 This method should be invoked in case you have disposed the resource manually.
 Otherwise you'll eventually get an over-release crash.
 */
-(void)releaseGuard;


/**
 Deallocates the memory occupied by the receiver. Also it calls the resource disposal block unless the [ObjcReferendeCountGuard releaseGuard] has been executed.
 */
-(void)dealloc;

@end
