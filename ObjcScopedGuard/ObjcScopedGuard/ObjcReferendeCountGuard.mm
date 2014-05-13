#import "ObjcReferendeCountGuard.h"
#import "ObjcScopedGuard.h"

using namespace ::Utils;

@implementation ObjcReferendeCountGuard
{
@private
    GuardCallbackBlock _block;
    BOOL _isActive;
}

-(void)dealloc
{
    if ( !self->_isActive )
    {
        return;
    }

    ObjcScopedGuard::SafeInvokeGuardBlock( self->_block );
}

-(instancetype)init
{
    [ self doesNotRecognizeSelector: _cmd ];
    return nil;
}

+(instancetype)new
{
    [ self doesNotRecognizeSelector: _cmd ];
    return nil;
}


-(instancetype)initWithBlock:( GuardCallbackBlock )block_
{
    NSParameterAssert( nil != block_ );

    self = [ super init ];
    if ( nil == self )
    {
        return nil;
    }
    
    self->_block = [ block_ copy ];
    self->_isActive = YES;

    return self;
}

-(void)releaseGuard
{
    self->_isActive = NO;
}

@end
