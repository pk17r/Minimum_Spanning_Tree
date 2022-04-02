#ifndef MY_PRIORITY_QUEUE_H_
#define	MY_PRIORITY_QUEUE_H_

#include <list>
#include "Neighbor.h"

class MyPriorityQueue
{
public:
	MyPriorityQueue();
	~MyPriorityQueue();

	void push(Neighbor city);

	Neighbor* top();

	Neighbor get_and_pop_top();

	bool contains_index(int index);

	Neighbor* member_with_index(int index);

	void sort();

	int size();

	void print();

private:
	std::list<Neighbor> my_list_;
};

#endif // !MY_PRIORITY_QUEUE_H_