#include "common_test_fixture.h"
#include "fields_manager.h"
#include "fields_uncoverer.h"
#include "model/field.h"

class FieldUncovererTest : public CommonTestFixture
{
private:
    void SetUp() override
    {}
};

TEST_F(FieldUncovererTest, UncoverAdjacentEmptyFields1)
{
    MinefieldParameters minefieldParameters(4, 4, 10);
    Minefield minefield(minefieldParameters);

    minefield.setMine(Coordinates(1, 4));

    FieldsManager::assignAdjacentMinesCountToAllFields(minefield);

    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 1))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 2))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 3))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 4))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 1))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 2))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 3))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 4))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 1))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 2))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 3))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 4))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 1))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 2))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 3))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 4))->getState(), FieldState::COVERED);

    auto& field = minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 1));
    FieldsUncoverer::uncoverAdjacentEmptyFields(*field, minefield);

    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 1))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 2))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 3))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 4))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 1))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 2))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 3))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 4))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 1))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 2))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 3))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 4))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 1))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 2))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 3))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 4))->getState(), FieldState::UNCOVERED);
}

TEST_F(FieldUncovererTest, UncoverAdjacentEmptyFields2)
{
    MinefieldParameters minefieldParameters(4, 4, 10);
    Minefield minefield(minefieldParameters);

    minefield.setMine(Coordinates(1, 1));
    minefield.setMine(Coordinates(4, 1));
    minefield.setMine(Coordinates(4, 4));

    FieldsManager::assignAdjacentMinesCountToAllFields(minefield);

    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 1))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 2))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 3))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 4))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 1))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 2))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 3))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 4))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 1))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 2))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 3))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 4))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 1))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 2))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 3))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 4))->getState(), FieldState::COVERED);

    auto& field = minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 4));
    FieldsUncoverer::uncoverAdjacentEmptyFields(*field, minefield);

    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 1))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 2))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 3))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(1, 4))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 1))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 2))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 3))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(2, 4))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 1))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 2))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 3))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(3, 4))->getState(), FieldState::UNCOVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 1))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 2))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 3))->getState(), FieldState::COVERED);
    EXPECT_EQ(minefield.getCoordinatesToFieldsMapping().at(Coordinates(4, 4))->getState(), FieldState::COVERED);
}
