#include "AgendaUI.hpp"
#include "sys/types.h"
#include "sys/wait.h"
AgendaUI aui;
void Safety(int sign) {
	std::cout << std::endl;
	exit(0);
	std::cout << std::endl;
}
int main() {
	signal(SIGINT, Safety);
    aui.OperationLoop();
    return 0;
}