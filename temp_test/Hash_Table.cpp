#include <iostream>
#include <vector>
#include <math.h>




size_t str_hash(std::string& data) {
	size_t hash = 0;
	for(char i : data)
		hash = hash * 13 + i;
	return hash;
}

static constexpr size_t BUCKETS_COUNT[] = {
	7, 17 , 37, 73, 149, 251, 509, 1021, 2027, 5003, 10837
};


template<class Key> struct Hash {
	size_t operator()(const std::string& str) {
		
	}
};

template<> struct Hash<std::string> {
	size_t operator()(const std::string& str) {

	}
};


template<typename Key, typename Value>
class HashMap {
	struct Node {
		Node(const Key& k, const Value& v, Node* n) : key(k), value(v), next(n) {};
		
		Key key;
		Value value;
		Node* next;
	};


	constexpr size_t MAX_LEN = 7;
	public:
	HashMap();


	Value* find(const Key& key) {


	};

	bool erase(const Key& key, const Value& value);

	bool insert(const Key& key) {
		if (find(key)) {
			return false;
		}

		if(buckets_count * MAX_LEN >= items_count) {
			grow();
		}
		size_t idx = hasher(key) % buckets_count;
		buckets[idx] = new Node(key, value, buckets[idx]);

	};

private:
		void grow() {
			size_t  new_buckets_count = BUCKETS_SIZES_LIST[buckets_sizes_list_ind++];
			Node** new_buckets = new Node*[new_buckets_count];
			for (int i = 0; i <buckets_count; ++i) {
				new_buckets[i] = nullptr;
			}
			for (int i = 0; i <buckets_count; ++i) {


				
			}

		};


		Node** buckets;
		size_t buckets_count;

		size_t buckets_sizes_list_ind;
		size_t items_count;

		Hash hasher;
};


// MAIN FUNCT
int main() {
	

    return 0;
}
