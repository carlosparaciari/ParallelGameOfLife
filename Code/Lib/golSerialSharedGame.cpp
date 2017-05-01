/*=============================================================================

  GameOfLife: Let us mix together the Game of Life and parallel programming.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "golSerialSharedGame.h"

namespace gol {

	/// The class constructor.
 	SerialSharedGame::SerialSharedGame(game_parameters game_settings) {
 		m_game_settings = game_settings;
 	}

	/// Method to evolve a frame by one time step.
	void SerialSharedGame::evolve(frame & current_frame) {

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

		frame next_frame(m_game_settings.number_x_cells, std::vector<gol::cell>(m_game_settings.number_y_cells, gol::dead));
		int number_alive_cells;

		#pragma omp parallel private(number_alive_cells), shared(next_frame)
		{
			#pragma omp for collapse(2)
			for ( int i = 0 ; i < m_game_settings.number_x_cells ; ++i ) {
				for ( int j = 0 ; j < m_game_settings.number_y_cells ; ++j ) {
					number_alive_cells = count_alive_neighbours(i, j, current_frame);
					next_frame[i][j] = change_state_cell(number_alive_cells, current_frame[i][j]);
				}
			}
		}

		current_frame = next_frame;

	}

  /// Method to count the alive cells in the neighbourhood of a given cell.
	int SerialSharedGame::count_alive_neighbours(int x_coord, int y_coord, frame & current_frame) {

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
  cell SerialSharedGame::change_state_cell(int alive_neighbours, cell current_state) {

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
