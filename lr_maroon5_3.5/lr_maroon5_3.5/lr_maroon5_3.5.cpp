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
		throw "Elements with the same priority not allowed";
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
/// Locate and return element with the lowest priority in the queue
/// </summary>
Element FindLowestPriorityElement(Queue* queue) {
	if (queue->isLast) {
		return queue->element;
	}
	else {
		return FindLowestPriorityElement(queue->nextElement);
	}
}

/// <summary>
/// Locate and delete element with the lowest priority in the queue
/// </summary>
Queue* ExcludeLowestPriorityElement(Queue* queue) {
	if (queue->isLast) {
		delete queue;
		return NULL;
	}
	else if (queue->nextElement->isLast) {
		delete queue->nextElement;
		queue->nextElement = NULL;
		queue->isLast = true;
		return queue;
	}
	else {
		queue->nextElement = ExcludeLowestPriorityElement(queue->nextElement);
		return queue;
	}
}

/// <summary>
/// Clear the queue
/// </summary>
Queue* DeleteQueue(Queue* queue) {
	if (queue->isLast) {
		delete queue;
		return NULL;
	}
	if (!queue->nextElement->isLast) {
		DeleteQueue(queue->nextElement);
	}
	delete queue->nextElement;
	return NULL;
}

class ConsoleInterface {
public:
	enum ConsoleInputBBB { Creating, Acting };

	static void OutputQueue(Queue* queue) {
		cout << "\nTable of content of the queue\n";
		Queue* copy = queue;
		cout << "indices:\t";
		int i = 0;
		while (copy != NULL) {
			cout << i++ << "\t";
			copy = copy->nextElement;
		}
		copy = queue;
		cout << "\n";
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

	static void MainDialogue() {
		setlocale(LC_ALL, "rus");
		Queue* myQueue = NULL;
		int variant;
		int index;
		do {
			if (myQueue != NULL) {		// список задан
				system("cls");
				ConsoleInterface::OutputQueue(myQueue);
				cout
					<< "\nWhat's the matter?\n"
					<< "1. Add new element to the queue\n"
					<< "2. Find element with the lowest priority\n"
					<< "3. Find and exclude from the queue element with the lowest priority\n"
					<< "4. Delete whole queue\n"
					<< "5. Exit\n"
					<< "> ";
				variant = ConsoleInterfaceInput(Acting);
				switch (variant) {
				case 1:
					cout << "\nInput one pair of integers (value - priority)\n> ";
					int val, pr;
					cin >> val >> pr;

					try {
						myQueue = Enqueue(myQueue, Element{ val,pr });
					}
					catch (const char* msg) {
						cout << msg << endl;
						system("pause");
					}
					break;
				case 2:
					Element lowestPcasetwo = FindLowestPriorityElement(myQueue);
					cout << "\nFound element with the lowest priority:\n"
						<< "Value:\t\t" << lowestPcasetwo.dataValue << endl
						<< "Priority:\t" << lowestPcasetwo.priorityValue << endl << endl;
					system("pause");
					break;
				case 3:
					Element lowestPcasethree = FindLowestPriorityElement(myQueue);
					myQueue = ExcludeLowestPriorityElement(myQueue);
					cout << "\nFound element with the lowest priority:\n"
						<< "Value:\t\t" << lowestPcasethree.dataValue << endl
						<< "Priority:\t" << lowestPcasethree.priorityValue << endl << endl;
					cout << "New queue\n";
					ConsoleInterface::OutputQueue(myQueue);
					system("pause");
					break;
				case 4:
					myQueue = DeleteQueue(myQueue);
					break;
				}
			}
			else {					// список не задан
				system("cls");
				cout << "\tWhat's the matter?\n"
					<< "1. Create new queue\n"
					<< "2. Exit\n"
					<< "> ";
				variant = ConsoleInterfaceInput(Creating);
				switch (variant)
				{
				case 1:
					int n;
					cout << "\nWhat's the lenght of the queue: \n> ";
					cin >> n;
					if (n <= 0) {
						break;
					}
					int* arr = new int[2 * n];
					cout << "\nInput " << n << " pairs of integers (value - priority)\n> ";
					for (int i = 0; i < 2 * n; i++) cin >> arr[i];
					myQueue = CreateQueue(Element{ arr[0],arr[1] });
					for (int i = 2; i < 2 * n; i = i + 2) {
						try {
							myQueue = Enqueue(myQueue, Element{ arr[i], arr[i + 1] });
						}
						catch (const char* msg) {
							cout << msg << endl;
							myQueue = NULL;
							system("pause");
						}
					}
					break;
				}
			}
		} while (variant != 5 && myQueue != NULL || variant != 2 && myQueue == NULL);
	}

	static int ConsoleInterfaceInput(ConsoleInterface::ConsoleInputBBB putin) {
		int variant;
		cin >> variant;
		if (putin == Creating) {
			while (variant != 1 && variant != 2) {
				cout << "Wrong input. Try again > ";
				cin >> variant;
			}
		}
		else if (putin == Acting) {
			while (variant != 1 && variant != 2 && variant != 3 && variant != 4 && variant != 5) {
				cout << "Wrong input. Try again > ";
				cin >> variant;
			}
		}
		return variant;
	}

private:
	// disallow creating an instance of this object
	ConsoleInterface() {}
};


int main()
{
	ConsoleInterface::MainDialogue();
}
