#include "common_test_fixture.h"
#include "fields_manager.h"
#include "model/field.h"

class FieldManagerTest : public CommonTestFixture
{
private:
    void SetUp() override
    {}
};

/*100 fields, 0 mines, 0 uncovered, 0 flags*/
TEST_F(FieldManagerTest, CountCoveredFieldsWithoutMine1)
{
    MinefieldParameters minefieldParameters(10, 10, 10);
    Minefield minefield(minefieldParameters);

    EXPECT_EQ(FieldsManager::countRemainingCoveredFieldsWithoutMine(minefield), 100);
}

/*150 fields, 0 mines, 0 uncovered, 0 flags*/
TEST_F(FieldManagerTest, CountCoveredFieldsWithoutMine2)
{
    MinefieldParameters minefieldParameters(10, 15, 10);
    Minefield minefield(minefieldParameters);

    EXPECT_EQ(FieldsManager::countRemainingCoveredFieldsWithoutMine(minefield), 150);
}

/*100 fields, 2 mines, 0 uncovered, 0 flags*/
TEST_F(FieldManagerTest, CountCoveredFieldsWithoutMine3)
{
    MinefieldParameters minefieldParameters(10, 10, 10);
    Minefield minefield(minefieldParameters);

    minefield.setMine(Coordinates(1, 2));
    minefield.setMine(Coordinates(7, 5));

    EXPECT_EQ(FieldsManager::countRemainingCoveredFieldsWithoutMine(minefield), 98);
}

/*100 fields, 6 mines, 0 uncovered, 3 flags*/
TEST_F(FieldManagerTest, CountCoveredFieldsWithoutMine4)
{
    MinefieldParameters minefieldParameters(10, 10, 10);
    Minefield minefield(minefieldParameters);

    minefield.setMine(Coordinates(1, 2));
    minefield.setMine(Coordinates(4, 1));
    minefield.setMine(Coordinates(8, 10));
    minefield.setMine(Coordinates(7, 6));
    minefield.setMine(Coordinates(5, 5));
    minefield.setMine(Coordinates(10, 6));

    minefield.getCoordinatesToFieldsMapping().at(Coordinates(8, 2))->setState(FieldState::FLAGGED);
    minefield.getCoordinatesToFieldsMapping().at(Coordinates(7, 3))->setState(FieldState::FLAGGED);
    minefield.getCoordinatesToFieldsMapping().at(Coordinates(9, 2))->setState(FieldState::FLAGGED);

    EXPECT_EQ(FieldsManager::countRemainingCoveredFieldsWithoutMine(minefield), 94);
}

/*900 fields, 6 mines, 5 uncovered, 3 flags*/
TEST_F(FieldManagerTest, CountCoveredFieldsWithoutMine5)
{
    MinefieldParameters minefieldParameters(30, 30, 10);
    Minefield minefield(minefieldParameters);

    minefield.setMine(Coordinates(1, 2));
    minefield.setMine(Coordinates(4, 1));
    minefield.setMine(Coordinates(8, 10));
    minefield.setMine(Coordinates(19, 6));
    minefield.setMine(Coordinates(5, 5));
    minefield.setMine(Coordinates(10, 6));

    minefield.getCoordinatesToFieldsMapping().at(Coordinates(15, 6))->setState(FieldState::FLAGGED);
    minefield.getCoordinatesToFieldsMapping().at(Coordinates(16, 5))->setState(FieldState::FLAGGED);
    minefield.getCoordinatesToFieldsMapping().at(Coordinates(17, 3))->setState(FieldState::FLAGGED);

    minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 4))->uncover();
    minefield.getCoordinatesToFieldsMapping().at(Coordinates(5, 6))->uncover();
    minefield.getCoordinatesToFieldsMapping().at(Coordinates(7, 8))->uncover();
    minefield.getCoordinatesToFieldsMapping().at(Coordinates(9, 10))->uncover();
    minefield.getCoordinatesToFieldsMapping().at(Coordinates(11, 12))->uncover();

    EXPECT_EQ(FieldsManager::countRemainingCoveredFieldsWithoutMine(minefield), 889);
}

TEST_F(FieldManagerTest, GetAdjacentFields)
{
    MinefieldParameters minefieldParameters(10, 10, 10);
    Minefield minefield(minefieldParameters);

    std::vector<Field*> adjacentFields1 = FieldsManager::getAdjacentFields(Coordinates(1, 1), minefield);

    EXPECT_EQ(adjacentFields1.size(), 3);
    EXPECT_EQ(adjacentFields1.at(0)->getCoordinates(), Coordinates(1, 2));
    EXPECT_EQ(adjacentFields1.at(1)->getCoordinates(), Coordinates(2, 1));
    EXPECT_EQ(adjacentFields1.at(2)->getCoordinates(), Coordinates(2, 2));

    auto adjacentFields2 = FieldsManager::getAdjacentFields(Coordinates(5, 10), minefield);

    EXPECT_EQ(adjacentFields2.size(), 5);
    EXPECT_EQ(adjacentFields2.at(0)->getCoordinates(), Coordinates(4, 9));
    EXPECT_EQ(adjacentFields2.at(1)->getCoordinates(), Coordinates(4, 10));
    EXPECT_EQ(adjacentFields2.at(2)->getCoordinates(), Coordinates(5, 9));
    EXPECT_EQ(adjacentFields2.at(3)->getCoordinates(), Coordinates(6, 9));
    EXPECT_EQ(adjacentFields2.at(4)->getCoordinates(), Coordinates(6, 10));

    auto adjacentFields3 = FieldsManager::getAdjacentFields(Coordinates(5, 5), minefield);

    EXPECT_EQ(adjacentFields3.size(), 8);
    EXPECT_EQ(adjacentFields3.at(0)->getCoordinates(), Coordinates(4, 4));
    EXPECT_EQ(adjacentFields3.at(1)->getCoordinates(), Coordinates(4, 5));
    EXPECT_EQ(adjacentFields3.at(2)->getCoordinates(), Coordinates(4, 6));
    EXPECT_EQ(adjacentFields3.at(3)->getCoordinates(), Coordinates(5, 4));
    EXPECT_EQ(adjacentFields3.at(4)->getCoordinates(), Coordinates(5, 6));
    EXPECT_EQ(adjacentFields3.at(5)->getCoordinates(), Coordinates(6, 4));
    EXPECT_EQ(adjacentFields3.at(6)->getCoordinates(), Coordinates(6, 5));
    EXPECT_EQ(adjacentFields3.at(7)->getCoordinates(), Coordinates(6, 6));
}

TEST_F(FieldManagerTest, AssignAdjacentMinesCountToAllFields)
{
    MinefieldParameters minefieldParameters(3, 3, 10);
    Minefield minefield(minefieldParameters);

    minefield.setMine(Coordinates(1, 1));
    minefield.setMine(Coordinates(2, 2));
    minefield.setMine(Coordinates(3, 1));

    FieldsManager::assignAdjacentMinesCountToAllFields(minefield);

    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 2))->getAdjacentMineCount(), 2);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 3))->getAdjacentMineCount(), 1);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 1))->getAdjacentMineCount(), 3);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 3))->getAdjacentMineCount(), 1);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 2))->getAdjacentMineCount(), 2);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 3))->getAdjacentMineCount(), 1);

    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 1))->getAdjacentMineCount(), std::nullopt);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 2))->getAdjacentMineCount(), std::nullopt);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 1))->getAdjacentMineCount(), std::nullopt);
}
