#ifndef _JSON_UTIL_HPP_
#define _JSON_UTIL_HPP_

#include <boost/json.hpp>

using namespace boost::json;

namespace obj {
  template<class T>
  void extract(object const& obj, string_view key, T& t) {
    t = value_to<T>( obj.at( key ) );
  }


};

#endif