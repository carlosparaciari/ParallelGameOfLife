/*=============================================================================

  GameOfLife: Let us mix together the Game of Life and parallel programming.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "golSerialGame.h"

namespace gol {

	/// The class constructor.
 	SerialGame::SerialGame(game_parameters game_settings) {
 		m_game_settings = game_settings;
 	}

	/// Method to evolve a frame by one time step.
	void SerialGame::evolve(frame & current_frame) {}

  /// Method to count the alive cells in the neighbourhood of a given cell.
	int SerialGame::count_alive_neighbours(int x_coord, int y_coord, frame & current_frame) {

		if ( current_frame.empty() ) {
			std::string message = std::string("The frame is empty.");
      throw std::runtime_error(message);
		}

		bool notsame_x_size = current_frame.size() != m_game_settings.number_x_cells;
		bool notsame_y_size = current_frame[0].size() != m_game_settings.number_y_cells;

		if ( notsame_x_size || notsame_y_size ) {
			std::string message = std::string("The frame size is not correct.");
      throw std::runtime_error(message);
		}

		bool x_out_of_range = ( x_coord < 0 ) || ( x_coord >= m_game_settings.number_x_cells );
		bool y_out_of_range = ( y_coord < 0 ) || ( y_coord >= m_game_settings.number_y_cells );

		if (x_out_of_range || y_out_of_range) {
			std::string message = std::string("The coordinate is out of range.");
      throw std::runtime_error(message);
		}

    int number_alive_cells = 0;

    bool alive_centre = current_frame[x_coord][y_coord] == alive;
    if ( alive_centre )
    	number_alive_cells += -1;

    int delta = 1;

		for ( int i = x_coord - delta ; i <= x_coord + delta ; ++i ) {
			for ( int j = y_coord - delta ; j <= y_coord + delta ; ++j ) {
				bool bad_coord = (i < 0) ||
												 (j < 0) ||
												 (i >= m_game_settings.number_x_cells) ||
												 (j >= m_game_settings.number_y_cells);
				if ( !bad_coord ) {
					bool alive_cell = current_frame[i][j] == alive;
					if ( alive_cell )
						number_alive_cells += 1;
				}
			}
		}

		return number_alive_cells;

	}

	/// Method to change the state of a cell depending on the number of closeby alive cells.
  cell SerialGame::change_state_cell(int alive_neighbours, cell current_state) {

  	if ( current_state == alive) {
  		if ( alive_neighbours < 2 )
  			return dead;
  		if ( (alive_neighbours == 2) || (alive_neighbours == 3) )
  			return alive;
  		if ( alive_neighbours > 3 )
  			return dead;
  	}

  	if ( current_state == dead) {
  		if ( alive_neighbours == 3 )
  			return alive;
  		else
  			return dead;
  	}

  }

} // end namespace
