#pragma once

#include <QDialog>
#include "common.h"

namespace Ui
{
    class GameDimensionsDialogWindow;
}

class GameDimensionsDialogWindow : public QDialog
{
Q_OBJECT

public:
    explicit GameDimensionsDialogWindow();
    ~GameDimensionsDialogWindow() override;

    [[nodiscard]] MinefieldParameters getGameParameters() const
    { return *gameParameters_; }

private:
    void reject() override;

    Ui::GameDimensionsDialogWindow* ui_;
    std::unique_ptr<MinefieldParameters> gameParameters_;

private slots:
    void on_buttonBox_accepted();
};
