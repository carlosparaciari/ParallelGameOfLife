/*=============================================================================

  GameOfLife: Let us mix together the Game of Life and parallel programming.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef golInOutFrames_h
#define golInOutFrames_h

#include "golWin32ExportHeader.h"
#include "golBasicTypes.h"
#include <string>
#include <fstream>
#include <exception>
#include <array>
#include <algorithm>

/**
* \file golInOutFrames.h
* \brief This class handles the input and output of frames (Life 1.06 format).
* \ingroup utilities
*/
namespace gol
{

/**
* \brief The class InOutFrames handle the input and output files which are used by the class which evolves the system.
*
* This class provides methods to load a seed pattern (an initial condition) into the game, as well as some configuration
* parameters (number of iterations, size of the region). In addition it provides methods to save each frame into a different
* file (with the format Life 1.06), and to create a yaml configuration file for the script which creates a movies out of
* these frames.
*/
GAMEOFLIFE_WINEXPORT class InOutFrames {

  public:

  	/// The class constructor.
  	/**
    * \param seed_file_name is the name of the file containing the input frame.
    * \param config_file_name is the name of the file containing the configuration parameters of the game.
    */
  	InOutFrames(std::string seed_file_name, std::string config_file_name);

  	/// The class destructor.
  	~InOutFrames() {};

  	/// Method to load the parameters from the configuration file.
    /**
    * \return a structure game_parameters defining the number of x and y cells in a frame, and the number of time steps of the evolution.
    *
    * The method returns the parameters needed for the game, and saves
    * some additional information such as the name and extension of the
    * files where the frames are saved.
    */
  	game_parameters load_configuration_parameters();

  	/// Method to save the parameters into a configuration file for the video script.
    /**
    * The parameters needed by the MakeVideo script are saved in a yaml file. These
    * parameters are the size of the box, the time steps, the name of the files
    * where the frames are saved, and their extension.
    */
  	void save_configuration_to_file();

  	/// Method to load the seed pattern into the initial frame.
    /**
    * \param initial_frame is a matrix of cells, each of them either alive or dead.
    */
  	void load_seed_frame(frame & initial_frame);

  	/// Method to save the current frame into an output file.
    /**
    * \param current_frame is a matrix of cells, each of them either alive or dead.
    * \param iteration is the time step at which the frame was obtained.
    *
    * The method saves the frame into an output file whose name and extension are defined
    * by the iteration value and the config file provided to the class constructor.
    */
  	void save_frame_to_file(frame & current_frame, int iteration);

  private:

  	std::string m_seed_file_name; /**< The name of the file which contains the seed pattern. */
  	std::string m_config_file_name; /**< The name of the file which contains the configuration parameters. */

  	game_parameters m_game_settings; /**< The main settings for the game: number of x and y cells, and number of time steps. */

  	std::string m_frame_file_name; /**< Name of the output files where the frames are saved. */
  	std::string m_extension; /**< extension of the frames. */

};

} // end namespace

#endif
