/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:55:56 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/13 20:48:25 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"

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
    // estas dos son directrises generales del servidor que solo se alojaran
  //  en el alcance general de la locacion
    pair<string, size_t>  listen;
    string                serverName;

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
    void                        setListen(const string&);
    void                        setServerName(const string&);
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
    const pair<string, size_t>  getListen(void) const;
    const string                getServerName(void) const;
    void                        clear(void);
  friend ostream                &operator<<(ostream &, const Location&);
};
