#include "controller.h"

Controller::Controller(Model& model, MainWindow& view) : model_(model), view_(view)
{
    subscribeToRestartEvent();
    processRestartEvent(true);
}

void Controller::processMousePressEvent(QMouseEvent* event, Field& field)
{
    if(event->button() == Qt::MouseButton::LeftButton)
    {
        if(field.getState() == FieldState::COVERED)
        {
            if(field.isMinePresent())
            {
                field.setState(FieldState::MINE_EXPLODED);
                endGame(GameResult::LOSE);
            }
            else
            {
                field.uncover();

                if(field.getAdjacentMineCount() == 0)
                {
                    FieldsUncoverer::uncoverAdjacentEmptyFields(field, model_.getMinefield());
                }
            }

            if(FieldsManager::countRemainingCoveredFieldsWithoutMine(model_.getMinefield()) == 0)
            {
                endGame(GameResult::WIN);
            }
        }
    }
    else if(event->button() == Qt::MouseButton::RightButton)
    {
        if(field.getState() == FieldState::COVERED)
        {
            field.setState(FieldState::FLAGGED);
        }
        else if(field.getState() == FieldState::FLAGGED)
        {
            field.setState(FieldState::COVERED);
        }
    }
}

void Controller::processRestartEvent(bool newParametersRequested)
{
    if(newParametersRequested)
    {
        MinefieldParameters minefieldParameters = view_.showGameDimensionsDialog();
        resizeMinefield(minefieldParameters);

        subscribeToFieldButtonClickedEvents();
        subscribeFieldButtonsToFieldStateUpdatedEvents();
    }
    else
    {
        model_.reset();
        view_.renderAllFieldButtons();
    }

    view_.show();
}

void Controller::subscribeToFieldButtonClickedEvents()
{
    for(auto&[coordinates, fieldButton] : view_.getFieldButtons())
    {
        connect(fieldButton.get(), &FieldButton::mousePressedEvent, this, &Controller::processMousePressEvent);
    }
}

void Controller::subscribeFieldButtonsToFieldStateUpdatedEvents()
{
    for(auto&[coordinates, fieldButton] : view_.getFieldButtons())
    {
        connect(&fieldButton.get()->getField(), &Field::fieldStateUpdatedEvent, fieldButton.get(), &FieldButton::render);
    }
}

void Controller::resizeMinefield(const MinefieldParameters& minefieldParameters)
{
    model_.resizeMinefield(minefieldParameters);
    view_.updateFieldButtons();
}

void Controller::subscribeToRestartEvent() const
{
    connect(&view_, &MainWindow::restartEvent, this, &Controller::processRestartEvent);
}

void Controller::endGame(GameResult gameResult)
{
    view_.showEndGameDialog(gameResult);
}
