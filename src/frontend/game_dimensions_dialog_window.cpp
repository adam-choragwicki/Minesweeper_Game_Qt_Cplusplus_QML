#include "game_dimensions_dialog_window.h"
#include "ui_game_dimensions_dialog_window.h"

GameDimensionsDialogWindow::GameDimensionsDialogWindow() : ui_(new Ui::GameDimensionsDialogWindow)
{
    ui_->setupUi(this);

    for(int i = 0, rowCountOption = GameParametersLimits::MIN_ROW_COUNT; rowCountOption <= GameParametersLimits::MAX_ROW_COUNT; ++rowCountOption, ++i)
    {
        ui_->rowCount_ComboBox->addItem(QString::number(rowCountOption));
        ui_->rowCount_ComboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    for(int i = 0, columnCountOption = GameParametersLimits::MIN_COLUMN_COUNT; columnCountOption <= GameParametersLimits::MAX_COLUMN_COUNT; ++columnCountOption, ++i)
    {
        ui_->columnCount_ComboBox->addItem(QString::number(columnCountOption));
        ui_->columnCount_ComboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }

    for(int i = 0; i < GameParametersLimits::MINE_PERCENTAGE_OPTIONS.size(); ++i)
    {
        ui_->minesPercentage_ComboBox->addItem(QString::number(GameParametersLimits::MINE_PERCENTAGE_OPTIONS.at(i)));
        ui_->minesPercentage_ComboBox->setItemData(i, Qt::AlignCenter, Qt::TextAlignmentRole);
    }
}

GameDimensionsDialogWindow::~GameDimensionsDialogWindow()
{
    delete ui_;
}

void GameDimensionsDialogWindow::on_buttonBox_accepted()
{
    gameParameters_ = std::make_unique<MinefieldParameters>(ui_->rowCount_ComboBox->currentText().toInt(), ui_->columnCount_ComboBox->currentText().toInt(), ui_->minesPercentage_ComboBox->currentText().toInt());
}

void GameDimensionsDialogWindow::reject()
{
    exit(0);
}
