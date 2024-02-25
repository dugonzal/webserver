/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/29 17:36:07 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/02/25 20:00:17 by Dugonzal         ###   ########.fr       */
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
    void  serverError(unsigned int*);
    void  handlerScopeError(void);
 public:
    Parser(void);
    ifstream  *openFile(const string&);
    Parser(const string &);
    ~Parser(void);
    void  readIncludeError(string);
    void  readInclude(const string&);
    void  printData(void);
    int   getNservers(void) const;
};
