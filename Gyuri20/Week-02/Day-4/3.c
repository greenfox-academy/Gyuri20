#include <stdio.h>

int main() {
    int int_array[] = {1, 654, 987, 654, 31};
    float float_array[] = {1.2, 3.14, 1.41, 0.707, 1.73};

	//TODO:
	for(int i = 0; i < 5 ; i++){
        printf("%d\n", int_array [i]);
	}
    for(int i = 0; i < 5 ; i++){
        printf("%f\n", float_array [i]);
    }

    // Print out the content of the arrays

    return 0;
}
