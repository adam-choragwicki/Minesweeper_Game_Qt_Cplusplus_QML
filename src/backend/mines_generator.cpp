#include "mines_generator.h"
#include "model/field.h"

#include <QRandomGenerator>
#include <set>

void MineGenerator::generateMines(const MinefieldParameters& gameParameters, const Minefield& minefield)
{
    const int targetMineCount = static_cast<int>(gameParameters.rowCount * gameParameters.columnCount * (double(gameParameters.minePercentage) / 100));

    QRandomGenerator* randomGenerator = QRandomGenerator::global();

    std::set<Coordinates> mineCoordinatesSet;

    while(mineCoordinatesSet.size() != targetMineCount)
    {
        mineCoordinatesSet.insert(Coordinates(randomGenerator->bounded(1, gameParameters.rowCount), randomGenerator->bounded(1, gameParameters.columnCount)));
    }

    for(const Coordinates& mineCoordinates : mineCoordinatesSet)
    {
        if(minefield.getCoordinatesToFieldsMapping().contains(mineCoordinates))
        {
            minefield.getCoordinatesToFieldsMapping().at(mineCoordinates)->placeMine();
        }
        else
        {
            throw std::runtime_error("Cannot place mine on non-existing field.");
        }
    }
}
