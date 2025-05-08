
#include <boost/asio.hpp>
#include "server.h"
#include<iostream>
    int main() {
        try {
            boost::asio::io_context io_context;
            server s(io_context, 10086);  // 监听 10086 端口
            io_context.run();             // 启动事件循环
        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << "\n";
        }
    }
