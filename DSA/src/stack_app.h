#include <string>
#include "../DS_header/Stack/Stack.h"
using namespace std;

bool paren(string exp); //Brace matching(only "()").
string conversion(int num, int base); //Conversion e.g. 31(10) -> 1F(16).

char optr_cmp(char a, char b);
bool is_digit(char a);
double calculate_express(char* express);

template <class T>
bool if_stack_mix(T * a, T * b, int n);