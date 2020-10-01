#include "fields_manager.h"
#include "model/field.h"

void FieldsManager::assignAdjacentMinesCountToAllFields(const Minefield& minefield)
{
    for(auto& [coordinates, field] : minefield.getCoordinatesToFieldsMapping())
    {
        if(field->isMinePresent())
        {
            /*If a field is a mine itself an adjacent mine count is irrelevant*/
            field->setAdjacentMineCount(std::nullopt);
        }
        else
        {
            const Coordinates& currentFieldCoordinates = field->getCoordinates();
            std::vector<Coordinates> allAdjacentFieldsCoordinates = generateAdjacentFieldsCoordinates(currentFieldCoordinates);

            int adjacentMineCount = 0;

            for(const auto& adjacentFieldCoordinates : allAdjacentFieldsCoordinates)
            {
                if(minefield.getCoordinatesToFieldsMapping().contains(adjacentFieldCoordinates))
                {
                    const Field& otherField = *minefield.getCoordinatesToFieldsMapping().at(adjacentFieldCoordinates).get();

                    if(otherField.isMinePresent())
                    {
                        ++adjacentMineCount;
                    }
                }
            }

            field->setAdjacentMineCount(adjacentMineCount);
        }
    }
}

std::vector<Field*> FieldsManager::getAdjacentFields(const Coordinates& coordinates, const Minefield& minefield)
{
    std::vector<Coordinates> adjacentFieldsCoordinates = generateAdjacentFieldsCoordinates(coordinates);
    std::vector<Field*> adjacentFields;

    for(auto& adjacentFieldCoordinates : adjacentFieldsCoordinates)
    {
        if(minefield.getCoordinatesToFieldsMapping().contains(adjacentFieldCoordinates))
        {
            adjacentFields.push_back(minefield.getCoordinatesToFieldsMapping().at(adjacentFieldCoordinates).get());
        }
    }

    return adjacentFields;
}

int FieldsManager::countRemainingCoveredFieldsWithoutMine(const Minefield& minefield)
{
    int counter = 0;

    for(auto& [coordinates, field] : minefield.getCoordinatesToFieldsMapping())
    {
        if(field->getState() != FieldState::UNCOVERED && !field->isMinePresent())
        {
            ++counter;
        }
    }

    return counter;
}

std::vector<Coordinates> FieldsManager::generateAdjacentFieldsCoordinates(const Coordinates& coordinates)
{
    std::vector<Coordinates> adjacentFieldsCoordinates;

    for(const auto& [rowOffset, columnOffset] : DIRECTIONAL_OFFSETS)
    {
        int adjacentRow = coordinates.getRow() + rowOffset;
        int adjacentColumn = coordinates.getColumn() + columnOffset;

        if(Coordinates::validateCoordinates(adjacentRow, adjacentColumn))
        {
            adjacentFieldsCoordinates.emplace_back(adjacentRow, adjacentColumn);
        }
    }

    return adjacentFieldsCoordinates;
}
