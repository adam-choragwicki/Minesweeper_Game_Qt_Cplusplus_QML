#include "common_test_fixture.h"
#include "model/minefield.h"
#include "model/field.h"

class FieldTest : public CommonTestFixture
{};

TEST_F(FieldTest, CheckFieldDefaultParametersAfterCreation)
{
    Field field(Coordinates(3, 5));

    EXPECT_EQ(field.getCoordinates(), Coordinates(3,5));
    EXPECT_FALSE(field.isMinePresent());
    EXPECT_TRUE(field.getState() == FieldState::COVERED);
}

TEST_F(FieldTest, CreateFieldWrongCoordinates)
{
    EXPECT_THROW(Field field(Coordinates(0, 0)), std::out_of_range);
    EXPECT_THROW(Field field(Coordinates(0, 5)), std::out_of_range);
    EXPECT_THROW(Field field(Coordinates(3, 0)), std::out_of_range);
    EXPECT_THROW(Field field(Coordinates(-5, -3)), std::out_of_range);
    EXPECT_THROW(Field field(Coordinates(-5, 3)), std::out_of_range);
    EXPECT_THROW(Field field(Coordinates(7, -1)), std::out_of_range);
}

TEST_F(FieldTest, PlaceMine)
{
    Field field(Coordinates(7, 5));

    EXPECT_FALSE(field.isMinePresent());

    field.placeMine();

    EXPECT_TRUE(field.isMinePresent());
}

TEST_F(FieldTest, PlaceMineTwice)
{
    Field field(Coordinates(1, 3));

    field.placeMine();

    EXPECT_THROW(field.placeMine(), std::runtime_error);
}

TEST_F(FieldTest, Uncover)
{
    Field field(Coordinates(7, 5));

    EXPECT_TRUE(field.getState() == FieldState::COVERED);

    field.uncover();

    EXPECT_TRUE(field.getState() == FieldState::UNCOVERED);
}

TEST_F(FieldTest, Reset)
{
    Field field(Coordinates(7, 5));

    field.reset();

    EXPECT_EQ(field.getCoordinates(), Coordinates(7,5));
    EXPECT_FALSE(field.isMinePresent());
    EXPECT_TRUE(field.getState() == FieldState::COVERED);
}
