#include "common_test_fixture.h"
#include "minefield.h"
#include "tile.h"

class MinefieldTest : public CommonTestFixture
{};

TEST_F(MinefieldTest, MinefieldSize1)
{
    const MinefieldParameters minefieldParameters(10, 10, 10);
    const Minefield minefield(minefieldParameters);

    EXPECT_EQ(minefield.getRowsCount() * minefield.getColumnsCount(), 100);
}

TEST_F(MinefieldTest, MinefieldSize2)
{
    const MinefieldParameters minefieldParameters(13, 21, 20);
    const Minefield minefield(minefieldParameters);

    EXPECT_EQ(minefield.getRowsCount() * minefield.getColumnsCount(), 273);
}

TEST_F(MinefieldTest, MinefieldSize3)
{
    const MinefieldParameters minefieldParameters(30, 30, 10);
    const Minefield minefield(minefieldParameters);

    EXPECT_EQ(minefield.getRowsCount() * minefield.getColumnsCount(), 900);
}
