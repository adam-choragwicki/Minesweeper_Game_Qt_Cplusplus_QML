#pragma once

#include "model/model.h"
#include "frontend/main_window.h"

class Controller : public QObject
{
Q_OBJECT

public slots:
    void processMousePressEvent(QMouseEvent* event, Field& field);

public:
    Controller(Model& model, MainWindow& view);

    void subscribeToFieldButtonClickedEvents();
    void subscribeFieldButtonsToFieldStateUpdatedEvents();

    void endGame(GameResult gameResult);

private slots:
    void processRestartEvent(bool newParametersRequested);

private:
    Model& model_;
    MainWindow& view_;

    void resizeMinefield(const MinefieldParameters& minefieldParameters);
    void subscribeToRestartEvent() const;
};
