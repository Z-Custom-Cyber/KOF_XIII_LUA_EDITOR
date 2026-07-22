#include "transFunction.h"
#include "uuidGenerate.h"

int main() {
    FileEncoder encoder;

    int operation;
    int uuid_count;
    std::string fileName;

    while (true) {
        std::cout << DEVICE_NAME;
        std::cout << MSG_DEVICE_REQUEST;
        encoder.deviceCode = OPERATION_EXIT;
        std::cin >> encoder.deviceCode;
        if (   encoder.deviceCode != DEVICE_PC 
            && encoder.deviceCode != DEVICE_NS
            && encoder.deviceCode != OPERATION_EXIT) {
            std::cerr << MSG_DEVICE_CODE_ERROR << std::endl;
            continue;
        }
        if (encoder.deviceCode == OPERATION_EXIT) break;

        while (true) {
            std::cout << START_SYMBOL;
            std::cout << OPERATION_MENU;
            std::cout << MSG_OPERATION_REQUEST;
            std::cin >> operation;

            if (operation != OPERATION_EXIT
                && operation != OPERATION_DECODE
                && operation != OPERATION_ENCODE
                && operation != OPERATION_BAK_CLEAR
                && operation != OPERATION_UUID) {
                std::cerr << MSG_VALID_TYPE_ERROR << std::endl;
                continue;
            }

            if (operation == OPERATION_EXIT) {
                break;
            }

            if (operation == OPERATION_UUID) {
                std::cout << MSG_GUID_REQUEST;
                std::cin >> uuid_count;
                std::cout << std::endl;
                for (int i = 0; i < uuid_count; i++) {
                    std::cout << generate_uuid_v4() << std::endl;
                }
            }

            if (operation != OPERATION_BAK_CLEAR && operation != OPERATION_UUID) {
                std::cout << MSG_FILE_REQUEST;
                std::cin >> fileName;
            }

            if (encoder.processFile(fileName, operation)) {
                encoder.fileBackup();
                std::cout << MSG_OPERATION_SUCCESS << std::endl;
            }
            else {
                std::cout << MSG_OPERATION_FAILED << std::endl;
            }

            encoder.memberInit();
            operation = 0;
            uuid_count = 0;
            std::cout << END_SYMBOL;

            //以防万一
            if (encoder.deviceCode == 0) break;
        }
    }
    return 0;
}