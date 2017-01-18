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
  // - JSON::str()

  JSONObject  root;
  JSONObject *child1 = new JSONObject();
  JSONObject *child2 = new JSONObject();

  child1->addProperty("subProperty1", new JSONString("value1"));
  child2->addProperty("subProperty2", new JSONString("value2"));
  child2->addProperty("subProperty2", new JSONString("overriden1"));
  root.addProperty("property1", child1);
  root.addProperty("property2", child2);
  root.addProperty("property3", new JSONString("nope"));

  // Exception tests

  bool hasCatch;
  try
    {
      // Index accessing on object (it only accept property, with string)
      std::cout << "Index accessing on JSON Object:" << std::endl;
      root[1] = JSONString("");
    }
  catch (JSONException const &e)
    {
      hasCatch = true;
      assert(std::strcmp(e.what(), "Index accessing on JSONObject") == 0);
      std::cout << "Catch OK" << std::endl;
    }
  assert(hasCatch);

  hasCatch = false;
  try
    {
      // Index accessing on string (it doesn't accept accessing)
      std::cout << "Index accessing on JSON String:" << std::endl;
      root["property3"][0] = JSONString("");
    }
  catch (JSONException const &e)
    {
      hasCatch = true;
      assert(std::strcmp(e.what(), "Index accessing on JSONString") == 0);
      std::cout << "Catch OK" << std::endl;
    }
  assert(hasCatch);

  hasCatch = false;
  try
    {
      // Property accessing on string (it doesn't accept accessing)
      std::cout << "Property accessing on JSON String:" << std::endl;
      root["property3"]["oui"] = JSONString("");
    }
  catch (JSONException const &e)
    {
      hasCatch = true;
      assert(std::strcmp(e.what(), "Property accessing on JSONString") == 0);
      std::cout << "Catch OK" << std::endl;
    }
  assert(hasCatch);

  hasCatch = false;
  try
    {
      // Non existant property (it doesn't accept accessing)
      std::cout << "Non existant property:" << std::endl;
      root["nonExistant"] = JSONString("nope");
    }
  catch (JSONException const &e)
    {
      hasCatch = true;
      assert(std::strcmp(e.what(), "No such property") == 0);
      std::cout << "Catch OK" << std::endl;
    }
  assert(hasCatch);

  std::cout << "Validating JSON with json_verify:" << std::endl;
  std::cout << root.str() << std::endl;
  system(std::string("json_verify <<< " + root.str("\\\"")).c_str());
  return EXIT_SUCCESS;
}