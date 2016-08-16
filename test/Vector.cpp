#include <cassert>
#include "../ses.hpp"

int main() {
	ses::detail::AutoVector<int> vector;

	// Starts out empty.
	assert(vector.size() == 0);

	// Grows automatically as needed.
	vector[2] = 2;
	assert(vector.size() == 3);
	assert(vector[2] == 2);

	// Iteration works.
	for (auto& e : vector) {
		(void)e;
	}

	// Const iteration works.
	for (const auto& e : vector) {
		(void)e;
	}

	return EXIT_SUCCESS;
}

