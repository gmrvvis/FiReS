/**
 * @file    Filter.h
 * @brief
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date
 * @remarks Copyright (c) GMRV/URJC. All rights reserved.
 *          Do not distribute without further notice.
 */
#ifndef __FIRES_FILTER_H__
#define __FIRES_FILTER_H__

#include "Task.h"

namespace fires
{

  class Filter
  {

  public:
    virtual ~Filter( )
    {
    }

    virtual bool eval( const Feature& ) const = 0;

  };

  class FilterRange
    : public Filter
  {
  public:
    typedef enum
    {
      INSIDE_RANGE = 0,
      OUTSIDE_RANGE
    } TRangeInclusion;

    typedef enum
    {
      CLOSED_ENDPOINT = 0,
      OPENED_ENDPOINT
    } TRangeEndpoint;

  };

  template < typename T >
  class FilterScalarRange
    : public FilterRange
  {

  public:

    virtual ~FilterScalarRange( void )
    {
    }

    FilterScalarRange( const T min_, //= -1.0f, // std::numeric_limits< T >::min,
                       const T max_, // = 1.0f, //std::numeric_limits< T >::max,
                       const TRangeEndpoint minEndpoint_ = OPENED_ENDPOINT,
                       const TRangeEndpoint maxEndpoint_ = OPENED_ENDPOINT,
                       const TRangeInclusion rangeInclusion_ = INSIDE_RANGE )
      : _min( min_ )
      , _max( max_ )
      , _minEndpoint( minEndpoint_ )
      , _maxEndpoint( maxEndpoint_ )
      , _rangeInclusion( rangeInclusion_ )
    {
    }

    T& min( void )
    {
      return _min;
    }

    T& max( void )
    {
      return _max;
    }

    TRangeEndpoint& minEndpoint( void )
    {
      return _minEndpoint;
    }

    TRangeEndpoint& maxEndpoint( void )
    {
      return _maxEndpoint;
    }

    TRangeInclusion& rangeInclusion( void )
    {
      return _rangeInclusion;
    }

    virtual bool eval( const Feature& feature ) const
    {
      T fv = feature.value< T >( );
      bool v =
        (( _minEndpoint == OPENED_ENDPOINT ) ?
         ( fv > _min ) : ( fv >= _min )) &&
        (( _maxEndpoint == OPENED_ENDPOINT ) ?
         ( fv < _max ) : ( fv <= _max ));

      switch ( _rangeInclusion )
      {
      case INSIDE_RANGE:
        return v;
        break;
      case OUTSIDE_RANGE:
        return !v;
        break;
      default:
        throw std::runtime_error(
          std::string( "fires::FilterScalar::eval: " ) +
          std::string( "range inclusion type invalid" ));
         }
    }

  protected:
    T _min;
    T _max;
    TRangeEndpoint _minEndpoint;
    TRangeEndpoint _maxEndpoint;
    TRangeInclusion _rangeInclusion;

  };


 class FilterSetConfig : public TaskConfig
  {
  public:

    typedef std::vector< std::pair< std::string, Filter* >> TFilterPairs;

    class ObjectFulfilsFilter
    {
      TFilterPairs _filters;

    public:
      ObjectFulfilsFilter( TFilterPairs filters_ )
        : _filters( filters_ )
      {
      }

      bool operator( )( Object* obj ) const
      {
        bool fulfilsFilters = true;
        for ( auto filter  = _filters.begin( );
              filter != _filters.end( ); ++filter )
        {
          auto featureLabel = ( *filter ).first;
          auto filterObject = ( *filter ).second;
          bool fulfilsFilter =
            filterObject->eval(( obj->getFeature( featureLabel )));
          if ( !fulfilsFilter )
          {
            fulfilsFilters = false;
            break;
          }
        }
        return !fulfilsFilters;
      }
    };

  public:
    TFilterPairs& filters( )
    {
      return _filters;
    }

  protected:

    TFilterPairs _filters;

  };

  class FilterSet : public Task
  {
  public:

    virtual Objects& eval( Objects &objs, TaskConfig &config )
    {

      FilterSetConfig* filterSetConfig =
        static_cast< FilterSetConfig* >( &config );

      auto filters = filterSetConfig->filters( );

      // Avoid going through all objects if no filter needed
      if ( filters.size( ) == 0 )
      {
        return objs;
      }

      objs.erase(
        std::remove_if( objs.begin( ), objs.end( ),
                        FilterSetConfig::ObjectFulfilsFilter( filters )) ,
        objs.end( ));

      return objs;

    }

  }; // class FilterSet


} // namespace flter


#endif