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
 * \brief Error managment for runtime errors, inherited from std::exception
 */
class Error : public std::exception {
protected:
  const std::string _message; /*!< the error message */
  const std::string _code; /*!< the code error (example : FILE_NOT_FOUND) */
  const bool _critical; /*!< if the error is a critical error (true) or a warning (false, by default) */

public:

  /**
   * \brief Default constructor
   */
  Error() : _message(""), _code(""), _critical(false) {
  };

  /**
   * \brief Constructor for runtime errors
   * \param message : error message
   * \param code : error code
   * \param critical : if is critical 
   */
  Error(const std::string &message, const std::string &code, const bool critical) noexcept : _message(message), _code(code), _critical(critical) {
  }

    /**
   * \brief Constructor for runtime errors
   * \param message : error message
   * \param code : error code 
   */
  Error(const std::string &message, const std::string &code) noexcept : _message(message), _code(code), _critical(false) {
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
    std::string *err;
    if(_critical)
      err = new std::string("CRITICAL ERROR :\n -- [" + _code + "] " + _message + "\n");
    else
      err = new std::string("WARNING :\n -- [" + _code + "] " + _message + "\n");
    return err->c_str();
  }

};



#endif
