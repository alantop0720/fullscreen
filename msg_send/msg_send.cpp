//#define WIN32_LEAN_AND_MEAN

#include <iostream>
#include <fstream>
#include <string>
#include <locale>
#include <codecvt>
#include <cstdlib>



#include <winsock2.h>


//#include <psapi.h>
//#pragma comment(lib, "psapi.lib")
//#include <windows.h>
//#define BOOST_ASIO_NO_WIN32_LEAN_AND_MEAN
#include <boost/asio.hpp>





















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







void close() {
    HWND hwnd = NULL;
    while (hwnd == NULL) {
        hwnd = FindWindowW(L"Chrome_WidgetWin_1", NULL);
        SetForegroundWindow(hwnd);
        Sleep(1000);
    }
    // 模拟按下 Alt 键
    keybd_event(VK_MENU, 0, 0, 0);
    // 模拟按下 F4 键
    keybd_event(VK_F4, 0, 0, 0);
    // 模拟释放 F4 键
    keybd_event(VK_F4, 0, KEYEVENTF_KEYUP, 0);
    // 模拟释放 Alt 键
    keybd_event(VK_MENU, 0, KEYEVENTF_KEYUP, 0);
}




void refresh() {
    HWND hwnd = NULL;
    while (hwnd == NULL) {
        hwnd = FindWindowW(L"Chrome_WidgetWin_1", NULL);
        SetForegroundWindow(hwnd);
        Sleep(1000);
    }
    // 模拟按下 Ctrl 键
    keybd_event(VK_CONTROL, 0, 0, 0);
    // 模拟按下 F5 键
    keybd_event(VK_F5, 0, 0, 0);
    // 模拟释放 F5 键
    keybd_event(VK_F5, 0, KEYEVENTF_KEYUP, 0);
    // 模拟释放 Ctrl 键
    keybd_event(VK_CONTROL, 0, KEYEVENTF_KEYUP, 0);
}


void fullscreen() {
    // 等待浏览器窗口出现
    HWND hwnd = NULL;
    while (hwnd == NULL) {
        hwnd = FindWindowW(L"Chrome_WidgetWin_1", NULL);
        SetForegroundWindow(hwnd);
        Sleep(1000);
    }
    Sleep(2000);

    refresh();



    // 模拟按下 F11 键实现全屏
    keybd_event(VK_F11, 0, 0, 0);
    keybd_event(VK_F11, 0, KEYEVENTF_KEYUP, 0);
}

int boot() {
    std::ifstream file("config.ini");  // 
    if (!file.is_open()) {
        std::cerr << "无法打开文件" << std::endl;
        return 1;
    }

    std::string line1, line2, line3;
    std::getline(file, line1);
    std::getline(file, line2);
    std::getline(file, line3);
    file.close();


    line1 = line1 + ".exe";

    int num = std::stoi(line3);

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
        SetForegroundWindow(hwnd);
        Sleep(1000);
    }

    Sleep(num);
    fullscreen();
    return 0;
}

void reboot() {
    close();
    boot();
    
}

using boost::asio::ip::tcp;

void handleClient(tcp::socket socket) {

    while (true) {
        boost::asio::streambuf buffer;
        boost::system::error_code error;
        size_t length = boost::asio::read_until(socket, buffer, '\n', error);
        if (error == boost::asio::error::eof) {
            std::cout << "主控断开" << std::endl;
            break;
        }
        else if (error) {
            std::cout << "Error occurred: " << error.message() << std::endl;
            break;
        }

        std::string data = boost::asio::buffer_cast<const char*>(buffer.data());
        buffer.consume(length);

        std::cout << "Received: " << data << std::endl;


        if (data.find("reboot") != std::string::npos) {
            std::cout << "Received: " << data << std::endl;
            reboot();
        }

        if (data.find("refresh") != std::string::npos) {
            std::cout << "Received: " << data << std::endl;
            refresh();
        }

        if (data.find("close") != std::string::npos) {
            std::cout << "Received: " << data << std::endl;
            close();
        }

        if (data.find("boot") != std::string::npos) {
            std::cout << "Received: " << data << std::endl;
            boot();
        }

        if (data.find("fullscreen") != std::string::npos) {
            std::cout << "Received: " << data << std::endl;
            boot();
        }

        data.clear();


    }
}



int main() {

    HWND consoleWindow = GetConsoleWindow();
    ShowWindow(consoleWindow, SW_MAXIMIZE);

    boot();



    //网络监听

    boost::asio::io_context ioContext;

    tcp::acceptor acceptor(ioContext, tcp::endpoint(tcp::v4(), 1234));

    while (true) {
        tcp::socket socket(ioContext);
        tcp::endpoint endpoint;
        acceptor.accept(socket, endpoint);
        std::cout << "主控已连接: " << endpoint.address().to_string() << ", Port: " << endpoint.port() << std::endl;
        std::thread(handleClient, std::move(socket)).detach();
    }






    return 0;

}

