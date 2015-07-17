#include "Limit.hpp"

void CLimit::refresh()
{
    if (virtualMemory.size() != 0)
        memoryLimitArguments += std::string(" -Sv ") + virtualMemory;
    if (stackMemory.size() != 0)
        memoryLimitArguments += std::string(" -Ss ") + stackMemory;	//ulimit can only take one argument

    if (time.size() != 0)
        timeLimitArguments += time;
}
