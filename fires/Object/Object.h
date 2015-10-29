/**
 * @file    Object.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES__OBJECT_H__
#define __FIRES__OBJECT_H__

#include <fires/api.h>
#include "../Property/Property.h"

#include <string>
#include <map>

namespace fires
{

  namespace detail
  {
    class Object;
  }

  /*! \class Object
    \brief A class to represent objects that can be used in fires.

    This class provides access to object properties and properties
  */
  class FIRES_API Object
  {

  public:

    /**
     * Default constructor
     */
    Object( );

    /**
     * Copy constructor
     */
    Object( Object& object );

    /**
     * Destructor
     */
    virtual ~Object( );

    /**
     * Register a property to this object
     * @param label label string for the property
     * @param property property to be added
     */
    void registerProperty( const std::string& label, const Property& property );

    /**
     * Unregister a property of this object
     * @param label label of the property to be deleted
     * @return true if the property could be deleted
     */
    bool unregisterProperty( const std::string& label );

    /**
     * Get a property of this object
     * @param label label string to retrieve the property
     * @return the property if found and throw exception otherwise
     */
    Property& getProperty( const std::string& label );

    /**
     * Get a property of this object as const
     * @param label label string to retrieve the property
     * @return the property if found and throw exception otherwise
     */
    const Property& getProperty( const std::string& label ) const;

    /**
     * Get a property of this object
     * @param label label string to retrieve the property
     * @param property property to be setted
     * @return true in case property was setted, false otherwise
     */
    bool setProperty( const std::string& label, const Property& property);

    /**
     * Queries if a property has been registered in this object
     * @param label label string to retrieve the property
     * @return true if found
     */
    bool hasProperty( const std::string& label ) const;

    /**
     * Clears the properties of this object (no memory freeing)
     */
    void clearProperties( void );

    /**
     * Get all properties
     * @return map with all properties
     */
    std::map< std::string, Property >& getProperties( void );

    /**
     * Get a reference to the label of the object
     * @return reference to label
     */
    std::string& label( void );

    /**
     * Get the label of the object
     * @return label of the object
     */
    std::string label( void ) const;

  protected:

    detail::Object* _impl;

  };


}

#endif