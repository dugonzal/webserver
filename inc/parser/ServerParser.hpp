/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Dugonzal <dugonzal@student.42urduliz.com>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 14:41:32 by Dugonzal          #+#    #+#             */
/*   Updated: 2024/03/16 14:52:39 by Dugonzal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# pragma  once

# include "../Utils.hpp"

class ServerParser {
 private:
  vector<string>  buffer;
 public:
  ServerParser(void);
  ~ServerParser(void);
  ServerParser(const vector<string>&);
  ServerParser &operator=(const ServerParser&);
};
