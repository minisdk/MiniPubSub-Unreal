using System;
using System.IO;
using UnrealBuildTool;

public class MiniPubSubNative : ModuleRules
{
    public MiniPubSubNative(ReadOnlyTargetRules Target) : base(Target)
    {
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(
            new string[]
            {
                "Core"
            }
        );

        PrivateDependencyModuleNames.AddRange(
            new string[]
            {
                "CoreUObject",
                "Engine",
                "Slate",
                "SlateCore",
                "MiniPubSub",
                "Json",
                "JsonUtilities"
            }
        );
        
        if(Target.Platform == UnrealTargetPlatform.Android)
        {
            string uplPath = Path.Combine(ModuleDirectory, "MiniPubSubNative_Android_UPL.xml");
            Console.WriteLine("upl file path : " + uplPath);
            Console.WriteLine("upl file exist? " + File.Exists(uplPath));
            AdditionalPropertiesForReceipt.Add("AndroidPlugin", uplPath);
        }
        else if (Target.Platform == UnrealTargetPlatform.IOS)
        {
            PublicSystemLibraryPaths.Add("/usr/lib/swift");
            PublicSystemLibraryPaths.Add("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift/iphoneos");
            PublicSystemLibraryPaths.Add("/Applications/Xcode.app/Contents/Developer/Toolchains/XcodeDefault.xctoolchain/usr/lib/swift-5.0/iphoneos");
			
            const string frameworkName = "Thirdparty/iOS/MiniPubSub.framework";
            string frameworkPath = Path.Combine(ModuleDirectory, frameworkName);
            PublicAdditionalFrameworks.Add(new Framework("MiniPubSub", frameworkPath));
        }
    }
}