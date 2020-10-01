#include "model/field.h"

Field::Field(const Coordinates& coordinates) : coordinates_(coordinates)
{
    fieldState_ = FieldState::COVERED;
    mineIsPresent_ = false;
}

void Field::reset()
{
    fieldState_ = FieldState::COVERED;
    mineIsPresent_ = false;
    adjacentMineCount_ = std::nullopt;
}

void Field::placeMine()
{
    if(!mineIsPresent_)
    {
        mineIsPresent_ = true;
    }
    else
    {
        throw std::runtime_error("Cannot put mine on a field already containing mine.");
    }
}

void Field::uncover(bool safe)
{
    if(mineIsPresent_)
    {
        setState(FieldState::MINE_EXPLODED);
    }
    else
    {
        setState(FieldState::UNCOVERED);
    }

    emit fieldStateUpdatedEvent(*this);
}

void Field::setMine()
{
    if(mineIsPresent_)
    {
        throw std::runtime_error("Cannot place mine on field already containing mine");
    }
    else
    {
        mineIsPresent_ = true;
    }
}

void Field::setState(FieldState newFieldState)
{
    if(fieldState_ == FieldState::COVERED)
    {
        if(newFieldState == FieldState::COVERED)
        {
            throw std::runtime_error("Unsupported state transition");
        }
        else if(newFieldState == FieldState::UNCOVERED)
        {
            fieldState_ = newFieldState;
        }
        else if(newFieldState == FieldState::FLAGGED)
        {
            fieldState_ = newFieldState;
        }
        else if(newFieldState == FieldState::MINE_EXPLODED)
        {
            fieldState_ = newFieldState;
        }
    }
    else if(fieldState_ == FieldState::UNCOVERED)
    {
        if(newFieldState == FieldState::COVERED)
        {
            throw std::runtime_error("Unsupported state transition");
        }
        else if(newFieldState == FieldState::UNCOVERED)
        {
            throw std::runtime_error("Unsupported state transition");
        }
        else if(newFieldState == FieldState::FLAGGED)
        {
            throw std::runtime_error("Unsupported state transition");
        }
        else if(newFieldState == FieldState::MINE_EXPLODED)
        {
            throw std::runtime_error("Unsupported state transition");
        }
    }
    else if(fieldState_ == FieldState::FLAGGED)
    {
        if(newFieldState == FieldState::COVERED)
        {
            fieldState_ = newFieldState;
        }
        else if(newFieldState == FieldState::UNCOVERED)
        {
            /*Permitted only during uncovering adjacent empty fields*/
            fieldState_ = newFieldState;
        }
        else if(newFieldState == FieldState::FLAGGED)
        {
            throw std::runtime_error("Unsupported state transition");
        }
        else if(newFieldState == FieldState::MINE_EXPLODED)
        {
            throw std::runtime_error("Unsupported state transition");
        }
    }
    else if(fieldState_ == FieldState::MINE_EXPLODED)
    {
        if(newFieldState == FieldState::COVERED)
        {
            throw std::runtime_error("Unsupported state transition");
        }
        else if(newFieldState == FieldState::UNCOVERED)
        {
            throw std::runtime_error("Unsupported state transition");
        }
        else if(newFieldState == FieldState::FLAGGED)
        {
            throw std::runtime_error("Unsupported state transition");
        }
        else if(newFieldState == FieldState::MINE_EXPLODED)
        {
            throw std::runtime_error("Unsupported state transition");
        }
    }
    else
    {
        throw std::runtime_error("Unsupported field state");
    }

    emit fieldStateUpdatedEvent(*this);
}
