source_group(\\ FILES CMakeLists.txt)

set(FIRES_PUBLIC_HEADERS
  DependenciesManager.h
  error.h
  Log.h
  Object/Object.h
  Object/Objects.h
  ObserverManager.h
  PropertyGIDsManager.h
  PropertyManager.h
  Property/Aggregator.h
  Property/Averager.h
  Property/Comparer.h
  Property/Normalizer.h
  Property/PropertyCaster.h
  Property/Property.h
  Tasks/Aggregate.h
  Tasks/Engine.h
  Tasks/Filter.h
  Tasks/SearchConfig.h
  Tasks/Search.h
  Tasks/Sort.h
  Tasks/Task.h
)

set(FIRES_HEADERS )

set(FIRES_SOURCES
  DependenciesManager.cpp
  Log.cpp
  Object/Object.cpp
  Object/Objects.cpp
  ObserverManager.cpp
  PropertyGIDsManager.cpp
  PropertyManager.cpp
  Property/Comparer.cpp
  Property/Property.cpp
  Tasks/Engine.cpp
  Tasks/Filter.cpp
  Tasks/SearchConfig.cpp
  Tasks/Search.cpp
  Tasks/Sort.cpp
)

common_library(FiReS)
