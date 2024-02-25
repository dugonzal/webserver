/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:07 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/25 16:49:34 by Dugonzal         ###   ########.fr       */
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
    void      setNservers(void);
    void  parserError(unsigned int*);
    void  handlerParserError(void);
    std::vector<string>::iterator \
      &serverError(std::vector<string>::iterator&);
 public:
    Parser(void);
    ifstream  *openFile(const string&);
    Parser(const string &_filename);
    ~Parser(void);
    void  readIncludeError(string);
    void  readInclude(string);
    void  printData(void);
    int   getNservers(void) const;
};
