#include <iostream>
#include <cassert>
#include <random>

using namespace std;

//Task 6
template<typename T>
struct DefaultComparator {
	bool operator()(const T& left, const T& right) const {
		return left < right;
	}
};

// Dynamic Array
template <typename T, typename Comparator = DefaultComparator<T>>
class DynamMass {
public:
	DynamMass(Comparator comp = Comparator());

	//create DynamMass with buffer
	DynamMass(size_t Mass_size, Comparator comp = Comparator()) : mass_size(Mass_size) {
		buffer_size = 1;
		buffer_size = buffer_size << 1*(Mass_size/2 + 1);
		this->buf = new T[sizeof(T) * (buffer_size)];
	};

	DynamMass(const DynamMass&) = delete;
	DynamMass(DynamMass&&) = delete;

	DynamMass& operator=(const DynamMass&) = delete;
	DynamMass& operator=(DynamMass&&) = delete;

	~DynamMass() {
		delete[] this->buf;
	}

	T& operator[] (size_t ind){
		assert(!(this->is_empty()));
		return (this->buf[ind]);
	};

	void pop() {
		assert(!(this->is_empty()));
		this->buf[0] = this->buf[this->mass_size - 1];
		mass_size -= 1;
		this->shift_down(0);
	};

	void push(const T& value) {
		// пока размер меньше буффера
		if(this->buffer_size > this->mass_size) {
			this->mass_size += 1;
			buf[mass_size-1] = value;
		}
		else {
			// если размер больше буффера
			if(this->comp(this->top(), value)) {
				this->pop();
				this->mass_size += 1;
				buf[mass_size-1] = value;
				this->shift_up(mass_size-1);
			}
		}
	cout << mymass.is_empty() << endl;
	mymass.get_capacity();
	mymass.extend();
	}

	bool is_empty() const {
		return (this->mass_size == 0);
	};

	size_t size() const {
		return this->mass_size;
	}

	void get_capacity() {
		std::cout << this->mass_size << " " << this->buffer_size << std::endl;
	};

	void extend() {
		buffer_size = buffer_size << 1;
		T* temp = new T[sizeof(T) * (buffer_size)];
		for(size_t i = 0; i < this->buffer_size; ++i) {
			temp[i] = buf[i];
		}
		delete[] this->buf;
		this->buf = temp;
	}
private:


	T* buf;
	size_t buffer_size;
	size_t mass_size;

	Comparator comp;

};


// _____________КОНЕЦ РЕАЛИЗАЦИИ МАССИВА__________________________________
/*
template <typename T, typename Comparator = DefaultComparator<T>>
int partition(T *arr, int l, int r, Comparator cmp = Comparator()) {
    int pivot_idx = l + (r - l)/2;
    T pivot = arr[pivot_idx];
    std::swap(arr[pivot_idx], arr[r - 1]);
	int i = 0;
	int j = r-1;
    while(i < j) {
		for(; cmp(arr[i], pivot); ++i);
		while(!cmp(arr[j], pivot)) {
			j--;
		}
		if(i < j) {
			std::swap(arr[i], arr[j]);
			i++;
			j--;
		}
    }
	std::swap(arr[i], arr[r - 1]);
	return i;
}
*/

//MAIN FUNCTION
int main() {
	size_t K = 1;
	int a = 6;
	int b = 9;
	DynamMass<int> mymass(K);
	cout << mymass.is_empty() << endl;
	mymass.get_capacity();
	mymass.extend();
	mymass.get_capacity();
	mymass[0] = 1;
	cout << mymass[0] << endl;
	cout << "___" << (rand() % (b - a + 1) + a) << endl;
	return 0;
}
