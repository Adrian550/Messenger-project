// path to common includes
//#include "/Messenger/common_includes/std.h"

#include <QFile>

#include "task_manager.h"

#include <qtextstream.h>

#include "util/commands.h"
// path to common includes
//#include "/Messenger/common_includes/commands.h"
//Constructor
Task_manager::Task_manager(QObject *parent)
{
}
//run task manager
void Task_manager::run()
{
    exec();
}
// task manager mutex lock
void Task_manager::on_lock()
{
    lock = true;
}
//task manager mutex unlock
void Task_manager::on_unlock()
{
    if (receive_queue.size() != 0)
        handle_task();

    lock = false;
}
//disconnect task manager
void Task_manager::disconnect()
{
    exit(0);
}
//accept recieved task
void Task_manager::on_add_task(QByteArray task)
{
    receive_queue.enqueue(task);

    if (!lock)
        handle_task();
}
//handle task
void Task_manager::handle_task()
{
    QByteArray message = receive_queue.dequeue();
    QTextStream stream(message);
    QByteArray message_code[2];

    stream >> message_code[0];
// handle connection
    if (message_code[0][0] == SYSTEM_MESSAGE_START)
    {
        if (message_code[0] == ID)
        {
            QByteArray user_id;

            stream >> user_id;
            emit(set_user_id(user_id));
        }
//handle validation
        if (message_code[0] == VALIDATION)
        {
            QByteArray username;

            stream >> message_code[1];

            if (message_code[1] == GOOD)
            {
                stream >> username;
                emit(set_username(username));
                emit(login_true());
            }

            else if (message_code[1] == BAD)
                emit(login_false());

            else if (message_code[1] == DUPLICATE)
                emit(login_duplicate());
        }
//handle sign up
        else if (message_code[0] == SIGNUP)
        {
            stream >> message_code[1];

            if (message_code[1] == GOOD)
                emit(signup_true());

            else if (message_code[1] == BAD)
                emit(signup_false());
        }
//handle user's online status
        else if (message_code[0] == IS_ONLINE)
        {
            QByteArray contact;

            stream >> contact >> message_code[1];

            if (message_code[1] == GOOD)
                emit(contact_online(contact));

            else if (message_code[1] == BAD)
                emit(contact_offline(contact));
        }
//handle dialog with contact
        else if (message_code[0] == LOG)
        {
            QByteArray contact;
            stream >> contact;
            QString s = stream.readAll();

            s.remove(0, 1);
            emit(create_log(contact, s.toUtf8()));
        }
//handle finished send signal to update dialog
        else if (message_code[0] == LOG_FINISH)
        {
            QString contact;
            stream >> contact;

            emit(update_log(contact));
        }
//handle user connecton
        else if (message_code[0] == CONNECTED)
        {
            QByteArray name;

            stream >> name;
            emit(someone_connected(name));
        }

        else if (message_code[0] == DISCONNECTED)
        {
            QByteArray name;

            stream >> name;
            emit(someone_disconnected(name));
        }
//handle if user add contact
        else if (message_code[0] == ADD_CONTACT)
        {
            QString s = stream.readAll();
            s.remove(0, 1);

            if (s.length() != 0)
            {
                QStringList contact_list = s.split(" ");
                add_contacts(contact_list);
            }
        }
    }

    else if (message_code[0] == SEND)
    {
        QByteArray username, destination;

        stream >> username >> destination;
        QString s = stream.readAll();
        s.remove(0, 1);

        emit(receive_message(username, destination, s));
    }

    else if (message_code[0] == "test")
    {
        emit(reconnect());
    }
}
