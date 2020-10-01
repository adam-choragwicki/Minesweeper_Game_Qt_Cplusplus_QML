#include "fields_uncoverer.h"
#include "model/field.h"
#include "fields_manager.h"

void FieldsUncoverer::uncoverAdjacentEmptyFields(const Field& field, Minefield& minefield)
{
    std::vector<Field*> adjacentFields = FieldsManager::getAdjacentFields(field.getCoordinates(), minefield);

    for(auto& adjacentField : adjacentFields)
    {
        FieldState adjacentFieldState = adjacentField->getState();

        if(adjacentFieldState == FieldState::COVERED || adjacentFieldState == FieldState::FLAGGED)
        {
            adjacentField->uncover();

            if(adjacentField->getAdjacentMineCount() == 0)
            {
                uncoverAdjacentEmptyFields(*adjacentField, minefield);
            }
        }
    }
}

[[maybe_unused]] void FieldsUncoverer::debug_UncoverAllFields(const Minefield& minefield)
{
    for(auto& [coordinates, field] : minefield.getCoordinatesToFieldsMapping())
    {
        field->uncover();
    }
}
