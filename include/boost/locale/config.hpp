//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#ifndef BOOST_LOCALE_CONFIG_HPP_INCLUDED
#define BOOST_LOCALE_CONFIG_HPP_INCLUDED

#include <boost/config.hpp>

#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_LOCALE_DYN_LINK)
#   ifdef BOOST_LOCALE_SOURCE
#       define BOOST_LOCALE_DECL BOOST_SYMBOL_EXPORT
#   else
#       define BOOST_LOCALE_DECL BOOST_SYMBOL_IMPORT
#   endif  // BOOST_LOCALE_SOURCE
#else
#   define BOOST_LOCALE_DECL
#endif // BOOST_LOCALE_DYN_LINK

//
// Automatically link to the correct build variant where possible. 
// 
#if !defined(BOOST_ALL_NO_LIB) && !defined(BOOST_LOCALE_NO_LIB) && !defined(BOOST_LOCALE_SOURCE)
//
// Set the name of our library, this will get undef'ed by auto_link.hpp
// once it's done with it:
//
#define BOOST_LIB_NAME boost_locale
//
// If we're importing code from a dll, then tell auto_link.hpp about it:
//
#if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_LOCALE_DYN_LINK)
#  define BOOST_DYN_LINK
#endif
//
// And include the header that does the work:
//
#include <boost/config/auto_link.hpp>
#endif  // auto-linking disabled

#if defined(BOOST_LOCALE_HIDE_AUTO_PTR) || defined(BOOST_NO_AUTO_PTR)
#define BOOST_LOCALE_USE_AUTO_PTR 0
#else
#define BOOST_LOCALE_USE_AUTO_PTR 1
#endif

#ifdef BOOST_MSVC
// Denote a constant condition, e.g. for if(sizeof(...
#define BOOST_LOCALE_START_CONST_CONDITION __pragma(warning(push)) __pragma(warning(disable : 4127))
#define BOOST_LOCALE_END_CONST_CONDITION __pragma(warning(pop))
#else
#define BOOST_LOCALE_START_CONST_CONDITION
#define BOOST_LOCALE_END_CONST_CONDITION
#endif

#endif // boost/locale/config.hpp
// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

