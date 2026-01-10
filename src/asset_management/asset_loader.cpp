#include "asset_loader.h"
#include "asset_repository.h"
#include <QSoundEffect>
#include <QFile>
#include <QDebug>

bool AssetLoader::loadAssets()
{
    return loadSounds();
}

bool AssetLoader::loadSounds()
{
    struct SoundInfo
    {
        QString name;
        QUrl url;
    };

    static const std::vector<SoundInfo> sounds{
        {"flagPlace", QUrl("qrc:/sounds/flag_place.wav")},
        {"menuClick", QUrl("qrc:/sounds/menu_click.wav")},
        {"mine", QUrl("qrc:/sounds/mine.wav")},
        {"uncoverTile", QUrl("qrc:/sounds/uncover_tile.wav")}
    };

    for (const auto& [name, url]: sounds)
    {
        if (!loadSound(name, url))
        {
            return false;
        }
    }

    return true;
}

bool AssetLoader::loadSound(const QString& name, const QUrl& url)
{
    if (!checkIfResourceExists(url))
    {
        return false;
    }

    auto soundEffect = std::make_unique<QSoundEffect>();
    soundEffect->setSource(url);
    soundEffect->setVolume(1.0f);
    AssetRepository::instance().storeSound(name, std::move(soundEffect));

    return true;
}

bool AssetLoader::checkIfResourceExists(const QUrl& url)
{
    if (const QString resourcePath = url.toString().mid(3); !QFile::exists(resourcePath))
    {
        qCritical() << "QRC resource does not exist: " << resourcePath;
        return false;
    }

    return true;
}
