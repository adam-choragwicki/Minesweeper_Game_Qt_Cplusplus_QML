#pragma once

#include <memory>
#include <unordered_map>
#include <QSoundEffect>
#include <QString>
#include <QDebug>

class AssetRepository
{
public:
    static AssetRepository& instance()
    {
        static AssetRepository repo;
        return repo;
    }

    // Store a single sound under a logical name.
    void storeSound(const QString& name, std::unique_ptr<QSoundEffect> sound)
    {
        if (!sound)
        {
            qFatal() << "AssetRepository: Attempted to store null sound for name:" << name;
        }

        const auto [_, inserted] = sounds_.emplace(name, std::move(sound));

        if (!inserted)
        {
            qFatal() << "AssetRepository: Sound already registered under name:" << name << ". Duplicates are not allowed.";
        }
    }

    // Retrieve a sound by name (non-owning)
    [[nodiscard]] QSoundEffect* sound(const QString& name) const
    {
        const auto it = sounds_.find(name);

        if (it != sounds_.end())
        {
            return it->second.get();
        }

        return nullptr;
    }

private:
    AssetRepository() = default;

    std::unordered_map<QString, std::unique_ptr<QSoundEffect>> sounds_;
};
