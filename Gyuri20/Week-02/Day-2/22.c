#include <stdio.h>
#include <stdint.h>

int main() {

	uint8_t ac = 8;
	uint8_t time = 120;
	uint8_t out;

	if (ac % 4 == 0 && time <= 200){

        out = 0b100;
        printf("%d", out);
        }

    else

            if (ac % 4 == 0 && time > 200){

            out = 0b010;
            printf("%d", out);
            }

	else {
        out = 0b001;
        printf("%d", out);
	}
	// if ac is dividable by 4
	// and time is not more than 200
	// set out to 0b100
	// if time is more than 200
	// set out to 0b010
	// otherwise set out to 0b001
	return 0;
}
