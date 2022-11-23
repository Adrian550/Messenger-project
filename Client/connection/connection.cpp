#include <QDebug>
#include <QSqlQuery>
#include <Windows.h>
#include <qmessagebox.h>


#include "connection.h"

//Connection by QT socket
Connection::Connection(QObject *parent) : QTcpSocket(parent)
{
    connect(socket, SIGNAL(readyRead()), this, SLOT(receive_message()));
    connect(socket, SIGNAL(connected()), this, SLOT(on_socket_connected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(on_socket_error(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(stateChanged(QAbstractSocket::SocketState)), this, SLOT(on_socket_change(QAbstractSocket::SocketState)));

    QSqlQuery query;

    query.exec("select * from Connection;");

    if (query.next())
    {
    	this->server_ip = "176.126.103.19";//query.value(0).toString();
        this->server_port = query.value(1).toInt();
    }

    socket->connectToHost(server_ip, server_port);
}

//Destructor for Connection class
//Delete User's object, disconnect from server
Connection::~Connection()
{
    socket->deleteLater();
    delete user;
}

// connection succesfull
void Connection::on_socket_connected()
{
    status = true;
    emit(connected());
}
//connection error
void Connection::on_socket_error(QAbstractSocket::SocketError socketError)
{
    if (status)
        status = false;

    emit(error());
}
//Connect + Reconnect
void Connection::on_socket_change(QAbstractSocket::SocketState socketState)
{
    if (socketState == QAbstractSocket::UnconnectedState)
        socket->connectToHost(server_ip, server_port);
}

// recieve
void Connection::receive_message()
{
    QByteArray message = socket->readAll();

    emit(add_task(message));
}
//check if message has been sent
bool Connection::send_message(QByteArray message)
{
    if (socket->write(message))
        return 1;
    return 0;
}

// setters/getters
void Connection::set_user(User *user)
{
    this->user = user;
}

void Connection::set_destination(QByteArray destination)
{
    this->destination = destination;
}

QByteArray Connection::get_destination()
{
    return this->destination;
}

bool Connection::get_status()
{
    return status;
}

void Connection::on_set_username(QByteArray username)
{
    user->set_username(username);
}

void Connection::on_set_user_id(QByteArray user_id)
{
    user->set_user_id(user_id);
}
