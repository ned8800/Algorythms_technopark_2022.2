#include <iostream>
#include <cassert>

using namespace std;

//Task 4
template<typename T>
struct DefaultComparator {
	bool operator()(const T& left, const T& right) const {
		return left < right;
	}
};

struct Point {
	int x;
	int y;
};

bool operator< (const Point& left, const Point& right) {
	return left.y < right.y;
}

// MinHEAP
template <typename T, typename Comparator = DefaultComparator<T>>
class MinHeap {
public:
	MinHeap(Comparator comp = Comparator());

	//create heap with buffer
	MinHeap(size_t Buffer_size, Comparator comp = Comparator()) : buffer_size(Buffer_size), heap_size(0) {
		this->buf = new T[sizeof(T) * (Buffer_size)];
	};

	MinHeap(const MinHeap&) = delete;
	MinHeap(MinHeap&&) = delete;

	MinHeap& operator=(const MinHeap&) = delete;
	MinHeap& operator=(MinHeap&&) = delete;

	~MinHeap() {
		delete[] this->buf;
	}

	const T& top() const {
		assert(!(this->is_empty()));
		return (this->buf[0]);
	};

	void pop() {
		assert(!(this->is_empty()));
		this->buf[0] = this->buf[this->heap_size - 1];
		heap_size -= 1;
		this->shift_down(0);
	};

	void push(const T& value) {
		// пока размер меньше буффера
		if(this->buffer_size > this->heap_size) {
			this->heap_size += 1;
			buf[heap_size-1] = value;
			this->shift_up(heap_size-1);
		}
		else {
			// если value больше корня кучи
			if(this->comp(this->top(), value)) {
				this->pop();
				this->heap_size += 1;
				buf[heap_size-1] = value;
				this->shift_up(heap_size-1);
			}
		}
	}

	bool is_empty() const {
		return (this->heap_size == 0);
	};

	size_t size() const {
		return this->heap_size;
	}

private:
	void shift_down(size_t ind) {
		size_t left = 2 * ind + 1;
		size_t right = 2 * ind + 2;
		//находим большего потомка
		size_t largest = ind;
		if((left < this->heap_size) && comp(buf[left], buf[ind])) {
			largest = left;
		}
		if((right < this->heap_size) && comp(buf[right], buf[largest])) {
			largest = right;
		}
		if(largest != ind) {
			swap(buf[ind], buf[largest]);
			shift_down(largest);
		}
	};

	void shift_up(size_t ind) {
		int parent = 0;
		while (ind > 0) {
			parent = (ind - 1) / 2;
			if (comp(buf[parent], buf[ind])) {
				return;
			}
			swap(buf[ind], buf[parent]);
			ind = parent;
		}
	};

	T* buf;
	size_t buffer_size;
	size_t heap_size;

	Comparator comp;

};


// _____________КОНЕЦ РЕАЛИЗАЦИИ КУЧИ__________________________________


//MAIN FUNCTION
int main() {
	size_t N = 0;
	size_t K = 0;
	cin >> N >> K;
	MinHeap<Point> myheap(K);
	Point temp;
	for(int i = 0; i < N; ++i) {
		cin >> temp.x;
		cin >> temp.y;
		myheap.push(temp);
	}
	while(!myheap.is_empty()) {
		cout << myheap.top().x << " ";
		myheap.pop();
	}
	return 0;
}
