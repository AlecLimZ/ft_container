/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 12:23:08 by leng-chu          #+#    #+#             */
/*   Updated: 2022/12/02 14:50:17 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ITER_HPP
# define ITER_HPP

// input_iterator_tag class below is meant to implement 
// in a container class
// but i write here just for learning & practice.
template <class T>
class iterinput
{
	T & _data;
	int _index;
	public:
		typedef std::input_iterator_tag iterator_category;

		iterinput(T & data): _data(data), _index(0){}
		iterinput(iterinput const & other): _data(other._data), _index(other._index){}
		iterinput & operator=(iterinput const & other)
		{
			if (this != other)
			{
				_data = other._data;
				_index = other._index;
			}
			return (*this);
		}
		typename T::iterator begin()
		{
			return (_data.begin());
		}
		typename T::iterator end()
		{
			return (_data.end());
		}
		int operator*() const
		{
			return (_data[_index]);
		}
		iterinput & operator++()
		{
			_index++;
			return (*this);
		}
		bool operator!=(const iterinput & other) const
		{
			return (_index != other._index);
		}
		bool operator==(const iterinput & other) const
		{
			return (_index == other._index);
		}
};

#endif
