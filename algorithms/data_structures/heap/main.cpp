
#include <iostream>
#include <vector>

using namespace std;

class MaxHeap{
private:
	vector<int> items;
	int size;
protected:

	int getMaxChild(int i) {
		int left = 2 * i + 1;
		int right = 2 * i + 2;

		if (left >= size and right >= size) {
			throw std::out_of_range("Out of bound exeption");
		}
		
		int maxChild = i;

		if (items[left] > items[maxChild]) {
			maxChild = left;
		}
		
		if (right < size and items[right] > items[maxChild]) {
			maxChild = right;
		}
		return maxChild;
	}
public:
	

	void Heap() {
		size = 0;
	}

	int get() {
		if (size == 0) {
			throw std::out_of_range("Empty heap");
		}
		return items[0];
	}

	void add(int item) {
		items.push_back(item);
		
		int i = size;

		while (i > 0 and item > items[(i - 1) / 2]) {
			items[i] = items[(i - 1) / 2];
			items[(i - 1) / 2] = item;
			i = (i - 1) / 2;
		}
		size++;
	}
	
	int removeTop() {
		int top = get();
		
		items[0] = items[size - 1];
		size--;

		int i = 0;

		while (2 * i + 1 < size and getMaxChild(i) != i) {
			int maxChildIndex = getMaxChild(i);
			int iValue = items[i];
			items[i] = items[maxChildIndex];
			items[maxChildIndex] = iValue;			
			i = maxChildIndex;
		}
		return top;
	}

};

int main() {

	MaxHeap heap = MaxHeap();
	heap.add(1);
        std::cout << heap.get() << std::endl;
	heap.add(2);
        std::cout << heap.get() << std::endl;
	heap.add(3);
        std::cout << heap.get() << std::endl;
	heap.add(10);        
	std::cout << heap.get() << std::endl;
	heap.add(6);	
	std::cout << heap.get() << std::endl;
	// ----------------------------------
	heap.removeTop();
        std::cout << heap.get() << std::endl;
        heap.removeTop();
	std::cout << heap.get() << std::endl;
        
	return 0;
}
