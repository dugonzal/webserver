/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:55:56 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/12 21:58:16 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"
#include <utility>

class Location {
 private:
    string                root;
    string                path;
    string                index;
    int                   autoIndex;
    string                cgiPath;
    string                cgiExt;
    pair<size_t, string>  _return;
    vector<string>        methods;
    map<size_t, string>   errorPages;

 public:
    Location(void);
    ~Location(void);
    Location(const Location&);
    Location                    &operator=(const Location&);
    void                        setRoot(const string&);
    void                        setPath(const string&);
    void                        setIndex(const string&);
    void                        setAutoIndex(const string&);
    void                        setCgiPath(const string&);
    void                        setCgiExt(const string&);
    void                        setMethods(const string&);
    void                        setReturn(const string&);
    void                        setErrorPages(const string&);
    Location                    clone(void) const;
    const string                getRoot(void) const;
    const string                getPath(void) const;
    const string                getIndex(void) const;
    int                         getAutoIndex(void) const;
    const string                getCgiPath(void) const;
    const string                getCgiext(void) const;
    const vector<string>        getmethods(void) const;
    const pair<size_t, string>  getReturn(void) const;
    const map<size_t, string>   getErrorPages(void) const;
    void                        clear(void);
  friend ostream                &operator<<(ostream &, const Location&);
};
