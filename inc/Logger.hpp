/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Logger.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 11:42:46 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/21 22:07:15 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "Utils.hpp"

class Logger {
 private:
  static Logger *ins;
  ofstream      file;
  string        fileName;

 private:
  explicit Logger(const string&);

 public:
  Logger(void);
  ~Logger(void);
  Logger(const Logger&);
  Logger        &operator=(const Logger&);
  void          Log(const char *, ...);
};
