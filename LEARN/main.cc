/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/15 17:08:31 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myclass.hpp"
#include "iter.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <array>
#include <unordered_map>
#include <memory> // for unique make
#include <type_traits> // for enable_if
#include <numeric> // for std::reduce & accumulate()
#include <fstream>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
//using std::iterator_traits;
using std::list;
using std::unordered_map;
using std::string;
using std::ostream;
using std::iterator_traits;
using std::array;
using std::ifstream;

namespace ft
{
	template <class T>
	struct is_integral
	{
		static const bool value = std::numeric_limits<T>::is_integer;
	};
}

int main()
{
	vector<int> first;
	vector<int> second;
	vector<int> third;
	
	typedef vector<int>::iterator iter;

	first.assign(7);
	
	iter test = first.begin();
	iter test2 = first.end();

	while (test != test2)
		cout << *test++ << endl;

	vector<int>::iterator it;
	it = first.begin() + 1;

	second.assign(it, first.end() - 1);

	int myints[] = {1776, 7, 4};
	third.assign(myints, myints + 3);

	cout << "Size of first: " << first.size() << endl;
	cout << "Size of second: " << second.size() << endl;
	cout << "Size of third: " << third.size() << endl;
	return (0);
}
