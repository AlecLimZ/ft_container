/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ujian.cc                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 17:49:26 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/13 17:55:17 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <map>
#include <iostream>
#include <list>

using std::cout;
using std::endl;
using std::map;

int main(void)
{
	std::list<std::pair<const char, int> > lst;
	unsigned int lst_size = 5;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(std::make_pair('a' + i, (i + 1) * 7));
	map<char, int> lol(lst.begin(), lst.end());
}
