#import "ObjcScopedGuard.h"

using namespace ::Utils;

void ObjcScopedGuard::SafeInvokeGuardBlock(GuardCallbackBlock callback_) throw()
{
    if ( nil == callback_ )
    {
        return;
    }

    
    try
    {
        @try
        {
            callback_();
        }
        @catch ( NSException* exception )
        {
            NSLog( @"[ObjcScopedGuard] Obj-C exception in guard block : %@",  exception );
        }
        @finally
        {
            // IDLE
        }
    }
    catch (const std::exception& ex)
    {
        NSLog( @"[ObjcScopedGuard] C++ exception in guard block : %s",  ex.what() );
    }
    catch (...)
    {
        NSLog( @"[ObjcScopedGuard] Unknown C++ exception in guard block" );
    }

}

ObjcScopedGuard::ObjcScopedGuard( GuardCallbackBlock callback_ ) : 
    _block( [ callback_ copy ] ),
    _isActive( true )
{
}

ObjcScopedGuard::~ObjcScopedGuard() throw()
{
    if ( !this->_isActive )
    {
        return;
    }
    
    ObjcScopedGuard::SafeInvokeGuardBlock( this->_block );
}

void ObjcScopedGuard::Release() throw()
{
    this->_isActive = false;
    this->_block    = nil;
}

