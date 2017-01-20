#ifndef JSONSOURCE_H_
#define JSONSOURCE_H_

#include <string>

namespace JSON
{
  class IElement;
  class Object;
  class String;
  class Array;

  class Source
  {
  public:
    Source();
    Source(std::string const &filename);
    Source(Source const &other);
    ~Source();

    Source &operator=(Source const &other);

    std::string const &getText() const;
    void setText(std::string const &text);
    size_t getIndex() const;
    void setIndex(size_t index);

    IElement *parseJSON();
    String *  parseString();
    Array *   parseArray();
    Object *  parseObject();

  private:
    std::string m_text;
    size_t      m_index;

    void        clearSpaces();
    std::string parseStr();
  };
}

#endif // !JSONSOURCE_H_