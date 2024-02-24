/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:07 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/24 10:37:48 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../utils.hpp"

class Parser {
 private:
    string               fileName;
    std::size_t          nServers;
    std::vector<string>  data;
 private:
    ifstream  *openFile(const string&);
    void      setNservers(void);
    void  handlerError(void);
    std::vector<string>::iterator \
      &serverError(std::vector<string>::iterator&);
 public:
    Parser(void);
    Parser(const string &_filename);
    ~Parser(void);
    void  readIncludeError(string);
    void  readInclude(string);
    void  printData(void);
};
