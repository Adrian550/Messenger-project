#include <QtCore/QCoreApplication>

#include "task_manager.h"
#include "core/server.h"

#include "util/commands.h"

// Конструктор сервера, наследуемся от QTcpServer
// Начинаем слушать server_port
// Устанавливаем соединение с базой данных
Server::Server(QObject *parent) : QTcpServer(parent)
{
    if (!this->listen(QHostAddress::Any, server_port))
        OUTPUT("Failed to start a server");

    else
        OUTPUT("Server started successfully at port" << server_port);

    db.setDatabaseName(server_database_path);

    if (db.open())
    {
        OUTPUT("Database connected");
        QSqlQuery query;
        query.exec("delete from session;");
    }

    else
    {
        OUTPUT("Error: database connection failed:" << db.lastError());
        exit(1);
    }
    // В случае если остались активные сессии с прошлой работы сервера
    // удаляем их
    QSqlQuery query;
    query.exec("delete from session;");
}

// connection нового клиента
// С помощью класса Client создаем нового пользователя с уникальным ID
// Биндим сигналы и слоты для отправки пакетов, принятия пакетов, мьютексы для подключения, 
void Server::incomingConnection(qintptr socket_id)
{
    Client *thread = new Client(socket_id, this);
    Task_manager *task_manager = new Task_manager();

    connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
    connect(this, SIGNAL(send_message(QByteArray, QByteArray, QByteArray)), thread, SLOT(send_message(QByteArray, QByteArray, QByteArray)), Qt::QueuedConnection);

    connect(thread, SIGNAL(receive_message(QByteArray)), task_manager, SLOT(on_add_task(QByteArray)), Qt::QueuedConnection);
    connect(task_manager, SIGNAL(send_message(QByteArray, QByteArray, QByteArray)), this, SLOT(on_send_message(QByteArray, QByteArray, QByteArray)), Qt::QueuedConnection);
    connect(thread, SIGNAL(lock()), task_manager, SLOT(on_lock()), Qt::QueuedConnection);
    connect(thread, SIGNAL(unlock()), task_manager, SLOT(on_unlock()), Qt::QueuedConnection);

    thread->start();
    task_manager->start();

    OUTPUT("Client connected id:" << thread->get_id());
}

// Слот для отправки сообщения клиенту, в случае если переданный mode является EXIT
// то всем подключенным клиентам отправляется сообщение о его выходе, для корректной работы плашки Online/Offline
void Server::on_send_message(QByteArray mode, QByteArray value, QByteArray message)
{
    if (mode == EXIT)
        send_message(ALL, value, message);

    else
        send_message(mode, value, message);
}
