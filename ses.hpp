#ifndef SES_HPP
#define SES_HPP

#include <vector>

namespace ses {

namespace detail {

/**
 * Basic vector implementation for inheritance.
 */
template <class T>
struct Vector {
	size_t size() const {
		return vector.size();
	}

	bool empty() const {
		return vector.empty();
	}

	typename std::vector<T>::iterator begin() {
		return vector.begin();
	}

	typename std::vector<T>::iterator end() {
		return vector.end();
	}

	typename std::vector<T>::const_iterator begin() const {
		return vector.begin();
	}

	typename std::vector<T>::const_iterator end() const {
		return vector.end();
	}

	void clear() {
		vector.clear();
	}

	T& operator[](size_t index) {
		return vector[index];
	}

	const T& operator[](size_t index) const {
		return vector[index];
	}

	std::vector<T> vector;
};

template <class T>
struct AutoVector : Vector<T> {
	T& operator[](size_t index) {
		if (index + 1 > vector.size()) {
			vector.resize(index + 1);
		}
		return vector[index];
	}
};

template <class T>
struct RecycleVector : Vector<T> {
};

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

