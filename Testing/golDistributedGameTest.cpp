/*=============================================================================

  GameOfLife: Let us mix together the Game of Life and parallel programming.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#include "catch.hpp"
#include "golCatchMain.h"

#ifndef BUILD_OpenMPI
TEST_CASE("Fail the tests if we are not building MPI") {
    REQUIRE(false);
}
#endif

#ifdef BUILD_OpenMPI

#include <mpi.h>

TEST_CASE("Test that MPI is working") {
    int rank, size;
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    CHECK(size > 0);
    CHECK(rank >= 0);
}

#endif


