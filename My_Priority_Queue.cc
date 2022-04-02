#include <algorithm>
#include <list>
#include "My_Priority_Queue.h"

using namespace std;

MyPriorityQueue::MyPriorityQueue()
{	
}

MyPriorityQueue::~MyPriorityQueue()
{
}

void MyPriorityQueue::push(Neighbor city)
{
	my_list_.push_back(city);
	sort();
}

Neighbor* MyPriorityQueue::top()
{
	return &(my_list_.front());
}

Neighbor MyPriorityQueue::get_and_pop_top()
{
	auto city = my_list_.front();
	my_list_.pop_front();
	return city;
}

bool MyPriorityQueue::contains_index(int index)
{
	for (Neighbor city : my_list_)
	{
		if (city.index == index)
			return true;
	}
	return false;
}

Neighbor* MyPriorityQueue::member_with_index(int index)
{
	for (Neighbor &city : my_list_)
	{
		if (city.index == index)
		{
			return &city;
		}
	}
	return nullptr;
}

void MyPriorityQueue::sort()
{
	auto cmpFn = [](Neighbor left, Neighbor right) {return left.distance < right.distance; };
	my_list_.sort(cmpFn);
}

int MyPriorityQueue::size()
{
	return static_cast<int>(my_list_.size());
}

void MyPriorityQueue::print()
{
	cout << "Open Set: ";
	for_each(my_list_.cbegin(), my_list_.cend(), [](Neighbor city) { cout << "\t(" << city.index << "|" << city.distance << ")"; });
	cout << endl;
}
