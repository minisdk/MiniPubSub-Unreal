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
        [[ObjcSide sharedInstance] sendToNativeWithInfo:Info andData: Json];
    }
    const char* SendSyncNative(const char* Info, const char* Json)
    {
        return [[ObjcSide sharedInstance] sendSyncToNativeWithInfo: Info andData: Json];
    }
    void FreeCString(const char* ptr)
    {
        [[ObjcSide sharedInstance] freeCString: ptr];
    }
}