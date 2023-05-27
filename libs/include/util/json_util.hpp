// json_util.hpp
#ifndef _JSON_UTIL_HPP_
#define _JSON_UTIL_HPP_

#include <boost/json.hpp>

using namespace boost::json;

namespace obj {
  /**
   * @brief Extract the value corresponding to the key from an object
   * 
   * @details extract() fetches the value corresponding to the key and
   * casts the type using boost::json::value_to<T>() function. The type
   * of the value will be determined by the type of t, which is used 
   * as the container of the value.
   * 
   * @tparam T - The expected type of the value
   * @param obj JSON Object to be fetched
   * @param key Key of the value
   * @param t Container of the value
   */
  template<class T>
  void extract(object const& obj, string_view key, T& t) {
    t = value_to<T>( obj.at( key ) );
  }
};

#endif