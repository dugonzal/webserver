/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:55:56 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/02 18:16:55 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"

class Location {
 private:
    string            root;
    string            path;
    string            index;
    bool              autoIndex;
    string            cgiPath;
    string            cgiExt;
    vector<string>    methods;
    map<int, string>  errorPages;

 public:
    Location(void);
    ~Location(void);
    Location(const Location&);
    Location &operator=(const Location&);
    void  setRoot(const string&);
    void  setPath(const string&);
    void  setIndex(const string&);
    void  setAutoIndex(const bool&);
    void  setCgiPath(const string&);
    void  setCgiExt(const string&);
    void  setMethods(const string&);
    void  setErrorPages(const int&, const string&);
    Location  clone(void);
};
