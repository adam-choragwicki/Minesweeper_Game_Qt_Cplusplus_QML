#include "common_test_fixture.h"
#include "tiles_manager.h"
#include "tile.h"

class TilesManagerTest : public CommonTestFixture
{};

/*100 tiles, 0 generated mines, 0 uncovered, 0 flags*/
TEST_F(TilesManagerTest, CountCoveredTilesWithoutMine_NoMines)
{
    const MinefieldParameters minefieldParameters(10, 10, 0);
    const Minefield minefield(minefieldParameters);

    EXPECT_EQ(TilesManager::countRemainingCoveredTilesWithoutMine(minefield), 100);
}

/*100 tiles, 100 generated mines, 0 uncovered, 0 flags*/
TEST_F(TilesManagerTest, CountCoveredTilesWithoutMine_MinefieldIsFullOfMines)
{
    const MinefieldParameters minefieldParameters(10, 10, 100);
    const Minefield minefield(minefieldParameters);

    EXPECT_EQ(TilesManager::countRemainingCoveredTilesWithoutMine(minefield), 0);
}

/*100 tiles, 10 generated mines, 0 uncovered, 0 flags*/
TEST_F(TilesManagerTest, CountCoveredTilesWithoutMine1)
{
    const MinefieldParameters minefieldParameters(10, 10, 10);
    const Minefield minefield(minefieldParameters);

    EXPECT_EQ(TilesManager::countRemainingCoveredTilesWithoutMine(minefield), 90);
}

/*150 tiles, 15 generated mines, 0 uncovered, 0 flags*/
TEST_F(TilesManagerTest, CountCoveredTilesWithoutMine2)
{
    const MinefieldParameters minefieldParameters(10, 15, 10);
    const Minefield minefield(minefieldParameters);

    EXPECT_EQ(TilesManager::countRemainingCoveredTilesWithoutMine(minefield), 135);
}

TEST_F(TilesManagerTest, GetAdjacentTiles)
{
    const MinefieldParameters minefieldParameters(10, 10, 10);
    Minefield minefield(minefieldParameters);

    std::vector<Tile*> adjacentTiles1 = TilesManager::getAdjacentTiles(Coordinates(1, 1), minefield);

    EXPECT_EQ(adjacentTiles1.size(), 3);
    EXPECT_EQ(adjacentTiles1.at(0)->getCoordinates(), Coordinates(1, 2));
    EXPECT_EQ(adjacentTiles1.at(1)->getCoordinates(), Coordinates(2, 1));
    EXPECT_EQ(adjacentTiles1.at(2)->getCoordinates(), Coordinates(2, 2));

    auto adjacentTiles2 = TilesManager::getAdjacentTiles(Coordinates(5, 10), minefield);

    EXPECT_EQ(adjacentTiles2.size(), 5);
    EXPECT_EQ(adjacentTiles2.at(0)->getCoordinates(), Coordinates(4, 9));
    EXPECT_EQ(adjacentTiles2.at(1)->getCoordinates(), Coordinates(4, 10));
    EXPECT_EQ(adjacentTiles2.at(2)->getCoordinates(), Coordinates(5, 9));
    EXPECT_EQ(adjacentTiles2.at(3)->getCoordinates(), Coordinates(6, 9));
    EXPECT_EQ(adjacentTiles2.at(4)->getCoordinates(), Coordinates(6, 10));

    auto adjacentTiles3 = TilesManager::getAdjacentTiles(Coordinates(5, 5), minefield);

    EXPECT_EQ(adjacentTiles3.size(), 8);
    EXPECT_EQ(adjacentTiles3.at(0)->getCoordinates(), Coordinates(4, 4));
    EXPECT_EQ(adjacentTiles3.at(1)->getCoordinates(), Coordinates(4, 5));
    EXPECT_EQ(adjacentTiles3.at(2)->getCoordinates(), Coordinates(4, 6));
    EXPECT_EQ(adjacentTiles3.at(3)->getCoordinates(), Coordinates(5, 4));
    EXPECT_EQ(adjacentTiles3.at(4)->getCoordinates(), Coordinates(5, 6));
    EXPECT_EQ(adjacentTiles3.at(5)->getCoordinates(), Coordinates(6, 4));
    EXPECT_EQ(adjacentTiles3.at(6)->getCoordinates(), Coordinates(6, 5));
    EXPECT_EQ(adjacentTiles3.at(7)->getCoordinates(), Coordinates(6, 6));
}

TEST_F(TilesManagerTest, AssignAdjacentMinesCountToAllTiles)
{
    const MinefieldParameters minefieldParameters(3, 3, 10);
    const std::set<Coordinates> minesCoordinates{{1, 1}, {2, 2}, {3, 1}};

    const Minefield minefield(minefieldParameters, minesCoordinates);

    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 2)).getAdjacentMineCount(), 2);
    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 3)).getAdjacentMineCount(), 1);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 1)).getAdjacentMineCount(), 3);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 3)).getAdjacentMineCount(), 1);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 2)).getAdjacentMineCount(), 2);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 3)).getAdjacentMineCount(), 1);

    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 1)).getAdjacentMineCount(), std::nullopt);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 2)).getAdjacentMineCount(), std::nullopt);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 1)).getAdjacentMineCount(), std::nullopt);
}
