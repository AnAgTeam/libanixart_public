#import <netsess/StringTools.hpp>
#import <Foundation/Foundation.h>
#import <UIKit/UIDevice.h>

namespace anixart {
	using namespace network;

	std::string get_platform_version() {
		auto ops = [[NSProcessInfo processInfo] operatingSystemVersion];
		return StringTools::snformat("%d.%d", ops.majorVersion, ops.minorVersion);
	}

	std::string get_product_model() {
		NSString* model = [[UIDevice currentDevice] name];
		return std::string([model UTF8String], [model lengthOfBytesUsingEncoding:NSUTF8StringEncoding]);
	}
	
};
