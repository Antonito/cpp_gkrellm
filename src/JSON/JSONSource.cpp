#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
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
	sstring << file.rdbuf();
	m_text = sstring.str();
	this->clearSpaces();
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
    this->clearSpaces();
  }

  size_t Source::getIndex() const
  {
    return (m_index);
  }

  void Source::setIndex(size_t index)
  {
    m_index = index;
  }

  void Source::clearSpaces()
  {
    bool               inString = false;
    bool               escaping = false;
    std::string        res("");
    const std::string &str(m_text);
    size_t             i = 0;

    for (size_t i = 0; i < str.size(); ++i)
      {
	if (inString)
	  {
	    res += str[i];
	    if (str[i] == '\"' && escaping == false)
	      inString = false;
	    if (str[i] == '\\')
	      escaping = !escaping;
	  }
	else
	  {
	    if (str[i] == '\"')
	      inString = true;
	    if (std::isspace(str[i]) == false)
	      res += str[i];
	  }
      }
    m_text = res;
  }

  IElement *Source::parseJSON()
  {
    char cur = m_text[m_index];

    if (cur == 0)
      throw JSONException("JSON parsing error: unexpected end of source (1)");

    if (cur == '\"')
      return this->parseString();
    else if (cur == '{')
      return this->parseObject();
    else if (cur == '[')
      return this->parseArray();
    std::cerr << "Invalid char: '" << cur << "' (" << m_index << ")"
              << std::endl;
    throw JSONException("JSON parsing error: invalid character");
  }

  std::string Source::parseStr()
  {
    size_t &           idx(m_index); // Reference on cursor index
    std::string const &str(m_text);  // Reference on source text

    std::string res("");   // Resulting string
    bool escaping = false; // Boolean to know if we are escaping a character

    // Check if the first character is a double quote
    if (str[idx] != '"')
      {
	throw JSONException(
	    "Invalid parsing: JSON string (first double quote missing)");
      }
    ++idx; // Go to next char

    // Looping until a not escaped double quote
    while (str[idx] != '"' && !escaping)
      {
	// If we reached the end of the source text, throw
	if (idx >= str.length())
	  {
	    throw JSONException(
	        "Invalid parsing: JSON string (last double quote missing)");
	  }

	// If we are currently escaping, add the character, no matter what
	if (escaping)
	  {
	    res += str[idx];
	    escaping = false; // We are no more escaping
	  }
	// Else if it's an escaping character, enable it to escape the next one
	else if (str[idx] == '\\')
	  escaping = true;
	else
	  res += str[idx]; // Else add it normally

	++idx; // Go to next char
      }
    ++idx; // The last char is '"', so go to the next
    return (res);
  }

  String *Source::parseString()
  {
    return new String(this->parseStr());
  }

  Array *Source::parseArray()
  {
    Array *            res = new Array(); // Resulting array
    size_t &           idx(m_index);      // Reference on cursor index
    std::string const &str(m_text);       // Reference on source text

    // Check if the first character is an opening bracket
    if (str[idx] != '[')
      {
	throw JSONException(
	    "Invalid parsing: JSON array (missing opening bracket)");
      }
    ++idx; // Go to the content

    // While we do not encounter a closing bracket
    while (str[idx] != ']')
      {
	// If we reached end of source text, throw
	if (idx >= str.length())
	  {
	    throw JSONException(
	        "Invalid parsing: JSON array (missing closing bracket)");
	  }

	// If this is not the first element, check for the comma
	if (res->size() != 0)
	  {
	    if (str[idx] != ',')
	      {
		throw JSONException(
		    "Invalid parsing: JSON array (missing comma)");
	      }
	    ++idx;
	  }
	// Parse objects directly and add them
	res->push(this->parseJSON());
      }
    ++idx; // Move from the ']' char
    return (res);
  }

  Object *Source::parseObject()
  {
    Object *           res = new Object(); // Resulting object
    size_t &           idx(m_index);       // Reference on cursor index
    std::string const &str(m_text);        // Reference on source text

    // Check if the character is an opening brace
    if (str[idx] != '{')
      {
	throw JSONException(
	    "Invalid parsing: JSON object (missing opening brace)");
      }
    ++idx;
    // While we do not encounter a closing brace
    while (str[idx] != '}')
      {
	// If we reached end of source text, throw
	if (idx >= str.length())
	  {
	    throw JSONException(
	        "Invalid parsing: JSON object (missing closing brace)");
	  }

	// If this is not the first element, check for comma
	if (res->size() != 0)
	  {
	    if (str[idx] != ',')
	      {
		throw JSONException(
		    "Invalid parsing: JSON object (missing comma)");
	      }
	    ++idx;
	  }
	// Get the property name
	std::string name = this->parseStr();
	// Check for the ':' between the property name and the value
	if (str[idx] != ':')
	  {
	    throw JSONException(
	        "Invalid parsing: JSON object (missing colon in property)");
	  }
	++idx;
	// Get the property's value
	IElement *val = this->parseJSON();
	// Add it to the current object
	res->addProperty(name, val);
      }
    ++idx;
    return (res);
  }
}