#ifndef SES_HPP
#define SES_HPP

#include <vector>

namespace ses {

namespace detail {

/**
 * Type Family templates for auto incrementing a 
 * inheriting type's id().
 */
template <class T>
struct Family {
	static size_t& counter() {
		static size_t counter_ = 0;
		return counter_;
	}
};

template <class Family, class T>
struct Type {
	static size_t& id() {
		static size_t id_ = Family::counter()++;
		return id_;
	}
};

/**
 * Templates for generating lists of type ids from
 * variadic template parameters.
 */
template <class... Types>
void make_type_list(std::vector<size_t>& list) {
	list.insert(list.end(), {Types::id()...});
}

template <class... Types>
struct TypeList {
	static std::vector<size_t> list() {
		std::vector<size_t> list_;
		make_type_list<Types...>(list_);
		return list_;
	}
};

} // namespace detail

/**
 * Component.
 */
struct ComponentFamily : detail::Family<ComponentFamily> {};

struct ComponentBase {
	virtual ~ComponentBase() {}
};

template <class T>
struct Component : detail::Type<ComponentFamily, T>, ComponentBase {};

/**
 * System.
 */
struct SystemFamily : detail::Family<SystemFamily> {};

struct SystemBase {
	SystemBase(const std::vector<size_t>& includes, const std::vector<size_t>& excludes) : 
		includes(includes), excludes(excludes) {}
	virtual ~SystemBase() {}

	std::vector<size_t> includes;
	std::vector<size_t> excludes;
};

template <class... Types>
struct Includes : detail::TypeList<Types...> {};

template <class... Types>
struct Excludes : detail::TypeList<Types...> {};

template <class T, class IncludeList = Includes<>, class ExcludeList = Excludes<>>
struct System : detail::Type<SystemFamily, T>, SystemBase {
	System() : SystemBase(IncludeList::list(), ExcludeList::list()) {}
};

} // namespace ses

#endif

