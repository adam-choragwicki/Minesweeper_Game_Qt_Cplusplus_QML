#include "main_window.h"
#include "ui_main_window.h"
#include "end_game_dialog.h"
#include "game_dimensions_dialog_window.h"

MainWindow::MainWindow(const Model& model) : ui_(new Ui::MainWindow), model_(model)
{
    ui_->setupUi(this);

    mainGridLayout_.setHorizontalSpacing(0);
    mainGridLayout_.setVerticalSpacing(0);

    layout()->setSizeConstraint(QLayout::SetFixedSize);
    ui_->centralwidget->setLayout(&mainGridLayout_);
}

MainWindow::~MainWindow()
{
    delete ui_;
}

void MainWindow::closeEvent(QCloseEvent*)
{
    exit(0);
}

void MainWindow::centerOnScreen()
{
    const QRect screenRect = QWidget::screen()->availableGeometry();
    const QRect widgetRect({}, frameSize().boundedTo(screenRect.size()));

    move(screenRect.center() - widgetRect.center());
}

void MainWindow::updateFieldButtons()
{
    removeFieldButtons();
    createFieldButtons();

    centerOnScreen();
}

void MainWindow::createFieldButtons()
{
    for(const auto&[coordinates, field] : model_.getMinefield().getCoordinatesToFieldsMapping())
    {
        const auto&[_, inserted] = coordinatesToFieldButtonsMapping.insert_or_assign(coordinates, std::make_unique<FieldButton>(*field));

        if(!inserted)
        {
            throw std::runtime_error("Error, field button with given coordinates is already on the minefield");
        }

        mainGridLayout_.addWidget(coordinatesToFieldButtonsMapping.at(coordinates).get(), coordinates.getRow(), coordinates.getColumn());
    }

    setFixedSize(size());
}

void MainWindow::removeFieldButtons()
{
    coordinatesToFieldButtonsMapping.clear();
}

MinefieldParameters MainWindow::showGameDimensionsDialog()
{
    GameDimensionsDialogWindow gameDimensionsDialogWindow;
    gameDimensionsDialogWindow.exec();

    auto minefieldParameters_ = gameDimensionsDialogWindow.getGameParameters();

    return minefieldParameters_;
}

void MainWindow::showEndGameDialog(GameResult gameResult)
{
    EndGameDialog endGameDialog(this, gameResult);

    if(endGameDialog.result() == static_cast<int>(EndGameDialog::ButtonRole::RESTART))
    {
        emit restartEvent(false);
    }
    else if(endGameDialog.result() == static_cast<int>(EndGameDialog::ButtonRole::CHANGE_PARAMETERS))
    {
        emit restartEvent(true);
    }
    else
    {
        close();
    }
}

void MainWindow::renderAllFieldButtons()
{
    for(const auto&[coordinates, fieldButton] : coordinatesToFieldButtonsMapping)
    {
        fieldButton->render();
    }
}
