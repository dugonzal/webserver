/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signals.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:37:20 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/05 10:56:08 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <csignal>

class Signals {
 private:
    struct sigaction sign;

 public:
    Signals(void);
    ~Signals(void);
    void setSignals(void);
};
