/**
 * @file    Engine.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__ENGINE_H__
#define __FIRES__ENGINE_H__


#include "Comparer.h"
#include "Object.h"
#include "Objects.h"
#include "SearchConfig.h"
#include "Task.h"

#include <vector>
#include <map>


namespace fires
{

  /*! \class Engine
    \brief FiReS engine

    Provides the entry point for objects, comparers and results
  */
  class Engine
  {

  public:

    /**
     * Default destructor
     **/
    FIRES_API
    virtual ~Engine( );


    FIRES_API
    virtual void run( Objects& objects, Tasks& tasks );

  };


}

#endif
