/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/07 16:54:15 by leng-chu         ###   ########.fr       */
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

int main()
{
	vector<int> v = { 0, 1, 2, 3, 4, 5 };

	using RevIt = std::reverse_iterator<vector<int>::iterator>;

	vector<int>::iterator it = v.begin() + 4;
	//std::reverse_iterator<vector<int>::iterator>  r_it(it);
	vector<int>::reverse_iterator r_it(it);

	cout << "*it == " << *it << '\n'
		<< "*r_it == " << *r_it << '\n'
		<< "*r_it + 1== " << *r_it + 1 << '\n'
		<< "*r_it.base() == " << *r_it.base() << '\n'
		<< "*(r_it.base() - 1) == " << *(r_it.base() - 1) << '\n';

	it = r_it.base();
	cout << "*it == " << *it << endl;
	RevIt r_end{v.begin()};
	RevIt r_begin{v.end()};

	for (vector<int>::iterator it = r_end.base(); 
			it != r_begin.base(); ++it)
		cout << *it << " ";
	cout << endl;
}
