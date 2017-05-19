/*=============================================================================

  GameOfLife: Let us mix together the Game of Life and parallel programming.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#define CATCH_CONFIG_RUNNER  // This tells Catch we provide main.
#include "catch.hpp"
#include "golCatchMain.h"

#ifdef BUILD_OpenMPI
#include <mpi.h>
#endif

// Global! Only do this in a private test harness.
namespace gol
{
int argc;
char** argv;
}

int main (int argc, char * const argv[])
{
  gol::argc = argc;
  gol::argv = const_cast<char**>(argv);

  Catch::Session session; // There must be exactly once instance

  int tmpArgc = 1;
  char *tmpCommandName = new char[256];
  strcpy(tmpCommandName, argv[0]);

  int returnCode = session.applyCommandLine(tmpArgc, const_cast<char * const *>(&tmpCommandName));
  if(returnCode != 0) // Indicates a command line error
    return returnCode;

#ifdef BUILD_OpenMPI
  MPI_Init (&gol::argc, &gol::argv);
#endif

  int sessionReturnCode = session.run();

#ifdef BUILD_OpenMPI
  MPI_Finalize();
#endif

  delete [] tmpCommandName;
  return sessionReturnCode;
}

