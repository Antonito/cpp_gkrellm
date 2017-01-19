#include <cassert>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include "JSON.hh"

int main()
{

  // Easy example:
  // - Properties
  // - Object as property
  // - String as property
  // - Property override
  // - JSON::::str()

  JSON::Object  root;
  JSON::Object *child1 = new JSON::Object();
  JSON::Object *child2 = new JSON::Object();
  JSON::Array * array = new JSON::Array();

  array->push(new JSON::String("val in array1"));
  array->push(new JSON::String("val in array2"));
  array->push(new JSON::String("val in array3"));
  array->push(new JSON::String("val in array4"));
  array->pop();
  array->erase(1);
  child1->addProperty("subProperty1", new JSON::String("value1"));
  child2->addProperty("subProperty2", new JSON::String("value2"));
  child2->addProperty("subProperty2", new JSON::String("overriden1"));
  child2->addProperty("subProperty1", array);
  root.addProperty("property1", child1);
  root.addProperty("property2", child2);
  root.addProperty("property3", new JSON::String("nope"));

  // Exception tests

  bool hasCatch;
  try
    {
      // Index accessing on object (it only accept property, with string)
      std::cout << "Index accessing on JSON:: Object:" << std::endl;
      root[1] = JSON::String("");
    }
  catch (JSON::JSONException const &e)
    {
      hasCatch = true;
      assert(std::strcmp(e.what(), "Index accessing on JSON::Object") == 0);
      std::cout << "Catch OK" << std::endl;
    }
  assert(hasCatch);

  hasCatch = false;
  try
    {
      // Index accessing on string (it doesn't accept accessing)
      std::cout << "Index accessing on JSON:: String:" << std::endl;
      root["property3"][0] = JSON::String("");
    }
  catch (JSON::JSONException const &e)
    {
      hasCatch = true;
      assert(std::strcmp(e.what(), "Index accessing on JSON::String") == 0);
      std::cout << "Catch OK" << std::endl;
    }
  assert(hasCatch);

  hasCatch = false;
  try
    {
      // Property accessing on string (it doesn't accept accessing)
      std::cout << "Property accessing on JSON:: String:" << std::endl;
      root["property3"]["oui"] = JSON::String("");
    }
  catch (JSON::JSONException const &e)
    {
      hasCatch = true;
      assert(std::strcmp(e.what(), "Property accessing on JSON::String") == 0);
      std::cout << "Catch OK" << std::endl;
    }
  assert(hasCatch);

  hasCatch = false;
  try
    {
      // Non existant property (it doesn't accept accessing)
      std::cout << "Non existant property:" << std::endl;
      root["nonExistant"] = JSON::String("nope");
    }
  catch (JSON::JSONException const &e)
    {
      hasCatch = true;
      assert(std::strcmp(e.what(), "No such property") == 0);
      std::cout << "Catch OK" << std::endl;
    }
  assert(hasCatch);

  std::cout << "Validating json with json_verify:" << std::endl;
  std::cout << root.str() << std::endl;
  system(std::string("json_verify <<< \"" + root.str("\\\"") + "\"").c_str());

  JSON::Source src;

  src.setText(root.str());
  JSON::IElement *reconstruct = src.parseJSON();

  std::cout << "Reconstruction:" << std::endl;
  std::cout << reconstruct->str() << std::endl;

  JSON::Source example("example.json");
  JSON::IElement *ex = example.parseJSON();
  std::cout << ex->str() << std::endl;
  system(std::string("json_verify <<< \"" + ex->str("\\\"") + "\"").c_str());
  return EXIT_SUCCESS;
}