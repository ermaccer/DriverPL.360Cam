#include "PatternHelper.h"
#include "../utils/Patterns.h"
using namespace hook::txn;

unsigned int _pat(const char* pattern, int offset, const char* func)
{
	unsigned int pat = (unsigned int)get_pattern(pattern,offset);
	return pat;
}
