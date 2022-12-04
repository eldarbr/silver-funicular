#include <iostream>
using namespace std;

struct Element {
	int dataValue;
	int priorityValue;
};

struct Queue {
	Element element;
	bool isLast = true;
	Queue* nextElement = NULL;
};

/// <summary>
/// Create new queue from one element
/// </summary>
Queue* CreateQueue(Element element) {
	return new Queue{ element };
}

/// <summary>
/// Create new queue from one element and trailing queue
/// </summary>
Queue* CreateQueue(Element element, Queue* trailing) {
	return new Queue{ element, false, trailing };
}

/// <summary>
/// Insert new element into the queue
/// </summary>
Queue* Enqueue(Queue* queue, Element element) {
	// disallow insertion of elements with same priority value
	if (element.priorityValue == queue->element.priorityValue) {
		throw new exception("Elements with the same priority not allowed");
	}
	else if (element.priorityValue > queue->element.priorityValue) {
		return CreateQueue(element, queue);
	}
	else {
		if (queue->isLast) {
			queue->nextElement = CreateQueue(element);
			queue->isLast = false;
		}
		else {
			queue->nextElement = Enqueue(queue->nextElement, element);
		}
		return queue;
	}
}

/// <summary>
/// Locate and return the element with the lowest priority in the queue
/// </summary>
Element LowestPriorityElement(Queue* queue) {
	if (queue->isLast) {
		return queue->element;
	}
	else {
		return LowestPriorityElement(queue->nextElement);
	}
}

/// <summary>
/// Clear the queue
/// </summary>
void DeleteQueue(Queue* queue) {
	if (!queue->nextElement->isLast) {
		DeleteQueue(queue->nextElement);
	}
	delete queue->nextElement;
}

class ConsoleInterface {
public:
	static void OutputQueue(Queue* queue) {
		Queue* copy = queue;
		cout << "\nTable of content of the queue\n";
		cout << "data value:\t";
		while (copy != NULL) {
			cout << copy->element.dataValue << "\t";
			copy = copy->nextElement;
		}
		cout << "\n";
		cout << "priority:\t";
		while (queue != NULL) {
			cout << queue->element.priorityValue << "\t";
			queue = queue->nextElement;
		}
		cout << "\n";
	}


private:
	// disallow creating an instance of this object
	ConsoleInterface() {}
};


int main()
{
	Queue* myQueue = CreateQueue(Element{ 1,2 });
	myQueue = Enqueue(myQueue, Element{ 1,4 });
	myQueue = Enqueue(myQueue, Element{ 1,3 });
	ConsoleInterface::OutputQueue(myQueue);
	DeleteQueue(myQueue);
}
