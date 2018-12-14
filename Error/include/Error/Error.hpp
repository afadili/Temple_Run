/**
 * \file Error.hpp
 * \brief Declaration of the class "Error"
 */

#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#include <exception>
#include <string>

/**
 * \class Error
 * \brief Error managment, inherited from std::exception
 */
class Error : public std::exception {
protected:
  const std::string _message; /*!< the error message */
  const std::string _file; /*!< file where had the error */
  const unsigned int _line; /*!< line where had the error */
  const std::string _function; /*!< function where had the error */

public:

  /**
   * \brief Default constructor
   */
  Error() : _message(""), _file(""), _line(0), _function("") {
  };

  /**
   * \brief Constructor for development errors
   * \param message : error message
   * \param file : file where had the error 
   * \param line : line where had the error
   * \param function : function where had the error
   */
  Error(const std::string &message, const std::string &file, const unsigned int line, const std::string function) noexcept : _message(message), _file(file), _line(line), _function(function) {
  }

  /**
   * \brief destructor
   */
  ~Error() {
  }

  /**
   * \brief Get all the information from the error to display it
   * \return A string with all the information of the error
   */
  virtual
  const char* what() const noexcept {
    std::string *err = new std::string("Error : " + _file + ":" + std::to_string(_line) + "::" + _function + "\n  Message: " + _message);
    return err->c_str();
  }

  /** 
  * The error macro
  */
  #define ERROR_AT __FILE__, __LINE__, __func__
};



#endif
