#include <iostream>
#include <vector>
#include <cmath>

class PrimeIterator {
private:
    std::vector<int> primes;
    size_t index;
    int limit;
    
public:
    // Вложенный класс итератора
    class Iterator {
    private:
        const std::vector<int>* data;
        size_t pos;
        
    public:
        Iterator(const std::vector<int>* d = nullptr, size_t p = 0) : data(d), pos(p) {}
        
        // Операторы для input iterator
        bool operator!=(const Iterator& other) const {
            return pos != other.pos;
        }
        
        int operator*() const {
            return (*data)[pos];
        }
        
        Iterator& operator++() {
            pos++;
            return *this;
        }
    };
    
    // Конструктор
    PrimeIterator(int lim) : limit(lim), index(0) {
        // Решето Эратосфена
        if (limit < 2) return;
        
        std::vector<bool> is_prime(limit + 1, true);
        is_prime[0] = is_prime[1] = false;
        
        for (int i = 2; i <= std::sqrt(limit); ++i) {
            if (is_prime[i]) {
                for (int j = i * i; j <= limit; j += i) {
                    is_prime[j] = false;
                }
            }
        }
        
        for (int i = 2; i <= limit; ++i) {
            if (is_prime[i]) {
                primes.push_back(i);
            }
        }
    }
    
    // begin() и end() для range-based for
    Iterator begin() const {
        return Iterator(&primes, 0);
    }
    
    Iterator end() const {
        return Iterator(&primes, primes.size());
    }
};