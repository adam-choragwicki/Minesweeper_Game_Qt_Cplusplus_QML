#pragma once

#include "common.h"
#include "coordinates.h"

#include <QPushButton>
#include <QMouseEvent>

class FieldButton : public QPushButton
{
Q_OBJECT

signals:
    void mousePressedEvent(QMouseEvent* event, Field& field);

public slots:
    void render();

public:
    explicit FieldButton(Field& field);

    [[nodiscard]] const Field& getField() const
    { return field_; };

private:
    void mousePressEvent(QMouseEvent* event) override;

    static bool loadImages();
    void resetIcon();
    void clearText();

    inline static std::unique_ptr<QPixmap> flagPixmap;
    inline static std::unique_ptr<QPixmap> minePixmap;

    inline static bool pixmapsLoaded = false;

    Field& field_;
};
