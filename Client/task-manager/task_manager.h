#ifndef TASK_MANAGER_H
#define TASK_MANAGER_H

#include <QThread>
#include <QQueue>

class Task_manager : public QThread
{
    Q_OBJECT

public:
    explicit Task_manager(QObject *parent = 0);

signals:
//signals of authorization
    void login_true();
    void login_false();
    void login_duplicate();
    void signup_true();
    void signup_false();
//signals of online status
    void contact_online(QByteArray);
    void contact_offline(QByteArray);
//signals for messages
    void update_log(QString);
    void create_log(QByteArray, QByteArray);
//signals for user's connection
    void someone_connected(QByteArray);
    void someone_disconnected(QByteArray);
//signal for recieve message
    void receive_message(QByteArray, QByteArray, QString);
//signals for user's methods
    void add_contacts(QStringList);
    void set_username(QByteArray);
    void set_user_id(QByteArray);
    void reconnect();
//slot's methods
private slots:
    void on_add_task(QByteArray);
    void on_lock();
    void on_unlock();
//task manager queue
private:
    QQueue<QByteArray> receive_queue;
    bool lock = false;
//handle method
private:
    void handle_task();
//start/finish
public:
    void run();
    void disconnect();
};

#endif
