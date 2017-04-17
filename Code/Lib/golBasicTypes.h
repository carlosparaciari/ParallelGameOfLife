/*=============================================================================

  GameOfLife: Let us mix together the Game of Life and parallel programming.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef golBasicTypes_h
#define golBasicTypes_h

#include "golWin32ExportHeader.h"
#include <vector>

/**
* \defgroup internal internal
* \brief Internal stuff, not for end-users.
*/

/**
* \defgroup types types
* \brief Package-wide data types.
*/

/**
* \defgroup utilities utilities
* \brief Groups of c-style functions.
*/

/**
* \defgroup applications applications
* \brief Small, end-user applications, most likely command line.
*/

/**
* \file golBasicTypes.h
* \brief Defines types used in this library.
* \ingroup types
*/

//! Single namespace for all code in this package
namespace gol
{

	/// Structure for the main parameters of the game.
  struct game_parameters {
  	int number_x_cells; /**< The total number of cells in the x direction. */
  	int number_y_cells; /**< The total number of cells in the y direction. */
  	int time_steps; /**< The total number of steps we want to evolve the system. */
	};

  /// Enum type with the two possible states of a cell.
	enum cell {
    dead,
    alive
  };

  /// Type frame, is a matrix of cells.
  typedef std::vector<std::vector<cell>> frame;

} // end namespace

#endif
