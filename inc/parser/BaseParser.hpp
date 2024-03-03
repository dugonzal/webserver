/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:07 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/03 13:23:35 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"

class BaseParser {
 private:
    string               fileName;
    std::size_t          nServers;
    std::vector<string>  data;
 private:
    void      setNservers(void);
    void      readIncludeError(string);
    void      readInclude(const string&);
    int       serverError(unsigned int) const;
    void      handlerScopeError(void);
    void      checkSemicolon(void) const;
    ifstream  *openFile(const string&) const;
    void      handlerScopeLocation(void);
    int       parserScopeLocation(unsigned int) const;
 public:
    BaseParser(void);
    BaseParser(const BaseParser&);
    BaseParser &operator=(const BaseParser&);
    BaseParser(const string&);
    ~BaseParser(void);
 public:
    void  printData(const std::vector<string>&) const;
    std::vector<string> getData(void) const;
    int   getNservers(void) const;
};
