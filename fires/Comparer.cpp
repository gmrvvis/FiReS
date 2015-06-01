/**
 * @file    Comparer.cpp
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */

#include "Comparer.h"

#include <iostream>
#include <math.h>

namespace fires
{

  Comparer::~Comparer( void )
  {

  }

  float Comparer::distance( Feature* f1, Feature* f2 ) const
  {
    std::cerr << "FiReS: no distance function provided "
              << "in the comparer. Returning 0. "
              << "f1 = " << f1 << " f2 = " << f2
              << std::endl;
    return 0.0f;
  }

}
