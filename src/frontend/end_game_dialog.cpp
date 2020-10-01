#include "end_game_dialog.h"

#include <QApplication>

EndGameDialog::EndGameDialog(QWidget* parent, GameResult gameResult) : QMessageBox(parent)
{
    if(gameResult == GameResult::WIN)
    {
        setIcon(QMessageBox::Icon::Information);
        setWindowTitle("Congratulations");
        setText("You WIN");
    }
    else if(gameResult == GameResult::LOSE)
    {
        setIcon(QMessageBox::Icon::Warning);
        setWindowTitle("Game over");
        setText("Oops, do you want to play again?");
    }

    setStyleSheet("color: black");

    restartButton_ = addButton("Restart", QMessageBox::NoRole);
    closeButton_ = addButton("Close", QMessageBox::NoRole);
    changeParametersButton_ = addButton("Change parameters", QMessageBox::NoRole);

    int userInput = this->exec();

    if(userInput == static_cast<int>(ButtonRole::RESTART))
    {
        setResult(static_cast<int>(ButtonRole::RESTART));
    }
    else if(userInput == static_cast<int>(ButtonRole::EXIT))
    {
        setResult(static_cast<int>(ButtonRole::EXIT));
    }
    else if(userInput == static_cast<int>(ButtonRole::CHANGE_PARAMETERS))
    {
        setResult(static_cast<int>(ButtonRole::CHANGE_PARAMETERS));
    }
}

EndGameDialog::~EndGameDialog()
{
    delete restartButton_;
    delete closeButton_;
    delete changeParametersButton_;
}
