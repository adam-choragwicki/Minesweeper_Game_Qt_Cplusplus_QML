#include "game.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication application(argc, argv);
    Game game;

    return QApplication::exec();
}

//TODO center on screen does not work properly
//TODO use State pattern on Field state
