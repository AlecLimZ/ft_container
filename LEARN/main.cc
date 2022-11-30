/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/30 16:12:17 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myclass.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <unordered_map>
#include <memory> // for unique make
#include <type_traits> // for enable_if
#include <numeric> // for std::reduce

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

int main()
{
	vector<int> vec1;
	vector<char> vec2;
	list<char> lst;

	typedef iterator_traits<vector<int>::iterator>::iterator_category cati;
	typedef iterator_traits<vector<char>::iterator>::iterator_category catc;
	typedef iterator_traits<list<char>::iterator>::iterator_category catlst;

	// both are random-access iterators
	cout << "The type of iterator for vector<int> is identified by the tag: "<<" "
		<< typeid(cati).name() << endl;
	cout << "The type of iterator for vector<char> is identified by the tag: "<<" "
		<< typeid(catc).name()<< endl;
	cout << "\nOperation: typeid(cati) == typeid(catc)" << endl;
	if (typeid(cati) == typeid(catc))
		cout << "the iterators for vector are the same" << endl << endl;
	else
		cout << "the iterators for both vectors are not same" << endl << endl;

	// but the list iterator is bidirectional, not random access
	cout << "The type of iterator for list<char> is identified by the tag:"
		<< typeid(catlst).name() << endl;
	cout << "\nOperation: typeid(vec1.begin() == typeid(vec2.begin())" << endl;
	if (typeid(vec1.begin()) == typeid(vec2.begin()))
	{
		cout << " the iterator type for both vector's begin is same - "
			<< typeid(vec1.begin()).name() << " & " << typeid(vec2.begin()).name() << endl;
	}
	else
	{
		cout << "the iterator type for both vector's begin is not same - "
			<< typeid(vec1.begin()).name() << " & " << typeid(vec2.begin()).name() << endl;
	}
}
