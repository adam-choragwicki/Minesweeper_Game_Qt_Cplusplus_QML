#include "tiles_uncoverer.h"
#include "tile.h"
#include "tiles_manager.h"
#include <ranges>
#include <deque>


/**
 * This function performs a classic Minesweeper "flood fill":
 *
 * Starting from a tile that has already been uncovered AND has adjacentMineCount == 0, we automatically uncover all connected empty tiles (tiles with adjacentMineCount == 0),
 * and also uncover the "border" tiles around them (tiles with adjacentMineCount > 0).
 *
 * IMPORTANT:
 * - Mines are NEVER uncovered here.
 * - Flagged tiles are NEVER touched (they are not COVERED).
 * - Each tile is uncovered at most once.
 *
 * This is implemented as an iterative Breadth-First Search (BFS) instead of recursion to avoid stack overflows on large boards.
 */
void TilesUncoverer::uncoverAdjacentEmptyTiles(Tile& start, Minefield& field)
{
    // Queue of tiles that still need to be processed. We store pointers because Tile objects are owned by Minefield and guaranteed to stay alive for the duration of the algorithm.
    std::deque<Tile*> queue;

    // Seed the BFS with the starting tile.
    // The caller is responsible for ensuring that:
    // - 'start' is already UNCOVERED
    // - 'start' has adjacentMineCount == 0
    queue.push_back(&start);

    // Process tiles until no more empty-connected tiles remain
    while (!queue.empty())
    {
        // Take the next tile to process
        const Tile* tile = queue.front();
        queue.pop_front();

        // Examine all tiles adjacent to the current tile. Adjacent means up to 8 neighbors (including diagonals), but fewer on edges and corners.
        for (Tile* adjacentTile: TilesManager::getAdjacentTiles(tile->getCoordinates(), field))
        {
            /*
             * We only care about tiles that are:
             * - still COVERED (not uncovered yet, not flagged)
             * - not containing a mine
             *
             * Anything else is ignored:
             * - UNCOVERED tiles were already processed
             * - FLAGGED tiles must stay untouched
             * - MINE tiles must never be uncovered automatically
             */
            if (adjacentTile->getState() == Tile::State::COVERED && !adjacentTile->isMinePresent())
            {
                // Uncover the tile as part of the flood fill
                adjacentTile->uncover();

                /*
                 * If this newly uncovered tile has zero adjacent mines, it means it is also an "empty" tile.
                 * In that case, we need to continue the flood fill from this tile as well, so we add it to the queue.
                 * If adjacentMineCount > 0, this tile forms the "border" of the empty area and should NOT expand further.
                 */
                if (adjacentTile->getAdjacentMineCount() == 0)
                {
                    queue.push_back(adjacentTile);
                }
            }
        }
    }
}

[[maybe_unused]] void TilesUncoverer::debug_UncoverAllTiles(const Minefield& minefield)
{
    for (const auto& tile: minefield | std::views::values)
    {
        tile->uncover();
    }
}
