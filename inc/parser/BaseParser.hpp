/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:07 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/05 12:26:01 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"

class BaseParser {
 protected:
    string          fileName;
    size_t          nServers;
    vector<string>  data;

 private:
    void      setNservers(void);
    void      readIncludeError(string);
    void      readInclude(const string&);
    int       serverError(unsigned int) const;
    void      handlerScopeError(void);
    void      checkSemicolon(void) const;
    void      handlerScopeLocation(void);
    int       parserScopeLocation(unsigned int) const;

 public:
    BaseParser(void);
    BaseParser(const BaseParser&);
    BaseParser &operator=(const BaseParser&);
    BaseParser(const string&);
    virtual ~BaseParser(void) = 0;

 public:
    ifstream  *openFile(const string&) const;
    void  printData(const vector<string>&) const;
    vector<string> getData(void) const;
    int   getNservers(void) const;
};
