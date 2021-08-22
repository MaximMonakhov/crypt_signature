using System;
using MonoTouch.ObjCRuntime;

[assembly: LinkWith ("/Users/kristofer/Desktop/Project/crypt_signature/ios/libCPROCSP.a", Frameworks="CoreGraphics UIKit Foundation ExternalAccessory", LinkTarget = LinkTarget.ArmV7 | LinkTarget.Simulator,  IsCxx = true,  ForceLoad = true, LinkerFlags = "-lz -liconv -lstdc++ -all_rolad")]