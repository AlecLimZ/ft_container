/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cc                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 16:31:37 by leng-chu          #+#    #+#             */
/*   Updated: 2022/11/22 11:22:00 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "myclass.hpp"
#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include <unordered_map>
#include <memory> // for unique make

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::iterator_traits;
using std::list;
using std::unordered_map;
using std::string;

template <class _iter>
typename enable_if< _Is_iterator<_Iter>::value, void>::type
assign(__Iter _First, _Iter _Last)
{...}

void assign(size_type _Count, const value_type & Val)
{...}
