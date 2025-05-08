//
// Created by K W on 25-5-7.
//
#include<functional>
#include "server.h"

#include <iostream>

server::server(boost::asio::io_context& ioc, const short port):
    acceptor_(ioc, boost::asio::ip::tcp::endpoint(boost::asio::ip::tcp::v4(), port)), ioc_(ioc)

{
do_accept();
}


void server::do_accept()

{
    auto* new_session = new session(ioc_);
    acceptor_.async_accept(new_session->socket(), [this, new_session](const boost::system::error_code& ec)
    {
        do_start(new_session, ec);
    });
}

void server::do_start(session* new_session, const boost::system::error_code& ec)

{
    if (!ec)
    {
        new_session->start();
    }
    else
    {
        delete new_session;
    }
}

void session::do_read(const boost::system::error_code& ec, size_t bytes_transfered)
{
    if (!ec)
    {
        std::cout << "server receive data is" << buffer_ << std::endl;
        boost::asio::async_write(socket_, boost::asio::buffer(buffer_, bytes_transfered),
                                 [this]<typename T0>(T0 && PH1,auto && PH2) { do_write(std::forward<T0>(PH1)); });
    }


    else
        {
            delete this;
        }

}

void session::do_write(const boost::system::error_code& ec)
{
    if (!ec)
    {
        memset(buffer_, 0, sizeof(buffer_));
        socket_.async_read_some(boost::asio::buffer(buffer_, 1024),
                                [this]<typename T0, typename T1>(T0&& PH1, T1&& PH2)
                                {
                                    do_read(std::forward<T0>(PH1), std::forward<T1>(PH2));
                                });
    }
    else
    {
        delete this;
    }
}


void session::start()
{
    memset(buffer_, 0, sizeof(buffer_));
    socket_.async_read_some(boost::asio::buffer(buffer_, 1024),
                            [this]<typename T0, typename T1>(T0&& PH1, T1&& PH2)
                            {
                                do_read(std::forward<T0>(PH1), std::forward<T1>(PH2));
                            });
}
