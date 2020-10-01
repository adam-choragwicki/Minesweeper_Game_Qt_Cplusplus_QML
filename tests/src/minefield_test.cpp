#include "common_test_fixture.h"
#include "model/minefield.h"
#include "model/field.h"

class MinefieldTest : public CommonTestFixture
{};

TEST_F(MinefieldTest, MinefieldSize1)
{
    MinefieldParameters minefieldParameters(10, 10, 10);
    Minefield minefield(minefieldParameters);

    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().size(), 100);
}

TEST_F(MinefieldTest, MinefieldSize2)
{
    MinefieldParameters minefieldParameters(13, 21, 20);
    Minefield minefield(minefieldParameters);

    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().size(), 273);
}

TEST_F(MinefieldTest, MinefieldSize3)
{
    MinefieldParameters minefieldParameters(30, 30, 10);
    Minefield minefield(minefieldParameters);

    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().size(), 900);
}
