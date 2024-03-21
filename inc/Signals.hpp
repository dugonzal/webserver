/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Signals.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/18 15:37:20 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/21 12:59:30 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma once

# include <csignal>

class Signals {
 private:
    /* struct sigaction sign; */

 public:
    Signals(void);
    ~Signals(void);
    void setSignals(void);
};
