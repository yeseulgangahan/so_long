#include <stdlib.h>
#include <unistd.h>

int main() {
	while (1) {
		system("leaks a.out");
		sleep(1); //1초마다 한 번씩 출력
	}
}