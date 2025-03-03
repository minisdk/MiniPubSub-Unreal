#import "MiniPubSub/ObjcSide.h"
#import "MiniPubSub/MiniPubSub-Swift.h"

using iOSNativeCallback = void (*)(const char* infoCStr, const char* dataCStr);
extern "C"
{
    void Initialize(iOSNativeCallback NativeCallback)
    {
        [[ObjcSide sharedInstance] initializeWith:NativeCallback];
    }
    void SendNative(const char* Info, const char* Json)
    {
        [[ObjcSide sharedInstance] sendToNativeWithInfo:Info AndData: Json];
    }
}