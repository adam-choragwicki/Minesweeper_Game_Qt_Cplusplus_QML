#pragma once

#include "model/model.h"
#include "model/field.h"
#include "common.h"
#include "field_button.h"

#include <QMainWindow>
#include "QGridLayout"

using CoordinatesToFieldButtonsMapping = std::map<Coordinates, std::unique_ptr<FieldButton>>;

QT_BEGIN_NAMESPACE
namespace Ui
{
    class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
Q_OBJECT

signals:
    void restartEvent(bool newParametersRequested);

public:
    explicit MainWindow(const Model& model);
    ~MainWindow() override;

    void updateFieldButtons();
    void renderAllFieldButtons();

    [[nodiscard]] const CoordinatesToFieldButtonsMapping& getFieldButtons() const
    { return coordinatesToFieldButtonsMapping; }

    MinefieldParameters showGameDimensionsDialog();
    void showEndGameDialog(GameResult gameResult);

private:
    void closeEvent(QCloseEvent*) override;

    void createFieldButtons();
    void removeFieldButtons();
    void centerOnScreen();

    Ui::MainWindow* ui_;
    QGridLayout mainGridLayout_;
    const Model& model_;

    CoordinatesToFieldButtonsMapping coordinatesToFieldButtonsMapping;
};
