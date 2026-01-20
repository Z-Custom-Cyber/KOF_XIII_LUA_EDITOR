#ifndef TRANSFUNCTION_H
#define TRANSFUNCTION_H

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <filesystem>
#include <cstdlib>
#include <chrono>
#include <iomanip>
#include "macroDefine.h"

namespace fs = std::filesystem;

class FileEncoder {
private:
    // 转码映射表
    static const unsigned char codeMap[MAP_SIZE];
    // 获取转码后的值
    unsigned char transformByte(unsigned char byte, const unsigned char map[MAP_SIZE]);

    bool jarExcute();
    bool luaExcute();
    bool fileExistsCheck(const std::string& inPath, std::string msg);
    bool backupClear();
    bool pathPrepare();
    void pathEdit();
    void pathLstSet();
    bool operationCheck(int operationType);
    std::string getCurrentTimestamp();

    std::vector<fs::path> pathList;
    std::vector<fs::path> backPathList;
    bool isUnlock;
    std::string encodePath;
    std::string decodePath;
    std::string plaintextPath;
    std::string inputPath;
    std::string outputPath;
    std::string inputPTextPath;
    std::string outputPTextPath;
    std::string timestamp;
    std::string encodeBakpath;
    std::string plaintextBakpath;
    std::string fileNm;
public:
    FileEncoder();
    void memberInit();
    bool fileBackup();
    bool processFile(const std::string& filename, int isUnlock);
};

// 转码映射表
const unsigned char FileEncoder::codeMap[MAP_SIZE] = {
    6, 7, 4, 5, 2, 3, 0, 1, 14, 15, 12, 13, 10, 11, 8, 9
};

FileEncoder::FileEncoder() {
    memberInit();
    pathPrepare();
}

unsigned char FileEncoder::transformByte(unsigned char byte, const unsigned char map[MAP_SIZE]) {
    unsigned char high = (byte >> OFFSET) & MASK_CODE;
    unsigned char low = byte & MASK_CODE;

    high = map[high];
    low = map[low];

    return (high << 4) | low;
}

bool FileEncoder::processFile(const std::string& filename, int operationType) {
    
    if(!operationCheck(operationType)) return false;
    if (operationType == OPERATION_BAK_CLEAR) return backupClear();
    if (operationType == OPERATION_UUID) return true;

    fileNm = filename;

    pathEdit();
    // 重新加密
    if (!luaExcute()) return false;

    // 检查输入文件是否存在
    if (!fileExistsCheck(inputPath, MSG_SOURCE_FILE_ERROR)) return false;

    // 检查输入文件大小
    std::ifstream inputFile(inputPath, std::ios::binary | std::ios::ate);
    std::streamsize fileSize = inputFile.tellg();
    inputFile.close();

    if (fileSize > LIMIT_SIZE) { // 20MB限制
        std::cerr << MSG_OVERSIZE_ERROR << std::endl;
        return false;
    }

    // 读取输入文件
    std::ifstream fin(inputPath, std::ios::binary);
    if (!fin) {
        std::cerr << MSG_OUTPUT_OPEN_ERROR << inputPath << std::endl;
        return false;
    }

    std::vector<unsigned char> data(fileSize);
    fin.read(reinterpret_cast<char*>(data.data()), fileSize);
    fin.close();

    // 执行转码操作
    for (auto& byte : data) {
        byte = transformByte(byte, codeMap);
    }

    // 写入输出文件
    std::ofstream fout(outputPath, std::ios::binary);
    if (!fout) {
        std::cerr << MSG_OUTPUT_CREAT_ERROR << outputPath << std::endl;
        return false;
    }

    fout.write(reinterpret_cast<const char*>(data.data()), fileSize);
    fout.close();

    std::string msg = isUnlock ? MSG_DECODE_SUCCESS : MSG_ENCODE_SUCCESS;
    std::cout << msg << std::endl;
    std::cout << MSG_INPUT << inputPath  << std::endl;
    std::cout << MSG_OUTPUT << outputPath << std::endl;

    // 解码
    if(!jarExcute()) return false; 
    return true;
}

bool FileEncoder::jarExcute() {
    if (!isUnlock) return true;
    if (!fileExistsCheck(inputPTextPath, MSG_PLAINTEXT_ERROR)) return false;

    std::string command;
    command = std::string(JAR_PATH) + inputPTextPath + " > " + outputPTextPath;

    // 执行命令
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << MSG_JAR_EXECUTE_SUCCESS << std::endl;
    }
    else {
        std::cout << MSG_JAR_EXECUTE_ERROR << result << std::endl;
        return false;
    }
    return true;
}

bool FileEncoder::luaExcute() {
    if(isUnlock) return true;
    if (!fileExistsCheck(inputPTextPath, MSG_LUAC_COMPILE_ERROR)) return false;

    std::string command;
    command = std::string(LUAC_PATH) + outputPTextPath + " " + inputPTextPath;

    // 执行命令
    int result = system(command.c_str());

    if (result == 0) {
        std::cout << MSG_LUAC_EXECUTE_SUCCESS << std::endl;
    }
    else {
        std::cout << MSG_LUAC_EXECUTE_ERROR << result << std::endl;
        return false;
    }
    return true;
}

bool FileEncoder::fileExistsCheck(const std::string& inPath, std::string msg) {
    if (!fs::exists(inPath)) {
        std::cerr << msg << inPath << std::endl;
        return false;
    }
    return true;
}

bool FileEncoder::fileBackup() {
    if (fs::exists(encodePath)) {
        fs::copy_file(encodePath, encodeBakpath, fs::copy_options::overwrite_existing);
    }
    if (fs::exists(plaintextPath)) {
        fs::copy_file(plaintextPath, plaintextBakpath, fs::copy_options::overwrite_existing);
    }
    return true;
}

bool FileEncoder::backupClear() {
    try {
        for (int i = 0; i < backPathList.size(); i++) {
            fs::path dirPath = backPathList[i];

            if (fs::is_regular_file(dirPath) || fs::is_symlink(dirPath)) {
                fs::remove(dirPath);
            }
            else if (fs::is_directory(dirPath)) {
                fs::remove_all(dirPath);
            }
            std::cout << MSG_BACKUP_CLEAR_SUCCESS << dirPath << std::endl;
        }
        pathPrepare();
        return true;
    }
    catch (const fs::filesystem_error& e) {
        std::cerr << MSG_BACKUP_CLEAR_ERROR << e.what() << std::endl;
        return false;
    }
    return true;
}

bool FileEncoder::pathPrepare() {
    for (int i = 0; i < pathList.size(); i++) {
        if (!fs::exists(pathList[i])) {
            fs::create_directories(pathList[i]);
        }
        if (!fs::exists(backPathList[i])) {
            fs::create_directories(backPathList[i]);
        }
    }
    return true;
}

bool FileEncoder::operationCheck(int operationType) {
    switch (operationType) {
    case OPERATION_DECODE:
        isUnlock = true;
        break;
    case OPERATION_ENCODE:
        isUnlock = false;
        break;
    case OPERATION_BAK_CLEAR:
    case OPERATION_UUID:
        break;
    default:
        std::cerr << MSG_OPERATION_ERROE << std::endl;
        return false;
    }
    return true;
}

void FileEncoder::pathEdit() {
    std::string opr;

    encodePath = ENCODE_PATH + fileNm;
    decodePath = DECODE_PATH + fileNm;
    plaintextPath = PLAINTEXT_PATH + fileNm;

    inputPath = isUnlock ? encodePath : decodePath;
    outputPath = isUnlock ? decodePath : encodePath;
    inputPTextPath = isUnlock ? decodePath : plaintextPath;
    outputPTextPath = isUnlock ? plaintextPath : decodePath;
    opr = isUnlock ? OPERATION_NAME_DECODE : OPERATION_NAME_ENCODE;

    timestamp = getCurrentTimestamp();
    encodeBakpath = ENCODE_PATH_BAK + timestamp + "_" + opr + "_" + fileNm;
    plaintextBakpath = PLAINTEXT_PATH_BAK + timestamp + "_" + opr + "_" + fileNm;
}
void FileEncoder::memberInit() {
    isUnlock = false;

    encodePath.clear();
    decodePath.clear();
    plaintextPath.clear();
    pathList.clear();
    backPathList.clear();
    inputPath.clear();
    outputPath.clear();
    inputPTextPath.clear();
    outputPTextPath.clear();
    timestamp.clear();
    encodeBakpath.clear();
    plaintextBakpath.clear();
    fileNm.clear();

    pathLstSet();
}

std::string FileEncoder::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    std::tm tm;
    localtime_s(&tm, &time_t);
    std::ostringstream oss;
    oss << std::put_time(&tm, "%Y%m%d_%H%M%S");
    return oss.str();
}

void FileEncoder::pathLstSet() {
    fs::path encodPathObj(ENCODE_PATH);
    fs::path decodPathObj(DECODE_PATH);
    fs::path plainTextPathObj(PLAINTEXT_PATH);
    fs::path encodePathBakObj(ENCODE_PATH_BAK);
    fs::path decodePathBakObj(DECODE_PATH_BAK);
    fs::path plainTextPathBakObj(PLAINTEXT_PATH_BAK);

    pathList.push_back(encodPathObj);
    pathList.push_back(decodPathObj);
    pathList.push_back(plainTextPathObj);
    backPathList.push_back(encodePathBakObj);
    backPathList.push_back(decodePathBakObj);
    backPathList.push_back(plainTextPathBakObj);
}
#endif