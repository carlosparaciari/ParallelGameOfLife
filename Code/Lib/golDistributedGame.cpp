/*=============================================================================

  GameOfLife: Let us mix together the Game of Life and parallel programming.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "golDistributedGame.h"

namespace gol {

	/// The class constructor.
 	DistributedGame::DistributedGame(game_parameters game_settings) {

 	}

	/// Method to evolve a frame by one time step.
	void DistributedGame::evolve(frame & current_frame) {

	}

  /// Method to count the alive cells in the neighbourhood of a given cell.
	int DistributedGame::count_alive_neighbours(int x_coord, int y_coord, frame & current_frame) {

	}

	/// Method to change the state of a cell depending on the number of closeby alive cells.
  cell DistributedGame::change_state_cell(int alive_neighbours, cell current_state) {

  }

} // end namespace
