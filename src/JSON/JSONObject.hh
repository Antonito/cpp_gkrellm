#ifndef JSONOBJECT_HH_
#define JSONOBJECT_HH_

class JSONObject : public JSONElement
{
public:
  JSONObject(std::string const &name);
  ~JSONObject();

  JSObject &operator[](std::string const &prop);

private:
};

#endif // !JSONOBJECT_HH_