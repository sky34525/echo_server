//
// Created by K W on 25-5-7.
//
#pragma once

#include<boost/asio.hpp>
#ifndef SERVER_H
#define SERVER_H

class session
{
public:
    explicit session(boost::asio::io_context &ioc):socket_(ioc){};
    void start();
    boost::asio::ip::tcp::socket& socket()
    {
        return socket_;
    };
    private:
    boost::asio::ip::tcp::socket socket_;
    char buffer_[1024]={0};
    void do_read(const boost::system::error_code &ec,size_t bytes_transfered);
    void do_write(const boost::system::error_code &ec);
};

class server {
    public:
    server(boost::asio::io_context &ioc,short port);

    private:
    boost::asio::ip::tcp::acceptor acceptor_;
    boost::asio::io_context &ioc_;
    void do_accept();
    static void do_start(session* new_session,const boost::system::error_code &error);
};



#endif //SERVER_H
