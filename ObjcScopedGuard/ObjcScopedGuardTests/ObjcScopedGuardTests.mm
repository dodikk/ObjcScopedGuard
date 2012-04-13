#import "ObjcScopedGuardTests.h"
#import "ObjcScopedGuard.h"

using namespace ::Utils;

@implementation ObjcScopedGuardTests

-(void)testScopedGuard
{
   __block BOOL resourceAcquired_ = YES;
   GuardCallbackBlock releaseBlock_ = ^
   {
      resourceAcquired_ = NO;
   };
   
   ObjcScopedGuard* guardPtr_ = new ObjcScopedGuard( releaseBlock_ );
   STAssertTrue( resourceAcquired_, @"Guard creation must not release the resource" );
   
   delete guardPtr_;
   STAssertFalse( resourceAcquired_, @"Guard destruction must release the resource" );
}

@end
