## What is ObjcScopedGuard ?
It is a class in ObjectiveC++ that uses blocks to release resources.
A scoped guard executes the block in its C++ destructor and ensures correct resource management even if an exception has been thrown.

This class introduces the RAII idiom to the world of iOS developers.

```
License : BSD
```


## Why ObjcScopedGuard ?
Correct manuall resource handling resources is a hard work and is the main source of bugs.

```c
using namespace ::std;

void bad(const char* p)
{
    FILE* fh = fopen(p,"r"); // acquire
	
	
	// use f
	if ( someCondition )
	{
	    // Oops! Looks like we are missing the fclose() statement and leaking the resource
	    return;
	}
		
	f(); // OOPS! Exceptions can be thrown.
	fclose(fh); // release
    cout << "fclose() called" << endl;
}
```

The scoped guard idiom can be treated as an **autorelease** or **@autoreleasepool** statement for low level resources. Unlike **autorelease** the resource is disposed **at the moment the function exits**. Moreover, it works both for **return** and for **@throw exteption** cases. 

```
The ObjcScopedGuard class uses Objective-C blocks for easiy integration with existing legacy code.
```



## How to use ObjcScopedGuard ?
This class should be used to dispose resources that are not managed by ARC including :

1. **File** and **stream** handles
2. **dispatch_source_t** instances
3. ** sqlite3 ** handles
4. CoreFoundation objects (those disposed by **CFRelease**)


The code from the previous section can be rewritten in the resource safe and scalable manner :

```objective-c
using namespace ::std;
using namespace ::Utils;

void good(const char* p)
{
   FILE* fh = fopen(p,"r"); // acquire
	
	// the block to perform cleanup actions
    GuardCallbackBlock releaseBlock_ = ^void( void )
    {
       cout << "fclose() called" << endl;
       ::fclose( fh ); // release
    };
	
	// creating a guard
	ObjcScopedGuard guard( releaseBlock_ );
	
	// use f
	if ( someCondition )
	{
	    // Now the scoped guard will release the resource
	    return;
	}
		
	f(); // OOPS! Exceptions can be thrown.


	// Fclose should not be called explicitly since the 
    /*
	fclose(fh); // release
    cout << "fclose() called" << endl;
    */
}
```


## One More Thing...
Sometimes objects should live longer than the function scope and integrated with the **Cocoa autoreleasepool system**. Meaning, it should be possible to **retain** and **release** the guard. The ```ObjcReferendeCountGuard``` class which is a part of this library solves the mentioned problem.


```objective-c
using namespace ::std;
using namespace ::Utils;

void good_retain_release(const char* p, id<GuardHolderProtocol> guardHolder)
{
   FILE* fh = fopen(p,"r"); // acquire

	
	// the block to perform cleanup actions
    GuardCallbackBlock releaseBlock_ = ^void( void )
    {
       cout << "fclose() called" << endl;
       ::fclose( fh ); // release
    };


	// creating a guard and storing a strong reference to it
	guardHolder.guard = [ [ ObjcReferendeCountGuard alloc ] initWithBlock: releaseBlock_ ];	
	
	// use f
	if ( someCondition )
	{
	    // Now the scoped guard will release the resource
	    return;
	}
		
	f(); // OOPS! Exceptions can be thrown.


	// Fclose should not be called explicitly since the 
    /*
	fclose(fh); // release
    cout << "fclose() called" << endl;
    */
}
```




## Bibliography
Some [code examples](http://ideone.com/enqHPr) have been taken from the "Resource Acquisition is Initialization" [presentation](http://www.slideshare.net/adankevich/raii-and-scopeguard) by Andrey Dankevich.

[![Bitdeli Badge](https://d2weczhvl823v0.cloudfront.net/dodikk/objcscopedguard/trend.png)](https://bitdeli.com/free "Bitdeli Badge")

