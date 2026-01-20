#ifndef MACRO_DEFINE_H
#define LANGUAGE_EN

#define MAP_SIZE 16
#define LIMIT_SIZE 20971520
#define OFFSET 4
#define MASK_CODE 0x0F

#define OPERATION_EXIT   0
#define OPERATION_DECODE 1
#define OPERATION_ENCODE 2
#define OPERATION_BAK_CLEAR 3
#define OPERATION_UUID 4

#ifdef LANGUAGE_CN
	#define START_SYMBOL "---- 开始 -----------------------------------------------------\n"
	#define OPERATION_MENU "选择操作类型 :\n    [1]:解码\n    [2]:加密\n    [3]:清理备份\n    [4]:生成GUIDs\n    [0]:退出\n"
	#define END_SYMBOL "---- 结束 -----------------------------------------------------\n"
	
	#define MSG_LUAC_COMPILE_ERROR "error: 该明文文件不存在 - "
	#define MSG_PLAINTEXT_ERROR "error: 该加密文件不存在 - "
	#define MSG_SOURCE_FILE_ERROR "error: 该文件不存在 - "
	#define MSG_OVERSIZE_ERROR "error: 文件大小超过了 20MB"
	#define MSG_OUTPUT_OPEN_ERROR "error: 无法打开输出文件 - "
	#define MSG_OUTPUT_CREAT_ERROR "error: 无法创建输出文件 - "
	#define MSG_OPERATION_ERROE "error: 操作类型错误"
	#define MSG_BACKUP_CLEAR_ERROR "error: 备份清理失败: "
	#define MSG_VALID_TYPE_ERROR "error: 非法的操作类型"
	#define MSG_JAR_EXECUTE_ERROR "jar 执行失败，返回值: "
	#define MSG_LUAC_EXECUTE_ERROR "luac 执行失败，返回值: "
	#define MSG_OPERATION_FAILED "\n 操作失败!"
	
	#define MSG_DECODE_SUCCESS "解码成功!"
	#define MSG_ENCODE_SUCCESS "加密成功!"
	#define MSG_JAR_EXECUTE_SUCCESS "jar 执行成功!" 
	#define MSG_LUAC_EXECUTE_SUCCESS "luac 执行成功!"
	#define MSG_OPERATION_SUCCESS "\n 操作成功!"
	
	#define MSG_BACKUP_CLEAR_SUCCESS "备份清理完成: "
	#define MSG_GUID_REQUEST "需要生成几组GUID: "
	#define MSG_FILE_REQUEST "请输入文件名: "
	#define MSG_INPUT "目标文件: "
	#define MSG_OUTPUT "输出文件: "
#endif
#ifdef LANGUAGE_EN
	#define START_SYMBOL "---- START -----------------------------------------------------\n"
	#define OPERATION_MENU "select operation type :\n    [1]:Decode\n    [2]:Encode\n    [3]:Backup_clear\n    [4]:GUIDs_generate\n    [0]:Exit\n"
	#define END_SYMBOL "---- END -------------------------------------------------------\n"
	
	#define MSG_LUAC_COMPILE_ERROR "error: plaintext input file is not exists - "
	#define MSG_PLAINTEXT_ERROR "error: encode input file is not exists - "
	#define MSG_SOURCE_FILE_ERROR "error: input file is not exists - "
	#define MSG_OVERSIZE_ERROR "error: file is too big more than 20MB"
	#define MSG_OUTPUT_OPEN_ERROR "error: can not open output file - "
	#define MSG_OUTPUT_CREAT_ERROR "error: can not create output file - "
	#define MSG_OPERATION_ERROE "error: operation type error"
	#define MSG_BACKUP_CLEAR_ERROR "error: backup clear failed: "
	#define MSG_VALID_TYPE_ERROR "error: valid type"
	#define MSG_JAR_EXECUTE_ERROR "jar execute failed，result code: "
	#define MSG_LUAC_EXECUTE_ERROR "luac execute failed，result code:"
	#define MSG_OPERATION_FAILED "\n operation failed!"
	
	#define MSG_DECODE_SUCCESS "decode complete!"
	#define MSG_ENCODE_SUCCESS "encode complete!"
	#define MSG_JAR_EXECUTE_SUCCESS "jar execute success" 
	#define MSG_LUAC_EXECUTE_SUCCESS "luac execute success"
	#define MSG_OPERATION_SUCCESS "\n operation success!"
	
	#define MSG_BACKUP_CLEAR_SUCCESS "backup cleared: "
	#define MSG_GUID_REQUEST "How many GUIDs you want: "
	#define MSG_FILE_REQUEST "input file name: "
	#define MSG_INPUT "input: "
	#define MSG_OUTPUT "output: "
#endif

#define OPERATION_NAME_DECODE "DECODE"
#define OPERATION_NAME_ENCODE "ENCODE"
#define ENCODE_PATH ".\\1_ENCODE\\"
#define ENCODE_PATH_BAK ".\\1_ENCODE\\BAK\\"
#define DECODE_PATH ".\\2_DECODE\\"
#define DECODE_PATH_BAK ".\\2_DECODE\\"
#define PLAINTEXT_PATH ".\\3_PLAINTEXT\\"
#define PLAINTEXT_PATH_BAK ".\\3_PLAINTEXT\\BAK\\"
#define JAR_PATH "java -jar .\\compiler\\unluac.jar "
#define LUAC_PATH ".\\compiler\\luac_32.exe -o "
#endif // !MACRO_DEFINE_H
