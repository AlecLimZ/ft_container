/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/15 19:00:52 by leng-chu         ###   ########.fr       */
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
	std::vector<int> myvector(3, 100);
	std::vector<int>::iterator it;

	it = myvector.begin();
	it = myvector.insert(it , 200);

	for (vector<int>::size_type i = 0; i < myvector.size(); ++i)
		cout << myvector[i] << " ";
	cout << endl;

	myvector.insert(it, 2, 300);
	
	for (vector<int>::size_type i = 0; i < myvector.size(); ++i)
		cout << myvector[i] << " ";
	cout << endl;

	// "it" no longer valid, get a new one
//	it = myvector.begin();
	cout << "TEST" << endl;
	for (vector<int>::size_type i = 0; i < myvector.size(); ++i)
		cout << myvector[i] << " ";
	cout << endl;

	std::vector<int> anothervector(2, 400);
	for (vector<int>::size_type i = 0; i < anothervector.size(); ++i)
		cout << anothervector[i] << " ";
	cout << endl;
	myvector.insert(it + 2, anothervector.begin(), anothervector.end());
	for (vector<int>::size_type i = 0; i < myvector.size(); ++i)
		cout << myvector[i] << " ";
	cout << endl;

	int myarray[] = {501, 502, 503};
	myvector.insert(myvector.begin(), myarray, myarray + 3);

	cout << "final myvector contains: ";
	for (it = myvector.begin(); it < myvector.end(); ++it)
		cout << *it << " ";
	cout << endl;
	return (0);
}
