# KOF_XIII_LUA_EDITOR
This is a project that integrates the Lua decoding and encryption for KOF XIII, allowing you to easily modify the game's input commands. 
该工程整合了KOF XIII的Lua反编译和编译工具，让你可以简单地修改游戏指令

使用方法：
1.将游戏原版command_table.lua放到1_ENCODE文件夹中，
2.运行luaDecode_CN.exe 或者 luaDecode_EN.exe，这两个功能完全一致，只是一个英文版本，一个是中文版本
3.输入1
4.解码成功后可以在3_PLAINTEXT得到明文lua
5.修改指令
6.再次运行luaDecode_CN.exe 或者 luaDecode_EN.exe
7.输入2
8.加密成功后会将修改后地Lua覆盖到1_ENCODE中
9.将修改完成后的command_table.lua从1_ENCODE覆盖回游戏目录下
10.进入游戏体验
