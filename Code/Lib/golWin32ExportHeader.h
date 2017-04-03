/*=============================================================================

  GameOfLife: Let us mix together the Game of Life and parallel programming.

  Copyright (c) University College London (UCL). All rights reserved.

  This software is distributed WITHOUT ANY WARRANTY; without even
  the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
  PURPOSE.

  See LICENSE.txt in the top level directory for details.

=============================================================================*/

#ifndef golWin32ExportHeader_h
#define golWin32ExportHeader_h

/**
* \file golWin32ExportHeader.h
* \brief Header to sort Windows dllexport/dllimport.
*/

#if (defined(_WIN32) || defined(WIN32)) && !defined(GAMEOFLIFE_STATIC)
  #ifdef GAMEOFLIFE_WINDOWS_EXPORT
    #define GAMEOFLIFE_WINEXPORT __declspec(dllexport)
  #else
    #define GAMEOFLIFE_WINEXPORT __declspec(dllimport)
  #endif  /* GAMEOFLIFE_WINEXPORT */
#else
/* linux/mac needs nothing */
  #define GAMEOFLIFE_WINEXPORT
#endif

#endif
