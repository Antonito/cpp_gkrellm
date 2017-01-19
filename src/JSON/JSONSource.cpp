#include <fstream>
#include <sstream>
#include "JSON.hh"
#include "JSONSource.hh"

namespace JSON
{
  Source::Source() : m_text(""), m_index(0)
  {
  }

  Source::Source(std::string const &filename) : m_index(0)
  {
    std::ifstream     file(filename.c_str());
    std::stringstream sstring;

    if (file.is_open())
      {
	sstring << file;
	m_text = sstring.str();
	file.close();
      }
    else
      {
	throw JSONException("No such file: " + filename);
      }
  }

  Source::Source(Source const &other)
      : m_text(other.m_text), m_index(other.m_index)
  {
  }

  Source::~Source()
  {
  }

  Source &Source::operator=(Source const &other)
  {
    if (this != &other)
      {
	m_text = other.m_text;
	m_index = other.m_index;
      }
    return (*this);
  }

  std::string const &Source::getText() const
  {
    return (m_text);
  }

  void Source::setText(std::string const &text)
  {
    m_text = text;
  }

  size_t Source::getIndex() const
  {
    return (m_index);
  }

  void Source::setIndex(size_t index)
  {
    m_index = index;
  }

  void Source::jumpSpaces()
  {
    while (m_index < m_text.size() && std::isspace(m_text[m_index]))
      ++m_index;
    if (m_index == m_text.size())
      {
	throw JSONException("JSON parsing error: unexpected end of source");
      }
  }

  IElement *Source::parseJSON()
  {
    this->jumpSpaces();
    char cur = m_text[m_index];

    if (cur == '\"')
      return this->parseString();
    else if (cur == '{')
      return this->parseObject();
    else if (cur == '[')
      return this->parseArray();
    throw JSONException("JSON parsing error: invalid character");
  }

  std::string Source::parseStr()
  {
    size_t &           i(m_index);
    std::string const &s(m_text);

    std::string res("");
    bool        escaping = false;

    if (s[i] != '"')
      {
	throw JSONException(
	    "Invalid parsing: JSON string (first double quote missing)");
      }
    ++i;

    // Looping until a double quote (not escaped)
    while (s[i] != '"' && !escaping)
      {
	// If we reached the end of the source, throw
	if (i >= s.length())
	  {
	    throw JSONException(
	        "Invalid parsing: JSON string (last double quote missing)");
	  }
	if (escaping)
	  {
	    res += s[i];
	    escaping = false;
	  }
	else if (s[i] == '\\')
	  escaping = true;
	else
	  res += s[i];
	++i;
      }
    ++i;
    return (res);
  }

  String *Source::parseString()
  {
    this->jumpSpaces();
    return new String(this->parseStr());
  }

  Array *Source::parseArray()
  {
    Array *            res = new Array();
    size_t &           i(m_index);
    std::string const &s(m_text);

    this->jumpSpaces();
    if (s[i] != '[')
      {
	throw JSONException(
	    "Invalid parsing: JSON array (missing opening bracket)");
      }
    ++i;
    while (s[i] != ']')
      {
	if (i >= s.length())
	  {
	    throw JSONException(
	        "Invalid parsing: JSON array (missing closing bracket)");
	  }
	if (res->size() != 0)
	  {
	    this->jumpSpaces();
	    if (s[i] != ',')
	      {
		throw JSONException(
		    "Invalid parsing: JSON array (missing comma)");
	      }
	      ++i;
	  }
	res->push(this->parseJSON());
      }
      ++i;
    return (res);
  }

  Object *Source::parseObject()
  {
    Object *           res = new Object();
    size_t &           i(m_index);
    std::string const &s(m_text);

    this->jumpSpaces();
    if (s[i] != '{')
      {
	throw JSONException(
	    "Invalid parsing: JSON object (missing opening brace)");
      }
    ++i;
    while (s[i] != '}')
      {
	if (i >= s.length())
	  {
	    throw JSONException(
	        "Invalid parsing: JSON object (missing closing brace)");
	  }
	if (res->size() != 0)
	  {
	    this->jumpSpaces();
	    if (s[i] != ',')
	      {
		throw JSONException(
		    "Invalid parsing: JSON object (missing comma)");
	      }
	      ++i;
	  }
	std::string name = this->parseStr();
	this->jumpSpaces();
	if (s[i] != ':')
	  {
	    throw JSONException(
	        "Invalid parsing: JSON object (missing colon in property)");
	  }
	  ++i;
	IElement *val = this->parseJSON();
	res->addProperty(name, val);
      }
      ++i;
    return (res);
  }
}