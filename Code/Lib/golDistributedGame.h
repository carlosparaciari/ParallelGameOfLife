/*=============================================================================

  GameOfLife: Let us mix together the Game of Life and parallel programming.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef golDistributedGame_h
#define golDistributedGame_h

#include "golWin32ExportHeader.h"
#include "golBasicTypes.h"
#include "golGameOfLife.h"
#include <string>
#include <stdexcept>
#include <mpi.h>


/**
* \file golDistributedGame.h
* \brief This class evolves the system with a distributed (OpenMPI) solution
* \ingroup utilities
*/
namespace gol
{

/**
* \brief The class DistributedGame implements the game usign OpenMPI. 
*/
GAMEOFLIFE_WINEXPORT class DistributedGame : public GameOfLife {

  public:

  	/// The class constructor.
  	/**
    * \param game_settings specifies the size of the grid in which the game is played.
    */
  	DistributedGame(game_parameters game_settings);

		/// Method to evolve a frame by one time step.
		void evolve(frame & current_frame);

	protected:

    /// Method to count the alive cells in the neighbourhood of a given cell.
		int count_alive_neighbours(int x_coord, int y_coord, frame & current_frame);

		/// Method to change the state of a cell depending on the number of closeby alive cells.
	  cell change_state_cell(int alive_neighbours, cell current_state);

	private:

		game_parameters m_game_settings; /**< The main settings for the game: number of x and y cells, and number of time steps. */

};

} // end namespace

#endif
