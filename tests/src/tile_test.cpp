#include "common_test_fixture.h"
#include "minefield.h"
#include "tile.h"

class TileTest : public CommonTestFixture
{};

TEST_F(TileTest, CheckTileDefaultParametersAfterCreation)
{
    const Tile tile(Coordinates(3, 5));

    EXPECT_EQ(tile.getCoordinates(), Coordinates(3,5));
    EXPECT_FALSE(tile.isMinePresent());
    EXPECT_TRUE(tile.getState() == Tile::State::COVERED);
}

TEST_F(TileTest, PlaceMine)
{
    Tile tile(Coordinates(7, 5));

    EXPECT_FALSE(tile.isMinePresent());

    tile.setMine();

    EXPECT_TRUE(tile.isMinePresent());
}

TEST_F(TileTest, PlaceMineTwice)
{
    Tile tile(Coordinates(1, 3));

    tile.setMine();

    EXPECT_THROW(tile.setMine(), std::runtime_error);
}

TEST_F(TileTest, Uncover)
{
    Tile tile(Coordinates(7, 5));

    EXPECT_TRUE(tile.getState() == Tile::State::COVERED);

    tile.uncover();

    EXPECT_TRUE(tile.getState() == Tile::State::UNCOVERED);
}

TEST_F(TileTest, Reset)
{
    Tile tile(Coordinates(7, 5));

    tile.reset();

    EXPECT_EQ(tile.getCoordinates(), Coordinates(7,5));
    EXPECT_FALSE(tile.isMinePresent());
    EXPECT_TRUE(tile.getState() == Tile::State::COVERED);
}
