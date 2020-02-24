#pragma once
#include <iostream>
enum Trit { UNKNOWN = 0, FALSE = 1, TRUE = 2 };

Trit operator~(Trit a);
Trit operator&(Trit a, Trit b);
Trit operator|(Trit a, Trit b);
void operator <<(std::ostream &os, const Trit& a);