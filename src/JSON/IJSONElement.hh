#ifndef IJSONELEMENT_HH_
#define IJSONELEMENT_HH_

class IJSONElement
{
public:
  virtual ~IJSONElement(){};

  virtual std::string str(std::string const &c = "\"") const = 0;
  virtual IJSONElement &operator[](size_t index) = 0;
  virtual IJSONElement &operator[](std::string const &name) = 0;
};

#endif // !IJSONELEMENT_HH_