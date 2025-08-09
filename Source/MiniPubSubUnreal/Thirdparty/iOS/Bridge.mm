#import "sample/sample-Swift.h"

extern "C"
{
    void Load()
    {
        [[SampleKit shared] prepare];
    }
}