/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/29 16:17:39 by leng-chu         ###   ########.fr       */
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
using std::iterator_traits;
using std::list;
using std::unordered_map;
using std::string;
using std::ostream;

template<typename _Iterator>
struct iterator_traits
{
	typedef typename _Iterator::iterator_category iterator_category;
	typedef typename _Iterator::value_type value_type;
	typedef typename _Iterator::difference_type difference_type;
	typedef typename _Iterator::pointer pointer;
	typedef typename _Iterator::reference reference;
};

class MyIterator
{
	public:
		using iterator_category = std::forward_iterator_tag;
		using value_type = int;
		using difference_type = int;
		using pointer = int*;
		using refernece = int&;
};

int main()
{
	vector<int> numbers = {};
	cout << std::reduce(begin(numbers), end(numbers)) << endl;
}
