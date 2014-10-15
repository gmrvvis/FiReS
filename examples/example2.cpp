/**
 * @file    example2.cpp
 * @brief   This example show how to use vector-based features
 * @author  Pablo Toharia <pablo.toharia@urjc.es>
 * @date    
 * @remarks Copyright (c) GMRV/URJC. All rights reserved. 
 *          Do not distribute without further notice.
 */

#include "../fires/fires.h"

#include <iostream>
#include <math.h>


// This example requires fires compiled with vmmlib
#if (FIRES_WITH_VMMLIB == 1)


// Original test class which has some attributes 
// of different types
class Test
{
  
public:
  
  float attr1;

  float attr11, attr12;
  int attr21, attr22, attr23;
  float attr31, attr32, attr33;
  
};

// Class derived from original class and fires::Object
class TestObject 
  : public Test
  , public fires::Object
{
  
public:
  
  // If we are going to use pointers to vectors then this
  // vectors have to be created.

  // vector1 and vector2 are made of scalars, thus their changes
  // on the original attributes are not reflected automatically 
  // in the vector. It has to be manually upadated
  fires::Vec2f vector1;
  fires::Vec3i vector2;

  // vector3 is made od pointers to scalars. Thus, any change on 
  // the original values are directly reflected on the vector
  fires::Vec3pf vector3;
  
  fires::Feature * f1, * f2, * f3, * f4;

  TestObject () 
  {

    // Vectors of scalars are initilized to zero (optional)
    vector1 = fires::Vec2f::ZERO;
    vector2 = fires::Vec3i::ZERO;

    // Vector of pointers to scalars need to know the pointers to store
    vector3 = fires::Vec3pf( & attr31, & attr32, & attr33 );

    // Create the features
    f1 = new fires::FeatureVec2fPtr( & vector1 );
    f2 = new fires::FeatureVec3iPtr( & vector2 );
    f3 = new fires::FeatureVec3pfPtr( & vector3 );
    f4 = new fires::FeatureFloatPtr( & this->attr1);

    // Add the different features of different types, giving a name
    // and the feature itself
    this->addFeature(std::string("feature1"), f1 );
    this->addFeature(std::string("feature2"), f2 );
    this->addFeature(std::string("feature3"), f3 );
    this->addFeature(std::string("feature4"), f4 );

  }     

  ~TestObject () 
  {

    delete f1;
    delete f2;
    delete f3;
    delete f4;

  }

};



int main ( )
{

  // Two test objects
  TestObject obj1, obj2;

  // Set values to their attributes 
  obj1.attr1 = 1.2f;
  obj2.attr1 = 2.3f;

  obj1.attr11 = 3.4f;
  obj1.attr12 = 4.3f;

  obj1.attr21 = 3;
  obj1.attr22 = 2;
  obj1.attr23 = 2;

  obj2.attr11 = 2.4f;
  obj2.attr12 = 2.5f;

  obj2.attr21 = 4;
  obj2.attr22 = 1;
  obj2.attr23 = 2;

  obj1.attr31 = 4.4;
  obj1.attr32 = 1.2;
  obj1.attr33 = 2.6;

  obj2.attr31 = 2.2;
  obj2.attr32 = 2.4;
  obj2.attr33 = 3.1;

  // In case of using pointers to vectors of scalars their values 
  // have to be updated 
  obj1.vector1 = fires::Vec2f( obj1.attr11, obj1.attr12 );
  obj1.vector2 = fires::Vec3i( obj1.attr21, obj1.attr22, obj1.attr23 );

  obj2.vector1 = fires::Vec2f( obj2.attr11, obj2.attr12 );
  obj2.vector2 = fires::Vec3i( obj2.attr21, obj2.attr22, obj2.attr23 );

  // Asign labels
  obj1.label( ) = "Object 1";
  obj2.label( ) = "Object 2";
  

  // Set-up comparers
  fires::FeatureVec2fPtrComparer comparer1;
  fires::FeatureVec3iPtrComparer comparer2;
  fires::FeatureVec3pfPtrComparer comparer3;
  fires::FeatureFloatPtrComparer comparer4;

  // Set-up system
  fires::System sys;

  // Add objects to the system
  sys.addObject( &obj1 );
  sys.addObject( &obj2 );

  // Add query objects
  sys.addQueryObject( &obj1 );

  // Add the features to the system
  sys.addFeature( "feature1", 1.0, & comparer1 );
  sys.addFeature( "feature2", 1.0, & comparer2 );
  sys.addFeature( "feature3", 1.0, & comparer3 );
  sys.addFeature( "feature4", 1.0, & comparer4 );
  
  // Perform a query
  sys.query();

  // Print results
  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;
  std::cout << std::endl;

  // Now show that comparer parameters can be changed. In this case the
  // type of distance is changed from default euclidean to manhattan
  comparer1.distanceType() = fires::FeatureVec2fPtrComparer::MANHATTAN;
  comparer2.distanceType() = fires::FeatureVec3iPtrComparer::MANHATTAN;

  // Query again and print results
  sys.query();

  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;
  std::cout << std::endl;

  // Return the the distances to euclidean and print results. They 
  // should be the same as the first query
  comparer1.distanceType() = fires::FeatureVec2fPtrComparer::EUCLIDEAN;
  comparer2.distanceType() = fires::FeatureVec3iPtrComparer::EUCLIDEAN;

  sys.query();

  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;
  std::cout << std::endl;

  // Now change an atribute of an object which is used in a vector of 
  // scalars. In this case the vector is not affected and the result
  // of the query should be the same.
  // 
  obj1.attr11 = 13.4f;

  sys.query();

  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;

  // Now update the vector and the result now is correctly computed
  obj1.vector1 = fires::Vec2f( obj1.attr11, obj1.attr12 );


  sys.query();

  std::cout << std::endl;
  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;


  // If we use vectors of pointers to scalars in this case changing the 
  // value of an attribute affects the result of the query
  obj1.attr31 = 20.0f;
  sys.query();

  std::cout << std::endl;
  for (fires::System::Results::const_iterator it = sys.results().begin();
     it != sys.results().end(); it++)
    std::cout << (*it).obj->label() << ": " << (*it).score << std::endl;


  return 0;


}

#else 


int main ( void )
{

  std::cerr << "This example need vmmlib" << std::endl;

  return -1;

}

#endif 