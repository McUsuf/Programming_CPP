#include "Sort.h"
#include <algorithm>

void Sort::work(Flow &cur_flow)
{
	std::vector <std::string> cur_text = cur_flow.get_text();

	std::sort(cur_text.begin(), cur_text.end());
	
	cur_flow.set_text(cur_text);
}
