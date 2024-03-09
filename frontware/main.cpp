#include "systeme.h"

int main(void) {
	Systeme sys;
	sys.setLocalization();
	std::cout << sys.getLocalization() << std::endl;

	return 0;
}