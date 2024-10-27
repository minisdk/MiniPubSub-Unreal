#if PLATFORM_IOS
#include "iOSNativeBridge.h"

extern "C" void __iOSInitialize(NativeMessageCallback messageCallback)
{
	[[ObjcSide sharedInstance] initializeWith:messageCallback];
}

extern "C" void __iOSSend(const char* infoCStr, const char* dataCStr)
{
    [[ObjcSide sharedInstance] sendToNativeWithInfo:infoCStr AndData: dataCStr];
}
#endif
