#pragma once

#if PLATFORM_IOS
#import "MiniPubSub/ObjcSide.h"

extern "C" {
	void __iOSInitialize(NativeMessageCallback messageCallback);
	void __iOSSend(const char* infoCStr, const char* dataCStr);
}
#endif