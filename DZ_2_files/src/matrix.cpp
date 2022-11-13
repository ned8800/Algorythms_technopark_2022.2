#ifndef __MATRIX_H__
#define __MATRIX_H__

#include <matrix.hpp>

/*
template<class T>
class Queue {
    private:
        struct Node
        {
            Node* next;
            T data;
        };
    public:
        void push(const T& data){

        };
        T pop();


};
*/


// Task 1
int even_count(int number) {
    int evenSumm = 0;
    while(number != 0) {
        evenSumm += (number & 1);
        number = number >> 2;
    }
    return evenSumm;
}


// Task 2
int exponent_search(int a_size, int *a, int element) {
    int buff = a_size;
    int j = 1;
    while(j <=a_size) {
        if(element <= a[j-1]) {
            buff = j-1;
            break;
        }
        j = j << 1;
        if(j >a_size) {
            if(a[a_size-1] >= element) {
                buff = a_size-1;
                break;
            }
            else {
                buff = a_size;
                break;
            }
        }
    }
    return buff;
}

int * find_min_ind_for_element(int a_size, int b_size, int *a, int *b) {
    int *buff = new int[b_size];
    int left = 0;
    int right = 0;
    int mid = 0;

    for(int i = 0; i < b_size; ++i) {
        mid = 0;
        left = 0;
        right = exponent_search(a_size, a, b[i]);
        while(left < right) {
            mid = (left + right) / 2;
            if(a[mid] >= b[i]) {
                right = mid;
            }
            else {
                left = mid + 1;
            }
        }
        if(a[right] >= b[i]) {
            buff[i] = right;
        }
        else {
            buff[i] = a_size;
        }
    }

    return buff;
}

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
			if (!comp(buf[ind], buf[parent])) {
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


#endif // __MATRIX_H__
