/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Except.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leng-chu <-chu@student.42kl.edu.my>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/05 15:45:48 by leng-chu          #+#    #+#             */
/*   Updated: 2023/01/05 15:53:23 by leng-chu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPT_H
# define EXCEPT_H

#ifndef NO_RTTI
	#include <typeinfo>
#endif

#ifdef SAFE_STL
	#include "mystring.h"
	#include "StartConv.h"
#else
	#include <string>
	using namespace std;
#endif

class DSException
{
	public:
		DSException(const string & msg = ""): message(msg)
		{}
		virtual ~DSException(){}
		virtual string toString() const
#ifndef NO_RTTI
		{ return "Exception" + string(typeid(*this).name()) + ": " + what(); }
#else
		{ return "Exception " + string(": ") + what(); }
#endif
		virtual string what() const
		{ return message; }

	private:
		string message;
};

class NullPointerException: public DSException
{
	public:
		NullPointerException(const string & msg = ""): DSException(msg){}
};

#endif
