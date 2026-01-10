#include "common_test_fixture.h"
#include "minefield.h"
#include <ranges>

class MinesGeneratorTest : public CommonTestFixture
{};

int getMinesCount(const Minefield& minefield)
{
    return std::ranges::count_if(minefield, [](const auto& coordinatesTilePair) { return coordinatesTilePair.second->isMinePresent(); });
}

TEST_F(MinesGeneratorTest, CheckNumberOfGeneratedMines1)
{
    const MinefieldParameters minefieldParameters(10, 10, 10);
    const Minefield minefield(minefieldParameters);

    EXPECT_EQ(getMinesCount(minefield), 10);
}

TEST_F(MinesGeneratorTest, CheckNumberOfGeneratedMines2)
{
    const MinefieldParameters minefieldParameters(10, 10, 20);
    const Minefield minefield(minefieldParameters);

    EXPECT_EQ(getMinesCount(minefield), 20);
}

TEST_F(MinesGeneratorTest, CheckNumberOfGeneratedMines3)
{
    const MinefieldParameters minefieldParameters(20, 15, 20);
    const Minefield minefield(minefieldParameters);

    EXPECT_EQ(getMinesCount(minefield), 60);
}

TEST_F(MinesGeneratorTest, CheckNumberOfGeneratedMines4)
{
    const MinefieldParameters minefieldParameters(17, 12, 30);
    const Minefield minefield(minefieldParameters);

    EXPECT_EQ(getMinesCount(minefield), 61);
}

TEST_F(MinesGeneratorTest, CheckNumberOfGeneratedMines5)
{
    const MinefieldParameters minefieldParameters(17, 12, 20);
    const Minefield minefield(minefieldParameters);

    EXPECT_EQ(getMinesCount(minefield), 40);
}
