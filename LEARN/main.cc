/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/18 15:16:21 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myclass.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <unordered_map>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::iterator_traits;
using std::list;
using std::unordered_map;

int main()
{
	vector<int> values;

	for (int i = 1; i <= 5; i++)
		values.push_back(i);
	for (int i = 0; i < 5; i++)
		cout << values[i] << " ";
	cout << endl;
	for (vector<int>::iterator it = values.begin(); it != values.end(); it++)
		cout << *it << endl;

	typedef unordered_map<std::string, int> ScoreMap;
	ScoreMap map;
	map["Cherno"] = 5;
	map["C++"] = 2;

	for (ScoreMap::const_iterator it = map.begin(); it != map.end(); it++)
	{
		cout << it->first << " ";
		cout << it->second << endl;
	}
}
