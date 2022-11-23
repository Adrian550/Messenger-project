#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>

#include "core/user.h"
//Constructor 
class Connection : public QTcpSocket
{
    Q_OBJECT

public:
    explicit Connection(QObject *parent = 0);
    ~Connection();
    QString server_ip = "127.0.0.1";
    int server_port = 8084;

private:
    QTcpSocket* socket = new QTcpSocket(this);
    User *user;
    bool status = false;
    QByteArray destination;

signals:
//signals for connection
    void connected();
    void disconnected();
    void error();
//signal for task_manager
    void add_task(QByteArray);

private slots:
//slot for message check
    void receive_message();
//slots for connection
    void on_socket_connected();
    void on_socket_error(QAbstractSocket::SocketError socketError);
    void on_socket_change(QAbstractSocket::SocketState socketState);
//slots for setters
    void on_set_username(QByteArray);
    void on_set_user_id(QByteArray);

//checker and Getters/Setters
public:
    bool send_message(QByteArray message);
    void set_user(User *);
    bool get_status();
    void set_destination(QByteArray);
    QByteArray get_destination();
};

#endif
