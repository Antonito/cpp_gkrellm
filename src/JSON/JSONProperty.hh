#ifndef JSONPROPERTY_HH_
#define JSONPROPERTY_HH_

class JSONProperty
{
public:
  JSONProperty();
  JSONProperty(JSObject const &value);
  JSONProperty(JSONProperty const &other);
  ~JSONProperty();

  JSONProperty &operator=(JSONProperty const &other);
  JSONProperty &operator==(JSONProperty const &other);
  JSONProperty &operator!=(JSONProperty const &other);

  JSONObject &getValue() const;
  void setValue(JSONObject const &val);

private:
  std::string m_name;
  JSONObject  m_value;
};

#endif // !JSONPROPERTY_HH_