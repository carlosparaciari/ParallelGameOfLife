/*=============================================================================

  GameOfLife: Let us mix together the Game of Life and parallel programming.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "golInOutFrames.h"

namespace gol {

	/// The class constructor.
  InOutFrames::InOutFrames(std::string seed_file_name, std::string config_file_name) {

  	m_seed_file_name = seed_file_name;
  	m_config_file_name = config_file_name;

  }

  /// Method to load the parameters from the configuration file.
	game_parameters InOutFrames::load_configuration_parameters() {

		std::fstream filein;
		filein.open( m_config_file_name );

    if ( !filein.is_open() ) {
      std::string message = std::string("The configuration file cannot be opened.");
      throw std::runtime_error(message);
    }

    std::string definition;
    std::string value;

    std::array<int,5> fill_check;
    std::fill( fill_check.begin(), fill_check.end(), 0 );

    while ( true ) {
    	
    	std::getline(filein, definition, ' ');
    	std::getline(filein, value);

    	if ( filein.eof() )
    		break;

    	if ( definition == std::string("number_of_x_cells") ) {
        m_game_settings.number_x_cells = std::stoi( value );
        fill_check[0]++;
    	}
      else if ( definition == std::string("number_of_y_cells") ) {
        m_game_settings.number_y_cells = std::stoi( value );
        fill_check[1]++;
    	}
      else if ( definition == std::string("time_steps") ) {
        m_game_settings.time_steps = std::stoi( value );
        fill_check[2]++;
      }
      else if ( definition == std::string("output_filename") ) {
        m_frame_file_name = value;
        fill_check[3]++;
      }
      else if ( definition == std::string("extension") ) {
        m_extension = value;
        fill_check[4]++;
      }
      else {
        std::string message = std::string("There is an additional or misspelled parameter in the config file.");
      	throw std::runtime_error(message);
   		}

		}

    filein.close();

    bool all_field_filled = std::all_of( fill_check.begin(), fill_check.end(), [](int field){return field == 1;} );

    if ( !all_field_filled ) {
      std::string message = std::string("Not all fields have been filled. Please complete the configuration file.");
      throw std::runtime_error(message);
    }

    return m_game_settings;
	}

	/// Method to save the parameters into a configuration file for the video script.
	void InOutFrames::save_configuration_to_file() {}

	/// Method to load the seed pattern into the initial frame.
  void InOutFrames::load_seed_frame(frame & initial_frame) {}

  /// Method to save the current frame into an output file.
	void InOutFrames::save_frame_to_file(frame & current_frame, int iteration) {}

} // end namespace
