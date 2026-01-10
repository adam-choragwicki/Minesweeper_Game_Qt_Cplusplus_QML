#pragma once

#include <QUrl>

class AssetLoader
{
public:
    static bool loadAssets();

private:
    static bool loadSounds();
    static bool loadSound(const QString& name, const QUrl& url);

    static bool checkIfResourceExists(const QUrl& url);
};
