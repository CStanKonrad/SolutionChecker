#include "Time.hpp"

void CStoper::begin()
{
    gettimeofday(&startTime, NULL);
    isEnabled = true;
    return;
}
void CStoper::end()
{
    gettimeofday(&endTime, NULL);

    elapsedTime = (endTime.tv_sec - startTime.tv_sec)*1000;

    elapsedTime += (endTime.tv_usec - startTime.tv_usec)/1000.0;

    isEnabled = false;
    return;
}
double CStoper::getTime()
{
    return elapsedTime;
}
std::string CStoper::getTimeString()
{
    std::ostringstream strTime;
    unsigned long long currentTime = this->getTime();
    strTime << currentTime / 1000 << ".";

    std::string buffer;
    int i = 0;
    do
    {
        buffer += char(currentTime%10) + '0';
        currentTime /= 10;
        i++;
    }while (currentTime > 0 && i < 3);

    while (i < 3)
    {
        buffer += '0';
        i++;
    }

    i--;
    for (; i >= 0; i--)
    {
        strTime << buffer[i];
    }

    return strTime.str();

}
