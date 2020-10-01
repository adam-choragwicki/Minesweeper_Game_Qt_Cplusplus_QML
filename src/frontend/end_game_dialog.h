#pragma once

#include "common.h"

#include <QMessageBox>
#include <QPushButton>

class EndGameDialog : public QMessageBox
{
public:
    EndGameDialog(QWidget* parent, GameResult gameResult);
    ~EndGameDialog() override;

    enum class ButtonRole
    {
        RESTART = 0, EXIT = 1, CHANGE_PARAMETERS = 2
    };

private:
    QPushButton* restartButton_;
    QPushButton* closeButton_;
    QPushButton* changeParametersButton_;
};
