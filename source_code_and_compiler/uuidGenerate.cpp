#include "uuidGenerate.h"

// 封装UUID生成函数：返回标准小写UUID V4字符串
std::string generate_uuid_v4() {
    UUID uuid;
    // 生成原生UUID (Windows的UuidCreate就是标准UUID V4，纯随机)
    HRESULT hResult = UuidCreate(&uuid);
    if (hResult != RPC_S_OK) {
        return "generate uuid failed";
    }

    // 将UUID转为字符串格式
    RPC_CSTR uuid_str = nullptr;
    UuidToStringA(&uuid, &uuid_str);
    std::string result((char*)uuid_str);
    RpcStringFreeA(&uuid_str); // 释放内存，必须调用！

    // 转为小写（可选，Windows默认返回大写，按需转小写和你之前的格式一致）
    for (char& c : result) {
        c = tolower(c);
    }
    return result;
}
