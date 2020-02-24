#include "Trit.h"
Trit operator~ (Trit a)
{
	if (a == FALSE)
		return TRUE;
	else if (a == TRUE)
		return FALSE;
	else
		return UNKNOWN;
}
Trit operator& (Trit a, Trit b)
{
	if (a == TRUE && b == TRUE)
		return TRUE;
	if (a == FALSE || b == FALSE)
		return FALSE;
	return UNKNOWN;
}
Trit operator| (Trit a, Trit b)
{
	if (a == FALSE && b == FALSE)
		return FALSE;
	if (a == TRUE || b == TRUE)
		return TRUE;
	return UNKNOWN;
}

void operator << (std ::ostream &os, const Trit& a)
{
		switch (a)
		{
		case FALSE:
			os << "FALSE    ";
			break;
		case UNKNOWN:
			os << "UNKNOWN  ";
			break;
		case TRUE:
			os << "TRUE     ";
			break;
		default:
			os << "KAVOOOOO ";
			break;
		}
}