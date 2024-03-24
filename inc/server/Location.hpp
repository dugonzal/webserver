/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Location.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/22 18:55:56 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/23 09:55:05 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "../Utils.hpp"

class Location {
 private:
    string  route;

 public:
    Location(void);
    ~Location(void);
    Location(const Location&);
    Location &operator=(const Location&);
};