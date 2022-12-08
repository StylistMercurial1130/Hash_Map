#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <string>

#define HASH_MAP_SIZE 1024

namespace Utility {

    template<typename type>
    unsigned long Hash(type value);

    template<>
    unsigned long Hash<int>(int value) {

        unsigned long hash = value;
        hash ^= (hash << 13);
        hash ^= (hash >> 17);        
        hash ^= (hash << 5);
        return hash;

    } 

    template<>
    unsigned long Hash<std::string>(std::string value) {

        unsigned long hash = 5381;
        for(auto i : value)
            hash = ((hash << 5) + hash) + i;
        return hash;

    }

}

template<typename key_type,typename value_type>
class HashMap {
private:
    std::vector<std::pair<key_type,value_type>> mBuffer;
public:

    HashMap() : mBuffer(std::vector<std::pair<key_type,value_type>>(HASH_MAP_SIZE)) { }

    void Insert(key_type key,value_type value) {
        mBuffer[Utility::Hash<key_type>(key) % HASH_MAP_SIZE] = {key,value};
    }

    value_type Get(key_type key) {
        return mBuffer[Utility::Hash<key_type>(key) % HASH_MAP_SIZE].second;
    }

};

int main(int argc,char **argv) {
    HashMap<std::string,int> hshmap;
    /*nice !*/
    hshmap.Insert("Karthik",6);
    hshmap.Insert("Venkatesh",9);
    std::cout << hshmap.Get("Karthik") << hshmap.Get("Venkatesh") << std::endl;
    return 0;
}