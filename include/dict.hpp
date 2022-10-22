#ifndef ICPP_DICT_H
#define ICPP_DICT_H

#include <string>
#include <unordered_map>
#include <vector>

namespace icpp {

namespace dict {
namespace native {
static const std::vector<std::string> keywords{"exit", "reset"};
}  // namespace native
namespace cpp {
static const std::vector<std::string> keywords{
    "alignas",
    "alignof",
    "and",
    "and_eq",
    "asm",
    "atomic_cancel",
    "atomic_commit",
    "atomic_noexcept",
    "auto",
    "bitand",
    "bitor",
    "bool",
    "break",
    "case",
    "catch",
    "char",
    "char8_t",
    "char16_t",
    "char32_t",
    "class",
    "compl",
    "concept",
    "const",
    "consteval",
    "constexpr",
    "constinit",
    "const_cast",
    "continue",
    "co_await ",
    "co_return",
    "co_yield ",
    "decltype",
    "default",
    "delete",
    "do",
    "double",
    "dynamic_cast",
    "else",
    "enum",
    "explicit",
    "export",
    "extern",
    "false",
    "float",
    "for",
    "friend",
    "goto",
    "if",
    "inline",
    "int",
    "long",
    "mutable",
    "namespace",
    "new",
    "noexcept",
    "not",
    "not_eq",
    "nullptr",
    "operator",
    "or",
    "or_eq",
    "private",
    "protected",
    "public",
    "reflexpr",
    "register",
    "reinterpret_cast",
    "requires",
    "return",
    "short",
    "signed",
    "sizeof",
    "static",
    "static_assert",
    "static_cast",
    "struct",
    "switch",
    "synchronized",
    "template",
    "this",
    "thread_local",
    "throw",
    "true",
    "try",
    "typedef",
    "typeid",
    "typename",
    "union",
    "unsigned",
    "using",
    "virtual",
    "void",
    "volatile",
    "wchar_t",
    "while",
    "xor",
    "xor_eq",
};
static const std::unordered_map<std::string, std::vector<std::string>>
    includes = {
        {{"string"},{"std::string"}},
        {"iostream", {"std::cout", "std::cin", "std::endl"}},
        {"vector", {"std::vector"}},
        {"regex",
         {"std::regex_match", "std::regex", "std::cmatch",
          "std::regex_search"}},
        {"map", {"std::map"}},
        {{"algorithm"},
         {
             "std::all_of",
             "std::any_of",
             "std::none_of",
             "std::ranges::all_of",
             "std::ranges::any_of",
             "std::ranges::none_of",
             "std::for_each",
             "std::ranges::for_each",
             "std::ranges::for_each_result",
             "std::for_each_n",
             "std::count",
             "std::count_if",
             "std::ranges::count",
             "std::ranges::count_if",
             "std::mismatch",
             "std::ranges::mismatch",
             "std::ranges::mismatch_result",
             "std::find",
             "std::find_if",
             "std::find_if_not",
             "std::ranges::find",
             "std::ranges::find_if",
             "std::ranges::find_if_not",
             "std::ranges::find_last",
             "std::ranges::find_last_if",
             "std::ranges::find_last_if_not",
             "std::find_end",
             "std::ranges::find_end",
             "std::find_first_of",
             "std::ranges::find_first_of",
             "std::adjacent_find",
             "std::ranges::adjacent_find",
             "std::search",
             "std::ranges::search",
             "std::search_n",
             "std::ranges::search_n",
             "std::ranges::starts_with",
             "std::ranges::ends_with",
             "std::copy",
             "std::copy_if",
             "std::ranges::copy",
             "std::ranges::copy_if",
             "std::ranges::copy_result",
             "std::ranges::copy_if_result",
             "std::copy_n",
             "std::ranges::copy_n",
             "std::ranges::copy_n_result",
             "std::copy_backward",
             "std::ranges::copy_backward",
             "std::ranges::copy_backward_result",
             "std::move",
             "std::ranges::move",
             "std::ranges::move_result",
             "std::move_backward",
             "std::ranges::move_backward",
             "std::ranges::move_backward_result",
             "std::fill",
             "std::ranges::fill",
             "std::fill_n",
             "std::ranges::fill_n",
             "std::transform",
             "std::ranges::transform",
             "std::ranges::unary_transform_result",
             "std::ranges::binary_transform_result",
             "std::generate",
             "std::ranges::generate",
             "std::generate_n",
             "std::ranges::generate_n",
             "std::remove",
             "std::remove_if",
             "std::ranges::remove",
             "std::ranges::remove_if",
             "std::remove_copy",
             "std::remove_copy_if",
             "std::ranges::remove_copy",
             "std::ranges::remove_copy_if",
             "std::ranges::remove_copy_result",
             "std::ranges::remove_copy_if_result",
             "std::replace",
             "std::replace_if",
             "std::ranges::replace",
             "std::ranges::replace_if",
             "std::swap",
             "std::swap_ranges",
             "std::ranges::swap_ranges",
             "std::ranges::swap_ranges_result",
             "std::iter_swap",
             "std::reverse",
             "std::ranges::reverse",
             "std::reverse_copy",
             "std::ranges::reverse_copy",
             "std::ranges::reverse_copy_result",
             "std::rotate",
             "std::ranges::rotate",
             "std::rotate_copy",
             "std::ranges::rotate_copy",
             "std::ranges::rotate_copy_result",
             "std::shift_left",
             "std::shift_right",
             "std::ranges::shift_left",
             "std::ranges::shift_right",
             "std::random_shuffle",
             "std::shuffle",
             "std::ranges::shuffle",
             "std::sample",
             "std::ranges::sample",
             "std::unique",
             "std::ranges::unique",
             "std::ranges::unique_copy",
             "std::ranges::unique_copy_result",
             "std::unique_copy",
             "std::is_partitioned",
             "std::ranges::is_partitioned",
             "std::partition",
             "std::ranges::partition",
             "std::partition_copy",
             "std::ranges::partition_copy",
             "std::ranges::partition_copy_result",
             "std::stable_partition",
             "std::ranges::stable_partition",
             "std::partition_point",
             "std::ranges::partition_point",
             "std::is_sorted",
             "std::ranges::is_sorted",
             "std::is_sorted_until",
             "std::ranges::is_sorted_until",
             "std::sort",
             "std::ranges::sort",
             "std::partial_sort",
             "std::ranges::partial_sort",
             "std::partial_sort_copy",
             "std::ranges::partial_sort_copy",
             "std::ranges::partial_sort_copy_result",
             "std::stable_sort",
             "std::ranges::stable_sort",
             "std::nth_element",
             "std::ranges::nth_element",
             "std::lower_bound",
             "std::ranges::lower_bound",
             "std::upper_bound",
             "std::ranges::upper_bound",
             "std::binary_search",
             "std::ranges::binary_search",
             "std::equal_range",
             "std::ranges::equal_range",
             "std::merge",
             "std::ranges::merge",
             "std::ranges::merge_result",
             "std::inplace_merge",
             "std::ranges::inplace_merge",
             "std::includes",
             "std::ranges::includes",
             "std::set_difference",
             "std::ranges::set_difference",
             "std::ranges::set_difference_result",
             "std::set_intersection",
             "std::ranges::set_intersection",
             "std::ranges::set_intersection_result",
             "std::set_symmetric_difference",
             "std::ranges::set_symmetric_difference",
             "std::ranges::set_symmetric_difference_result",
             "std::set_union",
             "std::ranges::set_union",
             "std::ranges::set_union_result",
             "std::is_heap",
             "std::ranges::is_heap",
             "std::is_heap_until",
             "std::ranges::is_heap_until",
             "std::make_heap",
             "std::ranges::make_heap",
             "std::push_heap",
             "std::ranges::push_heap",
             "std::pop_heap",
             "std::ranges::pop_heap",
             "std::sort_heap",
             "std::ranges::sort_heap",
             "std::max",
             "std::ranges::max",
             "std::max_element",
             "std::ranges::max_element",
             "std::min",
             "std::ranges::min",
             "std::min_element",
             "std::ranges::min_element",
             "std::ranges::minmax",
             "std::ranges::minmax_result",
             "std::minmax",
             "std::ranges::minmax_element",
             "std::ranges::minmax_element_result"
             "std::clamp",
             "std::ranges::clamp",
             "std::equal",
             "std::ranges::equal",
             "std::lexicographical_compare",
             "std::ranges::lexicographical_compare",
             "std::lexicographical_compare_three_way",
             "std::is_permutation",
             "std::ranges::is_permutation",
             "std::next_permutation",
             "std::ranges::next_permutation",
             "std::ranges::next_permutation_result",
             "std::prev_permutation",
             "std::ranges::prev_permutation",
             "std::ranges::prev_permutation_result",
         }},
        {{"numeric"},
         {"std::iota", "std::ranges::iota", "std::ranges::iota_result",
          "std::accumulate", "std::inner_product", "std::adjacent_difference",
          "std::partial_sum", "std::reduce", "std::exclusive_scan",
          "std::inclusive_scan", "std::transform_reduce",
          "std::transform_exclusive_scan", "std::transform_inclusive_scan"}},
        {{"memory"},
         {"std::make_shared", "std::make_shared_for_overwrite",
          "std::make_unique", "std::make_unique_for_overwrite",
          "std::allocate_shared", "std::allocate_shared_for_overwrite"
          "std::static_pointer_cast", "std::dynamic_pointer_cast", "std::const_pointer_cast", "std::reinterpret_pointer_cast",
          "std::get_deleter"
          "std::unique_ptr",
          "std::shared_ptr",
          "std::weak_ptr",
          "std::owner_less",
          "std::enable_shared_from_this",
          "std::bad_weak_ptr",
          "std::default_delete",
          "std::out_ptr_t",
          "std::out_ptr",
          "std::inout_ptr_t",
          "std::inout_ptr",
          "std::allocator",
          "std::allocator_traits",
          "std::allocation_result",
          "std::allocate_at_least",
          "std::allocator_arg",
          "std::uses_allocator",
          "std::uses_allocator_construction_args",
          "std::make_obj_using_allocator",
          "std::uninitialized_construct_using_allocator",
          "std::scoped_allocator_adaptor",
          "std::pmr::polymorphic_allocator",
          "std::pmr::memory_resource",
          "std::pmr::new_delete_resource",
          "std::pmr::null_memory_resource",
          "std::pmr::get_default_resource",
          "std::pmr::set_default_resource",
          "std::pmr::pool_options",
          "std::pmr::synchronized_pool_resource",
          "std::pmr::unsynchronized_pool_resource",
          "std::pmr::monotonic_buffer_resource",
          "std::raw_storage_iterator",
          "std::get_temporary_buffer",
          "std::return_temporary_buffer",
          "std::uninitialized_copy",
          "std::ranges::uninitialized_copy",
          "std::ranges::uninitialized_copy_result",
          "std::uninitialized_copy_n",
          "std::ranges::uninitialized_copy_n",
          "std::ranges::uninitialized_copy_n_result",
          "std::uninitialized_fill",
          "std::ranges::uninitialized_fill",
          "std::uninitialized_fill_n",
          "std::ranges::uninitialized_fill_n",
          "std::uninitialized_move",
          "std::ranges::uninitialized_move",
          "std::ranges::uninitialized_move_result",
          "std::uninitialized_move_n",
          "std::ranges::uninitialized_move_n",
          "std::ranges::uninitialized_move_n_result",
          "std::uninitialized_default_construct",
          "std::ranges::uninitialized_default_construct",
          "std::uninitialized_default_construct_n",
          "std::ranges::uninitialized_default_construct_n",
          "std::uninitialized_value_construct",
          "std::ranges::uninitialized_value_construct",
          "std::uninitialized_value_construct_n",
          "std::ranges::uninitialized_value_construct_n",
          "std::destroy",
          "std::ranges::destroy",
          "std::destroy_n",
          "std::ranges::destroy_n",
          "std::destroy_at",
          "std::ranges::destroy_at",
          "std::construct_at",
          "std::ranges::construct_at"}},
        {{"cstdlib"}, {"qsort", "bsearch"}},
        {{"concepts"}, {
          "std::same_as", 
          "std::derived_from",
          "std::convertible_to",
          "std::common_reference_with",
          "std::common_with",
          "std::signed_integral",
          "std::unsigned_integral",
          "std::floating_point",
          "std::assignable_from",
          "std::swappable", 
          "std::swappable_with",
          "std::destructible",
          "std::constructible_from",
          "std::default_initializable",
          "std::move_constructible",
          "std::copy_constructible",
          "std::equality_comparable", 
          "std::equality_comparable_with",
          "std::totally_ordered", 
          "std::totally_ordered_with",
          "std::movable",
          "std::copyable",
          "std::semiregular",
          "std::invocable",
          "std::regular_invocable",
          "std::predicate",
          "std::relation",
          "std::equivalence_relation",
          "std::strict_weak_order",
          "std::ranges::swap"}},
          {{"string"},{
            "std::char_traits",
            "std::basic_string",
            "std::getline",
            "std::stoi",
            "std::stol",
            "std::stoll",
            "std::stoul",
            "std::stoull",
            "std::stof",
            "std::stod",
            "std::stold",
            "std::to_string",
            "std::to_wstring"}},
            {{"charconv"},
            {"std::chars_format",
            "std::from_chars", 
            "std::from_chars_result", 
            "std::to_chars", 
            "std::to_chars_result"}}, 
            {{"tuple"},{
              "std::tuple",
              "std::tuple_size",
              "std::tuple_element",
              "std::tuple_size<std::tuple>",
              "std::tuple_element<std::tuple>",
              "std::uses_allocator<std::tuple>",
              "std::ignore",
              "std::make_tuple",
              "std::tie",
              "std::forward_as_tuple",
              "std::tuple_cat",
              "std::apply",
              "std::make_from_tuple"}}};
}  // namespace cpp
}  // namespace dict
}  // namespace icpp
#endif