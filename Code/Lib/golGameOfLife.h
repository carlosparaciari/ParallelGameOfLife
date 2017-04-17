/*=============================================================================

  GameOfLife: Let us mix together the Game of Life and parallel programming.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef golGameOfLife_h
#define golGameOfLife_h

#include "golWin32ExportHeader.h"
#include "golBasicTypes.h"

/**
* \file golGameOfLife.h
* \brief This is an abstract class that provides an interface for different implementations of the game
* \ingroup utilities
*/
namespace gol
{

/**
* \brief The class GameOfLife provides the structure we need to play the game of life.
*
* This class is the interface for the different classes which will implement the Game of life.
* The main methods that all the classes will have are in this abstract class.
* The classes which inherit from this will implement the game with different parallelising strategies.
*/
GAMEOFLIFE_WINEXPORT class GameOfLife {

  public:

		/// Method to evolve a frame by one time step.
    /**
    * \param current_frame is the frame that will be evolved by one time step.
    *
    * The method evolves the system (whose configuration is specified by the
    * input frame) using the rules of Conway's Game of Life.
    */
		virtual void evolve(frame & current_frame) = 0;

	protected:

    /// Method to count the alive cells in the neighbourhood of a given cell.
    /**
    * \param x_coord is the coordinate along the x axes of the cell whose neighbours we are interested in.
    * \param y_coord is the coordinate along the y axes of the cell whose neighbours we are interested in.
    * \return the number of alive cells around the specified one.
    */
		virtual int count_alive_neighbours(int x_coord, int y_coord) = 0;

		/// Method to change the state of a cell depending on the number of closeby alive cells.
    /**
    * \param alive_neighbours number of alive neighbours
    * \return the state of the cell (either alive of dead).
    *
    * In order to modify the state of the cell, the rules of the game are used.
    */
		virtual cell change_state_cell(int alive_neighbours) = 0;

};

} // end namespace

#endif
