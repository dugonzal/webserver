/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ServerParser.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaizpuru <jaizpuru@student.42urduliz.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/19 09:38:37 by jaizpuru          #+#    #+#             */
/*   Updated: 2024/03/19 09:41:49 by jaizpuru         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
