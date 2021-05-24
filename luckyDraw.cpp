#ifndef LUCKYDRAW_CPP
#define LUCKYDRAW_CPP
#include "luckyDraw.h"
#include "stack.cpp"
#include "queue.cpp"


luckyDraw::luckyDraw(int count)
{
	totalCount = count;
}

//populate lane_1 with the given array of winnersId
void luckyDraw::populateQueue(int* winnersId)
{
	for (int i = 0; i < totalCount; i++)
	{
		lane_1.enqueue(winnersId[i]);
	}
}

//populate table_1 with the given array of giftsId
void luckyDraw::populateTable(int* giftsId)
{
	for (int i = 0; i < totalCount; i++)
	{
		table_1.push(giftsId[i]);
	}
}

//reverse the queue keeping the conditions in mind
void luckyDraw::reverseQueue()
{
	//copy everything to lane_2
	while (lane_1.length() != 0)
	{
		lane_2.enqueue(lane_1.dequeue());

	}
	//run n-1 times and move front to lane_1
	while (lane_2.length() > 0)
	{
		for (int i = 0; i < lane_2.length() - 1; i++) {
			lane_2.enqueue(lane_2.dequeue());
		}
		lane_1.enqueue(lane_2.dequeue());
	}
}

//transfer the stack keeping the conditions in mind
void luckyDraw::transferStack()
{
	for (int j = table_1.length(); j > 0; j--)
	{
		specialVariable = table_1.pop();
		//runs n-1 times the length of table and pushes those
		// elements in table2
		for (int i=j; i-1>0;i--)
		{
			table_2.push(table_1.pop());//
		}
		table_1.push(specialVariable);
		while (table_2.length() > 0)
		{
			table_1.push(table_2.pop());//pushing back to table 1
		}
		

	}
	//table 1 is reversed and now putting everything back to table 2
		while(table_1.length()>0)
		{
			table_2.push(table_1.pop());
		}
}



#endif
