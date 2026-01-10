#include "common_test_fixture.h"
#include "tiles_manager.h"
#include "tiles_uncoverer.h"
#include "tile.h"

class TilesUncovererTest : public CommonTestFixture
{};

TEST_F(TilesUncovererTest, Uncover_BigEmptyArea)
{
    const MinefieldParameters minefieldParameters(100, 100, 0);
    const std::set<Coordinates> mines{}; // empty
    Minefield minefield(minefieldParameters, mines);

    // start flood fill from a center
    Tile& uncoverStartTile = minefield.getTileAt(Coordinates(50, 50));
    TilesUncoverer::uncoverAdjacentEmptyTiles(uncoverStartTile, minefield);

    // all tiles should be uncovered (no mines)
    for (int row = 1; row <= 10; ++row)
    {
        for (int column = 1; column <= 10; ++column)
        {
            EXPECT_EQ(minefield.getTileAt(Coordinates(row,column)).getState(), Tile::State::UNCOVERED);
        }
    }
}

TEST_F(TilesUncovererTest, UncoverAdjacentEmptyTiles1)
{
    MinefieldParameters minefieldParameters(4, 4, 10);
    const std::set<Coordinates> minesCoordinates{{1, 4}};

    Minefield minefield(minefieldParameters, minesCoordinates);

    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 1)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 2)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 3)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 4)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 1)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 2)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 3)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 4)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 1)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 2)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 3)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 4)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(4, 1)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(4, 2)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(4, 3)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(4, 4)).getState(), Tile::State::COVERED);

    auto& tile = minefield.getTileAt(Coordinates(4, 1));
    TilesUncoverer::uncoverAdjacentEmptyTiles(tile, minefield);

    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 1)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 2)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 3)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 4)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 1)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 2)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 3)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 4)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 1)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 2)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 3)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 4)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(4, 1)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(4, 2)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(4, 3)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(4, 4)).getState(), Tile::State::UNCOVERED);
}

TEST_F(TilesUncovererTest, UncoverAdjacentEmptyTiles2)
{
    MinefieldParameters minefieldParameters(4, 4, 10);
    const std::set<Coordinates> minesCoordinates{{1, 1}, {4, 1}, {4, 4}};

    Minefield minefield(minefieldParameters, minesCoordinates);

    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 1)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 2)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 3)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 4)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 1)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 2)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 3)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 4)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 1)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 2)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 3)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 4)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(4, 1)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(4, 2)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(4, 3)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(4, 4)).getState(), Tile::State::COVERED);

    auto& tile = minefield.getTileAt(Coordinates(1, 4));
    TilesUncoverer::uncoverAdjacentEmptyTiles(tile, minefield);

    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 1)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 2)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 3)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(1, 4)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 1)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 2)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 3)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(2, 4)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 1)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 2)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 3)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(3, 4)).getState(), Tile::State::UNCOVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(4, 1)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(4, 2)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(4, 3)).getState(), Tile::State::COVERED);
    EXPECT_EQ(minefield.getTileAt(Coordinates(4, 4)).getState(), Tile::State::COVERED);
}
