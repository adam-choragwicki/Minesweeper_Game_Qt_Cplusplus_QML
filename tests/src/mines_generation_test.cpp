#include "common_test_fixture.h"
#include "model/minefield.h"
#include "mines_generator.h"
#include "model/field.h"

class MinesGeneratorTest : public CommonTestFixture
{};

int getMinesCount(const Minefield& minefield)
{
    const CoordinatesToFieldsMapping& coordinatesToFieldsMapping = minefield.getCoordinatesToFieldsMapping();

    int mineCount = 0;

    for(auto& [coordinates, field] : coordinatesToFieldsMapping)
    {
        if(field->isMinePresent())
        {
            ++mineCount;
        }
    }

    return mineCount;
}

TEST_F(MinesGeneratorTest, CheckNumberOfGeneratedMines1)
{
    MinefieldParameters minefieldParameters(10, 10, 10);
    Minefield minefield(minefieldParameters);
    MineGenerator::generateMines(minefieldParameters, minefield);

    EXPECT_EQ(getMinesCount(minefield), 10);
}

TEST_F(MinesGeneratorTest, CheckNumberOfGeneratedMines2)
{
    MinefieldParameters minefieldParameters(10, 10, 20);
    Minefield minefield(minefieldParameters);
    MineGenerator::generateMines(minefieldParameters, minefield);

    EXPECT_EQ(getMinesCount(minefield), 20);
}

TEST_F(MinesGeneratorTest, CheckNumberOfGeneratedMines3)
{
    MinefieldParameters minefieldParameters(20, 15, 20);
    Minefield minefield(minefieldParameters);
    MineGenerator::generateMines(minefieldParameters, minefield);

    EXPECT_EQ(getMinesCount(minefield), 60);
}

TEST_F(MinesGeneratorTest, CheckNumberOfGeneratedMines4)
{
    MinefieldParameters minefieldParameters(17, 12, 30);
    Minefield minefield(minefieldParameters);
    MineGenerator::generateMines(minefieldParameters, minefield);

    EXPECT_EQ(getMinesCount(minefield), 61);
}

TEST_F(MinesGeneratorTest, CheckNumberOfGeneratedMines5)
{
    MinefieldParameters minefieldParameters(17, 12, 20);
    Minefield minefield(minefieldParameters);
    MineGenerator::generateMines(minefieldParameters, minefield);

    EXPECT_EQ(getMinesCount(minefield), 40);
}
