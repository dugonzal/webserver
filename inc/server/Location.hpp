/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:55:56 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/24 14:36:14 by Dugonzal         ###   ########.fr       */
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
    vector<string>    methods;
    map<int, string>  errorPages;

 public:
    Location(void);
    ~Location(void);
    Location(const Location&);
    Location &operator=(const Location&);
};
