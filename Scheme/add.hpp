#ifndef ADD_HPP
#define ADD_HPP
#include "is_container.hpp"
#include <algorithm>
#include <type_traits>
#include <boost/mpl/if.hpp>
#include <boost/mpl/and.hpp>
#include <boost/mpl/or.hpp>

namespace util {

template <class T>
using rm_ref_t = typename std::remove_reference<T>::type;

#define is_both_container(C1_t, C2_t) \
        is_container<C1_t>::value \
        && (is_container<C2_t>::value || std::is_array<C2_t>::value) \
        && std::is_convertible< \
            typename boost::mpl::if_< \
                std::is_array<C2_t>, \
                typename std::remove_extent<C2_t>::type, \
                typename C2_t::value_type>::type, \
            typename C1_t::value_type>::value

template <class C1, class C2>
typename std::enable_if<is_both_container(rm_ref_t<C1>, rm_ref_t<C2>), rm_ref_t<C1>>::type
add(C1&& c1, const C2& c2) {
    auto res(std::forward<C1>(c1));
    std::copy(begin(c2), end(c2), back_inserter(res));
    return res;
}

template <class C, class ... Args>
        typename std::enable_if<
            boost::mpl::and_<
                is_container<rm_ref_t<C>>,
                std::is_convertible<rm_ref_t<Args>, typename rm_ref_t<C>::value_type>...
            >::value, rm_ref_t<C>>::type
add(C&& c1, Args&& ... args) {
    using Container = rm_ref_t<C>;
    Container c2 = {static_cast<typename Container::value_type>(args)...};
    return add(std::forward<C>(c1), std::move(c2));
}

}
#endif
