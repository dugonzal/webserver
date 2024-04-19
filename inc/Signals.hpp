/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signals.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:37:20 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/04/19 18:21:24 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include "Utils.hpp"

class Signals {
 private:
    /* struct sigaction sign; */

 public:
    Signals(void);
    ~Signals(void);
    static void setSignals(int);
};
