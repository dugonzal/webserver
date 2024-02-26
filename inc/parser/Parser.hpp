/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:07 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/26 20:34:46 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"

class Parser {
 private:
    string               fileName;
    std::size_t          nServers;
    std::vector<string>  data;
 private:
    void      setNservers(void);
    void      readIncludeError(string);
    void      readInclude(const string&);
    void      serverError(unsigned int*) const;
    void      handlerScopeError(void);
    void      checkSemicolon(void) const;
    ifstream  *openFile(const string&) const;
    void      handlerScopeLocation(void);
    int       parserScopeLocation(unsigned int) const;
 public:
    Parser(void);
    Parser(const string&);
    ~Parser(void);
 public:
    void  printData(std::vector<string>) const;
    std::vector<string> getData(void) const;
    int   getNservers(void) const;
};
