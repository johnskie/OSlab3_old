#include "RTS.h"

using namespace std;

RTS::RTS(int numQueues, int at, int quantum, Process *processArray)
{
	this->at = at;
	this->quantum = quantum;
	this->processArray = processArray;
	totalwait = 0;
	totalTurnaround = 0;
	c = Clock();
	currentP = processArray;
}
// as far as i can remember rts cares aboutthe arrival time, the burst time(time quantum), and the end time
// once a process starts (sort by arrival time, then by priority and if that still doesnt do it, by PID)
// if the process finishes before it's alloted time quantum, insert the next process until the end of burst, then check for the next process to go (decrement runtime of inserted process as needed)
// make sure processes run by deadlines, if they cannot report them as failed (PID) and remove from queue
// ignore IO same as mfqs
void RTS::runProcess(Process *currentProcess, int q1, int curQuantum, int currentRemaining)
{
	if (q1 == 0)
	{
		totalWait = c.getTime() - currentProcess->getArrivalTime();
	}
	else
	{
		totalWait = totalWait = c.getTime() + currentProcess->getLastTime();
	}

	endTime = startTime + curQuantum;
	while (c.getTime() <= endTime && currentRemaining > 0)
	{
		c.incrementTme();
		currentProcess->decrementTime();
	}

	if (currentRemaining > 0)
	{
		currentProcess->setLastTime(endTime);
		queueList[q1 + 1].push(*currentProcess);
	}
	else
	{
		int diff = c.getTime() - currentProcess->getArrivalTime();
		totalTurnaround = totalTurnaround + diff;
	}

}

void RTS::scheduleProcesses()
{
	int procs, q, curQuan;
	bool comp = false;

	while (currentP != NULL && !comp
	{
		startTime = c.getTime();

		q = 0;
		curQuan = quantum;
		int atime = currentP->getArrivalTime();

		if (currentP != NULL && atime <= startTime)
		{
			runProcess(currentP, q, curQuan, currentP->getBurstTime());
			procs++
		}
		else
		{
			while(q < numQueues - 1 && &(queueList[q]) != NULL)
			{
				q++;
			}
		}
		if (q = 0 || q == numQueues - 1)
		{
			if (currentP != NULL)
			{
				while (currentP->getArrivalTime() > c.getTime())
				{
					c.incrementTime();
				}
			}
			else
			{
				comp = true;
			}
		}
		else if (q == numQueues - 2)
		{
			*currentP = queueList[q].front();
			queueList[q].pop();

			runProcess(currentP, q, currentP->getBurstTime(), currentP->getBurstTime());
		}
		else
		{
			for (int i = 0; i < q; i++)
			{
				curQuan = curQuan * 2;
			}
			
			//set next process
			*currentP = queueList[q].front();
			queueList[q].pop();

			//run the process
			runProcess(currentP, q, curQuan, currentP->getBurstRemaining());
		}

		while(&(queueList[numQueues - 1]) != NULL)
		{
			*currentP = queueList[numQueues - 1].empty())
			queueList[numQueues - 1].pop(); //pop up one queue of starving
			if (currentP->getLastTime()













