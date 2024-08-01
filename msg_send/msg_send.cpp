#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>


#include <locale>
#include <codecvt>


#include <iostream>
#include <cstdlib>

/*
int main() {
    std::string command = "mychrome.exe --Kiosk --new-window http://baidu.com";
    int result = std::system(command.c_str());
    if (result != 0) {
        std::cerr << "执行命令失败" << std::endl;
    }
    return 0;
}*/
/*
int main() {
        std::ifstream file("config.ini");  // 将 "your_file.txt" 替换为实际的文件名
        std::string line1, line2;

        if (file.is_open()) {

            std::getline(file, line1);
            std::getline(file, line2);


            file.close();
        }
        else {
            std::cerr << "无法打开文件" << std::endl;
        }

        line1 = line1 + ".exe";

        // 使用 codecvt 进行转换
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring wideStr = converter.from_bytes(line1);

        // 获取 wchar_t* 指针
        wchar_t* wcharPtr = const_cast<wchar_t*>(wideStr.c_str());



        // 使用 codecvt 进行转换
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converterurl;
        std::wstring wideStrurl = converterurl.from_bytes(line2);

        // 获取 wchar_t* 指针
        wchar_t* wcharPtrurl = const_cast<wchar_t*>(wideStrurl.c_str());




        // 启动 Chrome 并打开指定网址
        ShellExecuteW(NULL, L"open", wcharPtr, wcharPtrurl, NULL, SW_SHOWMAXIMIZED);
        //wchar_t commandLine[] = L"mychrome --Kiosk --new-window www.baidu.com";

        // 执行命令
        //ShellExecuteW(NULL, NULL, commandLine, NULL, NULL, SW_SHOWNORMAL);

        delete[] wcharPtr;
        delete[] wcharPtrurl;



        // 等待浏览器窗口出现
        HWND hwnd = NULL;
        while (hwnd == NULL) {
            hwnd = FindWindowW(L"Chrome_WidgetWin_1", NULL);

            Sleep(400);
        }

        // 模拟按下 F11 键实现全屏
        keybd_event(VK_F11, 0, 0, 0);
        keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);



        return 0;
}*/

#include <windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <memory>  // 用于智能指针

int main() {
    std::ifstream file("config.ini");  // 
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }

    std::string line1, line2;
    std::getline(file, line1);
    std::getline(file, line2);
    file.close();

    line1 = line1 + ".exe";

    // 使用 codecvt 进行转换，并使用智能指针管理内存
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::unique_ptr<wchar_t[]> wideStr = std::make_unique<wchar_t[]>(converter.from_bytes(line1).size() + 1);
    wcscpy_s(wideStr.get(), converter.from_bytes(line1).size() + 1, converter.from_bytes(line1).c_str());

    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converterurl;
    std::unique_ptr<wchar_t[]> wideStrurl = std::make_unique<wchar_t[]>(converterurl.from_bytes(line2).size() + 1);
    wcscpy_s(wideStrurl.get(), converterurl.from_bytes(line2).size() + 1, converterurl.from_bytes(line2).c_str());

    // 启动 Chrome 并打开指定网址
    ShellExecuteW(NULL, L"open", wideStr.get(), wideStrurl.get(), NULL, SW_SHOWMAXIMIZED);

    // 等待浏览器窗口出现
    HWND hwnd = NULL;
    while (hwnd == NULL) {
        hwnd = FindWindowW(L"Chrome_WidgetWin_1", NULL);
        Sleep(400);
    }

    // 模拟按下 F11 键实现全屏
    keybd_event(VK_F11, 0, 0, 0);
    keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);

    return 0;
}

