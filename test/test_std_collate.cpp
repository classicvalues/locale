//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifdef BOOST_LOCALE_NO_STD_BACKEND
#include <iostream>
int main()
{
        std::cout << "STD Backend is not build... Skipping" << std::endl;
}
#else

#include <boost/locale/config.hpp>
#include <boost/locale/conversion.hpp>
#include <boost/locale/localization_backend.hpp>
#include <boost/locale/generator.hpp>
#include <boost/locale/info.hpp>
#include <iomanip>
#include "test_locale.hpp"
#include "test_locale_tools.hpp"
#include <iostream>

int get_sign(int x)
{
    if(x<0)
        return -1;
    else if(x==0)
        return 0;
    return 1;
}

template<typename CharType>
void test_one(std::locale const &l,std::string ia,std::string ib,int diff)
{
    std::basic_string<CharType> a=to_correct_string<CharType>(ia,l);
    std::basic_string<CharType> b=to_correct_string<CharType>(ib,l);
    if(diff < 0) {
        TEST(l(a,b));
        TEST(!l(b,a));
    }
    else if(diff == 0) {
        TEST(!l(a,b));
        TEST(!l(b,a));
    }
    else {
        TEST(!l(a,b));
        TEST(l(b,a));
    }
    
    std::collate<CharType> const &col = std::use_facet<std::collate<CharType> >(l);

    TEST(diff == col.compare(a.c_str(),a.c_str()+a.size(),b.c_str(),b.c_str()+b.size()));
    TEST(diff == get_sign(col.transform(a.c_str(),a.c_str()+a.size()).compare(col.transform(b.c_str(),b.c_str()+b.size()))));
    if(diff == 0) {
        TEST(col.hash(a.c_str(),a.c_str()+a.size()) == col.hash(b.c_str(),b.c_str()+b.size()));
    }
}

template<typename CharType>
void test_char()
{
    boost::locale::generator gen;
    
    {
        std::cout << "- Testing at least C" << std::endl;
        std::locale l = gen("en_US.UTF-8");

        test_one<CharType>(l, "a", "b", -1);
        test_one<CharType>(l, "a", "a", 0);
    }

    std::string name;

    #if defined(_LIBCPP_VERSION) && (defined(__APPLE__) || defined(__FreeBSD__))
    std::cout << "- Collation is broken on this OS's standard C++ library, skipping" << std::endl;
    #else
    std::string names[] = { "en_US.UTF-8", "en_US.ISO8859-1" };
    for(unsigned i=0;i<sizeof(names)/sizeof(names[0]);i++) {
        name = get_std_name(names[i]);
        if(!name.empty()) {
            std::cout << "- Testing " << name << std::endl;
            std::locale l=gen(name);
            test_one<CharType>(l,"a","ç",-1);
            test_one<CharType>(l,"ç","d",-1);
        }
        else {
            std::cout << "- " << names[i] << " not supported, skipping" << std::endl;
        }
    }
    #endif
}


int main()
{
    try {
        boost::locale::localization_backend_manager mgr = boost::locale::localization_backend_manager::global();
        mgr.select("std");
        boost::locale::localization_backend_manager::global(mgr);

        std::cout << "Testing char" << std::endl;
        test_char<char>();
        std::cout << "Testing wchar_t" << std::endl;
        test_char<wchar_t>();
        #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
        std::cout << "Testing char16_t" << std::endl;
        test_char<char16_t>();
        #endif
        #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
        std::cout << "Testing char32_t" << std::endl;
        test_char<char32_t>();
        #endif
    }
    catch(std::exception const &e) {
        std::cerr << "Failed " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    FINALIZE();

}

#endif // NO STD

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4

// boostinspect:noascii 
