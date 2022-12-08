#include <iostream>
#include <string>
#include <limits>
using namespace std;

static constexpr size_t BUCKETS_SIZES_LIST[] = {
    7, 17, 37, 73, 149, 251, 509, 1021, 2027, 5003, 10837
};

static constexpr size_t START_HASH_CAPACITY = 8;

size_t MAXHASH = std::numeric_limits<size_t>::max();

size_t str_hash(const std::string& data, size_t m) {
	size_t hash = 0;
	for(char i : data)
		hash = (hash * 13 + i) % m;
	return hash;
}

class SimpleHashTable {
    public:
        SimpleHashTable(): elementsNumber(0), bufferSize(START_HASH_CAPACITY), buckets_sizes_list_idx(0) {
            this->buff = new string[START_HASH_CAPACITY];
            for(int i = 0; i < START_HASH_CAPACITY; ++i) {
                buff[i] = "NIL";
            }
        }

        ~SimpleHashTable() {
            delete[] this->buff;
        }

        bool isEmpty() {
            if (this->elementsNumber == 0) {
                return true;
            }
            return false;
        }
        
        bool checkString(string sample) {
            size_t sampleHash = str_hash(sample, bufferSize);
            for(size_t i = 0; i <= 3 * bufferSize; ++i) {
                sampleHash = ((sampleHash + i) % bufferSize);
                if(buff[sampleHash] == sample) {
                    return true;
                }
                if(buff[sampleHash] == "NIL") {
                    return false;
                }
                if(buff[sampleHash] == "DEL") {
                    continue;
                }
            }
            return false;
        }


        bool addString(const string &sample) {
            size_t sampleHash = str_hash(sample, bufferSize);
            for(size_t i = 0; i <= 3 * bufferSize; ++i) {
                sampleHash = ((sampleHash + i) % bufferSize);
                if(buff[sampleHash] == sample) {
                    return false;
                }
                if((buff[sampleHash] == "NIL") || (buff[sampleHash] == "DEL")) {
                    buff[sampleHash] = sample;
                    elementsNumber++;
                    if(((elementsNumber*4)/bufferSize) >= (3)) { // проверка на заполнение на 3/4
                        this->grow();
                    }
                    return true;
                }
            }
            return false;
        }

        bool delString(string sample) {
            size_t sampleHash = str_hash(sample, bufferSize);
                for(size_t i = 0; i <= 3 * bufferSize; ++i) {
                sampleHash = ((sampleHash + i) % bufferSize);
                if(buff[sampleHash] == sample) {
                    buff[sampleHash] = "DEL";
                    elementsNumber--;
                    return true;
                }
                if(buff[sampleHash] == "NIL") {
                    return false;
                }
                if(buff[sampleHash] == "DEL") {
                    continue;
                }
            }
            return false;
        }

        string getString(size_t idx) {
            if(this->isEmpty()) {
                return "empty";
            }
            if(idx >= elementsNumber) {
                return "  out of range!  ";
            }
            return this->buff[idx];
        }

        size_t getCapacity() {
            return this->bufferSize;
        }

        size_t getSize() {
            return this->elementsNumber;
        }

        void getBuffer() {
            cout << endl;
            for(size_t i = 0; i < bufferSize; ++i) {
                cout << buff[i] << " ";
            }
            cout << endl;
        }

    private:
        void grow() {
            size_t newBufferSize = BUCKETS_SIZES_LIST[++buckets_sizes_list_idx];
            string *tempBuff = new string[newBufferSize];
            for(int i = 0; i < newBufferSize; ++i) {
                tempBuff[i] = "NIL";
            }
            size_t sampleHash = 0;
            for(size_t i = 0; i < bufferSize; ++i) {
                sampleHash = str_hash(this->buff[i], newBufferSize);
                tempBuff[sampleHash] = this->buff[i];
            }
            delete[] this->buff;
            this->buff = tempBuff;
            this->bufferSize = newBufferSize;
        }

        string *buff;
        size_t elementsNumber;
        size_t bufferSize;
        size_t buckets_sizes_list_idx;
};

// MAIN FUNCT
int main() {
    SimpleHashTable hash;
    std::string key;
    char operation;
    while(std::cin >> operation >> key) {
        bool result = false;
        switch (operation) {
            case '+':
                result = hash.addString(key);
                break;
            case '-':
                result = hash.delString(key);
                break;
            case '?':
                result = (hash.checkString(key));
                break;
            /*case '#':
                result = true;
                hash.getBuffer();
                cout << "cap: " << hash.getCapacity() << " size:" <<
                hash.getSize() << endl;
                break;*/
            default:
                //return 0;
                break;
        }
        if (result) {
            std::cout << "OK" << std::endl;
        } else {
            std::cout << "FAIL" << std::endl;
        }
    }

   return 0;
}
