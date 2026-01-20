#include <iostream>
#include <string>
#include <Windows.h>
// 编译时自动链接Rpcrt4.lib，VS/MinGW都支持
#pragma comment(lib, "Rpcrt4.lib")

// 封装UUID生成函数：返回标准小写UUID V4字符串
std::string generate_uuid_v4();
