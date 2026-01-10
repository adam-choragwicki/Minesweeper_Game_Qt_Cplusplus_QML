#pragma once

#include "sound_player.h"
#include "asset_management/asset_repository.h"
#include <QRandomGenerator>
#include <QDebug>

class SoundPlayer
{
public:
    void playFlagPlace()
    {
        retrieveAndPlaySound("flagPlace");
    }

    void playMenuClick()
    {
        retrieveAndPlaySound("menuClick");
    }

    void playMine(const double volume = 1.0)
    {
        retrieveAndPlaySound("mine", volume);
    }

    void playUncoverTile()
    {
        retrieveAndPlaySound("uncoverTile");
    }

private:
    void retrieveAndPlaySound(const QString& name, const double volume = 1.0)
    {
        if (auto* sound = AssetRepository::instance().sound(name))
        {
            sound->setVolume(volume);
            sound->play();
        }
        else
        {
            qCritical() << name << "sound missing" << name;
        }
    }
};
