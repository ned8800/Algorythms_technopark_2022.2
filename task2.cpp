#include <iostream>
#include <cassert>
#include <queue>
//using namespace std;

static constexpr size_t START_HEAP_CAPACITY = 8;


//Task 2

template<typename T>
struct DefaultComparator {
	bool operator()(const T& left, const T& right) const {
		return left < right;
	}
};


/////////////////////////////////////////////////////////////////////////


// LevelOrderHeap
template <typename Comparator = DefaultComparator<int>>
class LevelOrderHeap {
	

	struct CBinaryNode {
		int Data;
		CBinaryNode* Left; // NULL, если нет.
		CBinaryNode* Right; // NULL, если нет.
		CBinaryNode* Parent; // NULL, если корень.
	};
	
public:
	LevelOrderHeap(Comparator comp = Comparator()) : buffer_size(START_HEAP_CAPACITY), heap_size(0) {
		this->buf = new int[sizeof(int) * (START_HEAP_CAPACITY)];
		for(size_t = 0; i < START_HEAP_CAPACITY; ++i) {
			buf[i] = nullptr;
		}
	}

	//create heap with start buffer value
	LevelOrderHeap(size_t Buffer_size, Comparator comp = Comparator()) : buffer_size(Buffer_size), heap_size(0) {
		this->buf = new int[sizeof(int) * (Buffer_size)];
	};

	LevelOrderHeap(const LevelOrderHeap&) = delete;
	LevelOrderHeap(LevelOrderHeap&&) = delete;

	LevelOrderHeap& operator=(const LevelOrderHeap&) = delete;
	LevelOrderHeap& operator=(LevelOrderHeap&&) = delete;

	~LevelOrderHeap() {
		delete[] this->buf;
	}

	// Обход в ширину.
	void TraverseBFS( CBinaryNode* root ) {
		if( root == nullptr ) {
			return;
		}
		queue<CBinaryNode*> q;
		q.put( root );
		while( !q.empty() ) {
		CBinaryNode* node = q.pop();
		visit( node );
		if( node->Left != nullptr )
		q.push( node->Left );
		if( node->Right != nullptr )
		q.push( node->Right );
		}
	};

	
	bool is_empty() const {
		return (this->heap_size == 0);
	};
	private:
	/*
	void shift_down(size_t value) {
		size_t parent = 0;
		size_t left = 2 * parent + 1;
		size_t right = 2 * parent + 2;
		
		if(comp(value, buf[parent])) {
			parent = left;
			left = 2 * parent + 1;
			right = 2 * parent + 2;
		}
		else {
			parent = right;
			left = 2 * parent + 1;
			right = 2 * parent + 2;
		}
		*/

	void grow() {
		size_t new_buff_size = this->buffer_size*2;
		CBinaryNode* temp_buff = new CBinaryNode[sizeof(CBinaryNode) * (new_buff_size)];
		for(size_t i = 0; i < new_buff_size; ++i) {
			CBinaryNode tempNode;
			temp_buff[i] = tempNode;
		}
		
		for(size_t i = 0; i < buffer_size; ++i) {
			temp_buff[i] = this->buf[i];
		}

		for(size_t i = 0; i < buffer_size; ++i) {
			delete this->buf[i];
		}
		delete[]this->buf;
		this->buf = temp_buff;
		this->buffer_size = new_buff_size;
        }
	


	size_t buffer_size;
    Node* buf;
	Comparator comp;
};


// _____________КОНЕЦ РЕАЛИЗАЦИИ_________________________________


//MAIN FUNCTION
int main() {
	
	
	return 0;
}
