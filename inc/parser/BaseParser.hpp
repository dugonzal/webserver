/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BaseParser.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:07 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/14 12:55:48 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"

class BaseParser {
 protected:
    string          fileName;
    size_t          nServers;
    vector<string>  data;
    set<string>     words;

 private:
    void      setNservers(void);
    bool      readIncludeError(string);
    bool      readInclude(const string&);
    size_t    serverError(size_t);
    void      handlerScopeError(void);
    void      checkSemicolon(void) const;
    void      handlerScopeLocation(void);
    size_t    parserScopeLocation(size_t) const;
    void      setWords(void);
    bool      checkAllowedWords(const string&) const;
    size_t    skipLocation(size_t);
    void      keyValueCkeck(void);
    void      deleteServerEmpty(void);

 public:
    BaseParser(void);
    explicit BaseParser(const string&);
    BaseParser(const BaseParser&);
    BaseParser &operator=(const BaseParser&);
    virtual ~BaseParser(void) = 0;

 public:
    ifstream              *openFile(const string&) const;
    void                  printData(const vector<string>&) const;
    const vector<string>  getData(void) const;
    size_t                getNservers(void) const;
    void                  setNservers(size_t);
};

