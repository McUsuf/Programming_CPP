#include "TritSet.h"
TritSet operator& (TritSet a, TritSet b)//Operator "&" for TritSet
{
	TritSet output = TritSet(max(a.GetNumberOfStoredTrits(), b.GetNumberOfStoredTrits()));
	for (size_t i = 0; i < output.GetNumberOfStoredTrits(); i++)
		output[i] = a[i] & b[i];
	return output;
}
TritSet operator| (TritSet a, TritSet b)//Operator "|" for TritSet
{
	TritSet output = TritSet(max(a.GetNumberOfStoredTrits(), b.GetNumberOfStoredTrits()));
	for (size_t i = 0; i < output.GetNumberOfStoredTrits(); i++)
		output[i] = a[i] | b[i];
	return output;
}
TritSet operator! (TritSet a)//Operator "!" for TritSet
{
	TritSet output = a;
	for (size_t i = 0; i < output.GetNumberOfStoredTrits(); i++)
		output[i] = ~output[i];
	return output;
}
bool operator== (TritSet a, TritSet b)//Operator "==" for TritSet
{
	for (size_t i = 0; i < max(a.GetNumberOfStoredTrits(), b.GetNumberOfStoredTrits()); i++)
		if (a[i] != b[i])
			return false;
	return true;
}
TritSet::TritSet(const size_t size)//Constructor for TritSet (SIZE is how many Trits objects will store)
{
	BufSize = size * 2 / 8 / sizeof(uint);
	if ((size % (sizeof(size_t) * 8 / 2)) != 0)
		BufSize++;
	class Reference {
		friend class TritSet;
	private:
		int index;
		TritSet* CurSet;
	public:
		Reference(TritSet *CurSer, int index);
		operator Trit();
		void operator = (const Trit a);
		Trit GetTrit();
		void SetTrit(const Trit a);
	};
	NumberOfStoredTrits = size;
	buf.resize(BufSize);
	for (size_t i = 0; i < BufSize; i++)
		buf[i] = 0; //set all the trist to unknown
}
TritSet::TritSet(const TritSet &a)//Copy constructor for TritSet
{
	BufSize = a.BufSize;
	buf.resize(BufSize);
	NumberOfStoredTrits = a.NumberOfStoredTrits;
	for (int i = 0; i < BufSize; i++)
		this->buf[i] = a.buf[i];
}
void TritSet::SetRandomly()
{
	for (size_t i = 0; i < this->GetNumberOfStoredTrits(); i++)
	{
		(*this)[i] = (Trit)(rand() % 3);
	}
}
TritSet::Reference::Reference(TritSet* const CurSet, const size_t index) : index(index), CurSet(CurSet) {}//Ñonstructor for Reference

size_t TritSet::capacity()
{
	return NumberOfStoredTrits * 2 / 8 /sizeof(uint);//Size of BUF in bytes
}
TritSet::Reference  TritSet::operator[](size_t index)//Operator "[]" for TritSet
{
	return Reference(this, index);
}

TritSet::Reference :: operator Trit() //Corversion from Reference to Trit
{
	return this->GetTrit();
}

void TritSet::Reference ::operator=(Trit a)//Operator "=" for Reference
{
	this->SetTrit(a);
}
Trit TritSet::Reference::GetTrit()//Returns Trit, to which posize_ts
{
	if (index > CurSet->NumberOfStoredTrits)
		return UNKNOWN;
	else
	{
		size_t shift = (index % (sizeof(uint) * 4)) * 2;
		size_t Shiftedsize_t = CurSet->buf[index / (sizeof(uint) * 4)] >> shift;
		return (Trit)((CurSet->buf[index / (sizeof(uint) * 4)] >> shift) & 0b11);
	}
}
void TritSet::Reference::SetTrit(Trit a)//Sets Trit, to which posize_ts
{
	if (index > CurSet->NumberOfStoredTrits)
	{
		if (a == UNKNOWN)
			return;
		CurSet->NumberOfStoredTrits = index + 1;
		CurSet->BufSize = (index + 1) * 2 / 8 / sizeof(uint);
		if (((index + 1) % (sizeof(size_t) * 8 / 2)) != 0)
			CurSet->BufSize++;
		CurSet->buf.resize(CurSet->BufSize);
	}
	size_t shift = (index % (sizeof(uint) * 4)) * 2;
	size_t BufIndex = index / (sizeof(uint) * 4); //in which uint in buf adressed trit contains
	CurSet->buf[BufIndex] = (CurSet->buf[BufIndex] & ~(0b11 << shift));
	uint Newsize_t = (uint)a << shift;
	this->CurSet->buf[BufIndex] = this->CurSet->buf[BufIndex] | Newsize_t;
}

size_t TritSet::cardinality(Trit value)//Returns the number of trits set to this value
{
	size_t sum = 0;
	for (size_t i = 0; i <= this->GetLastSettedTritIndex(); i++)
		if ((*this)[i] == value)
			sum++;
	return sum;
}
unordered_map<Trit, size_t> TritSet::cardinality()
{
	unordered_map<Trit, size_t> output;
	for (size_t i = 0; i <= this->GetLastSettedTritIndex(); i++)
		output[(*this)[i]]++;
	return output;
}
void TritSet::trim(size_t index)//Forgot all values, strating from LastIndex
{
	BufSize = index / (sizeof(uint) * 4) + 1;
	buf.resize(BufSize);
	NumberOfStoredTrits = index;
	int shift = (sizeof(int) * 4 - (index % (sizeof(int) * 4))) * 2;
	buf[BufSize - 1] = (buf[BufSize - 1] << shift) >> shift;
}
void TritSet::shrink()
{
	this->trim(this->GetLastSettedTritIndex());
}
size_t TritSet::GetLastSettedTritIndex()
{
	size_t output = NumberOfStoredTrits - 1;
	for (size_t i = NumberOfStoredTrits - 1; i >= 0; i--)
	{
		if ((*this)[i] != UNKNOWN)
			return i;
	}
	return -1; //if all trits are UNKNOWN
}
size_t TritSet::GetNumberOfStoredTrits()
{
	return this->NumberOfStoredTrits;
}
size_t max(size_t a, size_t b)
{
	if (a > b)
		return a;
	else
		return b;
}

void operator <<(std::ostream &os, TritSet& a)
{
	for (size_t i = 0; i < a.GetNumberOfStoredTrits(); i++)
	{
		os << a[i];
	}
	os << endl;
}