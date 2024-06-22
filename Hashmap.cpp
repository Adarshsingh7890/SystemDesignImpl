#include <iostream>
#include <vector>
#include <list>
#include <utility>
#include <functional> // hash

using namespace std;

// <typwName, Key>

template<typename K, typename V>
class HashMap{
    private :
        static const int default_size = 10;
        int curr_size;
        vector<list<pair<K,V>>>table;

        int hashFunction(const K & key)const {
            return hash<K>{}(key) % table.size();
        }
    
    public:
        HashMap(int size = default_size): table(size), curr_size(0){};

        void insert(const K & key, const V &value){
            int index = hashFunction(key);
            auto & chain = table[index];

            for (auto &pair: chain){
                if (pair.first == key){
                    pair.second = value;
                    return;
                }
            }

            chain.emplace_back(key,value);
            ++curr_size;
        }

        bool erase(const K &key){
            int index = hashFunction(key);
            auto &chain = table[index];

            for (auto it = chain.begin(); it!=chain.end(); it++){
                if (it->first == key){
                    chain.erase(it);
                    curr_size--;
                    return true;
                }
            }

            return false;
        }

        V *find(const K &key){
            int index = hashFunction(key);
            auto &chain = table[index];

            for(auto &pair: chain){
                if(pair.first == key){
                    return &pair.second;
                }
            }

            return nullptr;
        }

        void modify(const K&key, const V&newvalue){
            V * value = find(key);

            if (value){
                *value = newvalue;
            }else{
                cout << "The Key deosnot exists inside the Map" << endl;
            }
        }

        void display() const {
            for (int i = 0; i < table.size(); i++){
                cout << "Bucket" << i << " " << endl;
                for(auto &pair: table[i]){
                    cout << "[" << pair.first << ":" << pair.second << "]" ;
                }
                cout << endl;
            }
        }
};

int main(){
    
    HashMap<string, int> hashmap;

    hashmap.insert("Alice", 30);
    hashmap.insert("Bob", 25);  // Assume "Bob" hashes to the same index as "Alice"
    hashmap.insert("Charlie", 35);

    hashmap.display();

    int* age = hashmap.find("Alice");
    if (age) {
        std::cout << "Alice's age: " << *age << std::endl;
    }

    hashmap.modify("Alice", 31);
    age = hashmap.find("Alice");
    if (age) {
        std::cout << "Alice's new age: " << *age << std::endl;
    }

    hashmap.erase("Bob");
    hashmap.display();

    return 0;
}