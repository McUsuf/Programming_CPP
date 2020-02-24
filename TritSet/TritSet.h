#pragma once
#include "Trit.h"
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
#define uint unsigned int
class TritSet
{
private:
	class Reference {
		friend class TritSet;
	private:
		const size_t index;
		TritSet* const CurSet;
	public:
		Reference(TritSet* const, const size_t);
		operator Trit();
		void operator = (const Trit);
		Trit GetTrit();
		void SetTrit(const Trit);
	};
	vector <uint> buf;
	size_t NumberOfStoredTrits;
	size_t BufSize;
	size_t GetLastSettedTritIndex();
public:
	TritSet(const size_t);
	TritSet(const TritSet&);
	void SetRandomly();
	size_t capacity();
	Reference operator [] (const size_t);
	size_t cardinality(const Trit);
	unordered_map<Trit, size_t> cardinality();
	void trim(const size_t);
	void shrink();
	size_t GetNumberOfStoredTrits();
};
size_t max(const size_t a, const size_t b);
TritSet operator&(const	TritSet a, const TritSet b);
TritSet operator|(const TritSet a, const TritSet b);
TritSet operator!(const TritSet a);
bool operator==(const TritSet a, const TritSet b);
void operator <<(std::ostream &os, TritSet& a);