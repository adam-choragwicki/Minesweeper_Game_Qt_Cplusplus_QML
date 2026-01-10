#include "input_handler.h"
#include "controller.h"
#include "window_manager.h"

InputHandler::InputHandler(Controller& controller, WindowManager& windowManager) : controller_(controller), windowManager_(windowManager)
{}

void InputHandler::processKeyPress(const int key)
{
    constexpr bool logKeyPressed = false;

    if (logKeyPressed)
    {
        qDebug() << "InputHandler::onKeyPress:" << key;
    }

    switch (key)
    {
        case Qt::Key_Escape:
            if (logKeyPressed) qDebug() << "Escape key pressed";
            controller_.getStateManager().handleKeyPress(key);
            break;

        case Qt::Key_F11:
            if (logKeyPressed) qDebug() << "F11 key pressed";
            windowManager_.toggleFullScreen();
            break;

        default:
            if (logKeyPressed) qDebug() << "Unsupported key pressed";
            break;
    }
}
