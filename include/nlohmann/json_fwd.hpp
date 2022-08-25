//     __ _____ _____ _____
//  __|  |   __|     |   | |  JSON for Modern C++
// |  |  |__   |  |  | | | |  version 3.11.2
// |_____|_____|_____|_|___|  https://github.com/nlohmann/json
//
// SPDX-FileCopyrightText: 2013-2022 Niels Lohmann <https://nlohmann.me>
// SPDX-License-Identifier: MIT

#ifndef INCLUDE_NLOHMANN_JSON_FWD_HPP_
#define INCLUDE_NLOHMANN_JSON_FWD_HPP_

#include <cstdint> // int64_t, uint64_t
#include <map> // map
#include <memory> // allocator
#include <string> // string
#include <vector> // vector
#include <memory_resource>

#include <nlohmann/detail/abi_macros.hpp>

/*!
@brief namespace for Niels Lohmann
@see https://github.com/nlohmann
@since version 1.0.0
*/
NLOHMANN_JSON_NAMESPACE_BEGIN

/*!
@brief default JSONSerializer template argument

This serializer ignores the template arguments and uses ADL
([argument-dependent lookup](https://en.cppreference.com/w/cpp/language/adl))
for serialization.
*/
template<typename T = void, typename SFINAE = void>
struct adl_serializer;

template <typename at>
class polymorphic_allocator_t {
  private:
    std::pmr::memory_resource* resource_;

  public:
    using value_type = at;
    using size_type = size_t;

    explicit polymorphic_allocator_t(std::pmr::memory_resource* resource = std::pmr::get_default_resource()) : resource_(resource) {};
    void deallocate(at* ptr, size_t size) { resource_->deallocate(ptr, sizeof(at) * size); }
    at* allocate(size_t size) {
        return reinterpret_cast<at*>(resource_->allocate(sizeof(at) * size));
    }
};


/// a class to store JSON values
/// @sa https://json.nlohmann.me/api/basic_json/
template<template<typename U, typename V, typename... Args> class ObjectType =
         std::map,
         template<typename U, typename... Args> class ArrayType = std::vector,
         class StringType = std::string, class BooleanType = bool,
         class NumberIntegerType = std::int64_t,
         class NumberUnsignedType = std::uint64_t,
         class NumberFloatType = double,
         template<typename U> class AllocatorType = polymorphic_allocator_t,
         template<typename T, typename SFINAE = void> class JSONSerializer =
         adl_serializer,
         class BinaryType = std::vector<std::uint8_t>>
class basic_json;

/// @brief JSON Pointer defines a string syntax for identifying a specific value within a JSON document
/// @sa https://json.nlohmann.me/api/json_pointer/
template<typename RefStringType>
class json_pointer;

/*!
@brief default specialization
@sa https://json.nlohmann.me/api/json/
*/
using json = basic_json<>;

namespace pmr {
    using json = basic_json<std::map, std::vector, std::string, bool, std::int64_t, std::uint64_t, double, std::pmr::polymorphic_allocator, adl_serializer, std::vector<std::uint8_t>>;
}
/// @brief a minimal map-like container that preserves insertion order
/// @sa https://json.nlohmann.me/api/ordered_map/
template<class Key, class T, class IgnoredLess, class Allocator>
struct ordered_map;

/// @brief specialization that maintains the insertion order of object keys
/// @sa https://json.nlohmann.me/api/ordered_json/
using ordered_json = basic_json<nlohmann::ordered_map>;

NLOHMANN_JSON_NAMESPACE_END

#endif  // INCLUDE_NLOHMANN_JSON_FWD_HPP_
