//
//  Copyright (c) 2009-2011 Artyom Beilis (Tonkikh)
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//
#define BOOST_LOCALE_SOURCE
#include <boost/locale/boundary.hpp>
#include <boost/locale/collator.hpp>
#include <boost/locale/conversion.hpp>
#include <boost/locale/date_time_facet.hpp>
#include <boost/locale/info.hpp>
#include <boost/locale/message.hpp>

#include <boost/core/ignore_unused.hpp>

namespace boost {
    namespace locale {

        std::locale::id info::id;
        // Make sure we have the VTable here (Export/Import issues)
        info::~info() {}
        std::locale::id calendar_facet::id;

        std::locale::id converter<char>::id;
        converter<char>::~converter() {}
        std::locale::id base_message_format<char>::id;

        std::locale::id converter<wchar_t>::id;
        converter<wchar_t>::~converter() {}
        std::locale::id base_message_format<wchar_t>::id;

        #ifdef BOOST_LOCALE_ENABLE_CHAR16_T

        std::locale::id converter<char16_t>::id;
        converter<char16_t>::~converter() {}
        std::locale::id base_message_format<char16_t>::id;

        #endif

        #ifdef BOOST_LOCALE_ENABLE_CHAR32_T

        std::locale::id converter<char32_t>::id;
        converter<char32_t>::~converter() {}
        std::locale::id base_message_format<char32_t>::id;

        #endif

        namespace boundary {        

            std::locale::id boundary_indexing<char>::id;
            boundary_indexing<char>::~boundary_indexing() {}

            std::locale::id boundary_indexing<wchar_t>::id;
            boundary_indexing<wchar_t>::~boundary_indexing() {}

            #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
            std::locale::id boundary_indexing<char16_t>::id;
            boundary_indexing<char16_t>::~boundary_indexing() {}
            #endif

            #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
            std::locale::id boundary_indexing<char32_t>::id;
            boundary_indexing<char32_t>::~boundary_indexing() {}
            #endif
        }

        namespace {
            // Initialize each facet once to avoid issues where doing so
            // in a multithreaded environment could cause problems (races)
            struct init_all {
                init_all()
                {
                    const std::locale& l = std::locale::classic();
                    init_by<char>(l);
                    init_by<wchar_t>(l);
                    #ifdef BOOST_LOCALE_ENABLE_CHAR16_T
                    init_by<char16_t>(l);
                    #endif
                    #ifdef BOOST_LOCALE_ENABLE_CHAR32_T
                    init_by<char32_t>(l);
                    #endif

                    init_facet<info>(l);
                    init_facet<calendar_facet>(l);
                }
                template<typename Char>
                void init_by(const std::locale& l)
                {
                    init_facet<boundary::boundary_indexing<Char> >(l);
                    init_facet<converter<Char> >(l);
                    init_facet<message_format<Char> >(l);
                }
                template<typename Facet>
                void init_facet(const std::locale& l)
                {
                    // Use the facet to initialize e.g. their std::locale::id
                    ignore_unused(std::has_facet<Facet>(l));
                }
            } facet_initializer;
        }

    }
}

// vim: tabstop=4 expandtab shiftwidth=4 softtabstop=4
