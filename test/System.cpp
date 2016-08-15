#include <cstdlib>
#include "../ses.hpp"

struct ComponentA : ses::Component<ComponentA> {};
struct ComponentB : ses::Component<ComponentB> {};
struct ComponentC : ses::Component<ComponentC> {};
struct ComponentD : ses::Component<ComponentD> {};

struct SystemA : ses::System<SystemA, 
		ses::Includes<ComponentA, ComponentC>, 
		ses::Excludes<ComponentB, ComponentD>> {
	void enter() {}
	void run() {}
	void leave() {}
};

struct SystemB : ses::System<SystemB, 
		ses::Includes<ComponentA, ComponentB>, 
		ses::Excludes<ComponentC, ComponentD>> {
	void enter() {}
	void run() {}
	void leave() {}
};

int main() {
	SystemA system_a;
	SystemB system_b;

	return EXIT_SUCCESS;
}

