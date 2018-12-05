/**
 * \file Error.hpp
 * \brief 
 */

#include <exception>
#include <string>

#ifndef __ERROR_HPP__
#define __ERROR_HPP__

#define AT __FILE__, __LINE__, __func__

/**
 * \class Erreur
 * \brief Classe de gestion des erreurs, hérité de std::exception
 */
class Error : public std::exception {
protected:
  const std::string _message;
  const char* _file;
  const unsigned int _line;
  const char* _function;

public:

  /**
   * \brief Constructeur par défaut
   */
  Error() : _message(""), _file(""), _line(0), _function("") {
  };

  /**
   * \brief Constructeur
   * \param message : message d'erreur a afficher
   * \param file : fichier de l'erreur
   * \param line : ligne de l'erreur
   * \param function : fonction où a eu lieu l'erreur
   */
  Error(const std::string &message, const char* file, const unsigned int line, const char* function) : _message(message), _file(file), _line(line), _function(function) {
  }

  /**
   * \brief Destructeur
   */
  ~Error() {
  }

  /**
   * \brief Obtenir toutes les informations de l'erreur pour l'afficher
   * \return Une chaine avec toutes les informations de l'erreur
   */
  virtual
  const char* what() const noexcept {
    std::string *err = new std::string("Error : " + std::string(_file) + ":" + std::to_string(_line) + "::" + std::string(_function) + "\n  Message: " + _message);
    return err->c_str();
  }
};



#endif
