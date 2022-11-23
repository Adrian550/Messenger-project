#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QVector>
#include <QMap>
#include <QtSql>

#include "client/client.h"

class Server : public QTcpServer
{
    Q_OBJECT

public:
    explicit Server(QObject *parent = 0);

private:
    // Порт который слушаем на сервере
    int server_port = 8084;
    // Название базы данных
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");

signals:
    void send_message(QByteArray, QByteArray, QByteArray);

private slots:
    void on_send_message(QByteArray, QByteArray, QByteArray);

protected:
    void incomingConnection(qintptr user_id);
};

#endif
