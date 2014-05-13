#ifndef __ObjcScopedGuard_H__
#define __ObjcScopedGuard_H__

#include <ObjcScopedGuard/ObjcGuardBlocks.h>

namespace Utils
{
    /**
    A C++ class to dispose raw resources while leaving a current stack frame.
    
    By raw resources we mean :
    
    * CoreFoundation objects that do not support bridge casting
    * GCD primitives that require dispatch_release() call
    * Pure C API 
    * File IO
    * BSD sockets
    * etc.

    This class supports neither copying nor moving.
    It can be used both in C++11 and C++98 projects.
    */
    class ObjcScopedGuard
    {
    public:
        static void SafeInvokeGuardBlock( GuardCallbackBlock callback_ ) throw() __attribute__((nonnull));
        
    public:
        /**
         A C++ constructor.
         
         @param callback_ A block that is responsible for resource disposal. 
         It will be called in the destructor.
        */
        explicit ObjcScopedGuard( GuardCallbackBlock callback_ ) __attribute__((nonnull));

        /**
         A C++ destructor.
        */
        virtual ~ObjcScopedGuard() throw();
        
        /**
        Tells the guard object to not run the guard disposal block.
         
        This method should be invoked in case you have disposed the resource manually.
        Otherwise you'll eventually get an over-release crash.
        */
        void Release() throw();

        
    private: // move constructor is forbidden
#if __has_feature(cxx_rvalue_references)
        ObjcScopedGuard( const ObjcScopedGuard&& otherGuard_ );
        ObjcScopedGuard& operator=( const ObjcScopedGuard&& otherGuard_ );
#endif //C++ 11
        
    private: // copying is forbidden
        ObjcScopedGuard( const ObjcScopedGuard& otherGuard_ );
        ObjcScopedGuard& operator=( const ObjcScopedGuard& otherGuard_ );
        
    private:
        GuardCallbackBlock _block;
        bool _isActive;
    };
}


#endif //__ObjcScopedGuard_H__

