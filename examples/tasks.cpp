#include <fires/fires.h>

// Function to print out query results
void printResults( fires::Objects& objects, std::string scoreLabel )
{
  for ( auto obj = objects.begin( ); obj != objects.end( ); obj++ )
  {
    std::cout << ( *obj )->label( ) << ": "
              << ( *obj )->getFeature( scoreLabel ).value< float >( )
              << std::endl;
  }
}


class TestObject :
  public fires::Object
{
public:
  TestObject( )
  {
    this->registerFeature( std::string( "feature1" ), &this->attr1 );
    this->registerFeature( std::string( "feature2" ), &this->attr2 );
  }

public:
  float attr1, attr2;

};

int main( void )
{

  // Create objects and give value to their features
  TestObject obj1, obj2, obj3, obj4;

  obj1.attr1 = 3.4f;
  obj1.attr2 = 4.3f;

  obj2.attr1 = 3.2f;
  obj2.attr2 = 42.1f;

  obj3.attr1 = 1.4f;
  obj3.attr2 = 2.2f;

  obj4.attr1 = 4.1f;
  obj4.attr2 = 1.8f;

  // Label objects
  obj1.label( ) = "Object 1";
  obj2.label( ) = "Object 2";
  obj3.label( ) = "Object 3";
  obj4.label( ) = "Object 4";

  // Create comparers
  fires::ScalarPtrComparer< float > comparer;
  fires::ScalarPtrAverager< float > averager;
  fires::Search search;
  fires::SearchConfig sc;
  sc.add( std::string("feature1"), &comparer, &averager );
  sc.add( std::string("feature2"), &comparer, &averager );
  sc.queryObjects( ).add( &obj1 );
  sc.queryObjects( ).add( &obj2 );

  fires::Tasks tasks;
  tasks.push_back( fires::TasksConfig( &search, &sc ));

  fires::Engine engine;

  fires::Objects objects;
  objects.add( &obj1 );
  objects.add( &obj2 );
  objects.add( &obj3 );
  objects.add( &obj4 );

  engine.eval( objects, tasks );
  printResults( objects, "fires::score" );
  std::cout << std::endl;

  sc.distanceToQueryType( ) =
    fires::SearchConfig::MINIMUM_DISTANCE_TO_QUERY_OBJECTS;

  engine.eval( objects, tasks );
  printResults( objects, "fires::score" );


  return 0;
}
