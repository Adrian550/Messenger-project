// path to common includes
// #include "/Messenger/common_includes/std.h"

#include <QtWidgets/QApplication>

#include "ui/window.h"
#include "user.h"
#include "connection/connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Window w;
    w.show();

    return a.exec();
}
