#include "LevelTimerWidgetInterface.h"

void ULevelTimerWidgetInterface::addTime(int secondsToAdd)
{
	onAddTimeDelegate.Broadcast(secondsToAdd);
}
