#include "field_button.h"
#include "model/field.h"
#include "gui_config.h"

FieldButton::FieldButton(Field& field) : field_(field)
{
    if(!pixmapsLoaded)
    {
        pixmapsLoaded = loadImages();
    }

    setCheckable(true);
    setFixedSize(GuiConfig::FieldButton::SIZE, GuiConfig::FieldButton::SIZE);

    QFont currentFont = font();
    currentFont.setPointSize(GuiConfig::FieldButton::FONT_SIZE);
    currentFont.setBold(true);
    setFont(currentFont);

    render();
}

bool FieldButton::loadImages()
{
    flagPixmap = std::make_unique<QPixmap>();
    minePixmap = std::make_unique<QPixmap>();

    if(!flagPixmap->load(QString::fromStdString(GuiConfig::FieldButton::FLAG_PIXMAP_URL)))
    {
        throw std::runtime_error("Could not load: " + GuiConfig::FieldButton::FLAG_PIXMAP_URL);
    }

    if(!minePixmap->load(QString::fromStdString(GuiConfig::FieldButton::MINE_PIXMAP_URL)))
    {
        throw std::runtime_error("Could not load: " + GuiConfig::FieldButton::MINE_PIXMAP_URL);
    }

    return true;
}

void FieldButton::mousePressEvent(QMouseEvent* event)
{
    emit mousePressedEvent(event, field_);
}

void FieldButton::render()
{
    switch(field_.getState())
    {
        case FieldState::FLAGGED:
            setIcon(*flagPixmap);
            setChecked(false);
            setIconSize(QSize(width() - 5, height() - 5));
            clearText();
            break;

        case FieldState::COVERED:
            resetIcon();
            setChecked(false);
            setStyleSheet("color: black");
            setIconSize(QSize(width() - 5, height() - 5));
            clearText();
            break;

        case FieldState::MINE_EXPLODED:
            setIcon(*minePixmap);
            setChecked(false);
            setIconSize(QSize(width() - 2, height() - 2));
            clearText();
            break;

        default:
            resetIcon();
            setChecked(true);

            auto adjacentMineCount = field_.getAdjacentMineCount();

            if(adjacentMineCount == 0)
            {
                setStyleSheet("background:rgb(240, 240, 240);");
                clearText();
            }
            else
            {
                setStyleSheet("color: black");
                setText(QString::number(adjacentMineCount.value_or(-1)));
            }
            break;
    }
}

void FieldButton::resetIcon()
{
    setIcon(QIcon());
}

void FieldButton::clearText()
{
    setText("");
}
