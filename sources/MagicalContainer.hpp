#ifndef MAGICALCONTAINER_HPP
#define MAGICALCONTAINER_HPP

#include <stdexcept>
#include <vector>
using namespace std;
namespace ariel
{

    class MagicalContainer
    {
    private:
        std::vector<int> elements;
        std::vector<int*> primesIndices;  // Pointers to prime numbers in 'elements'  
    public:
        MagicalContainer();
        void addElement(int element);
        void removeElement(int element);
        size_t size() const;
        int operator[](size_t index) const;
        vector<int> getElements() const;
        bool isPrime(int num) const;

        class AscendingIterator
        {
        private:
            const MagicalContainer &container;
            size_t position;

        public:
            AscendingIterator(const MagicalContainer &container);
            AscendingIterator(const AscendingIterator &other);
            ~AscendingIterator();

            AscendingIterator &operator=(AscendingIterator &&other) noexcept;
            AscendingIterator(AscendingIterator &&other) noexcept;

            AscendingIterator &operator=(const AscendingIterator &other);
            bool operator==(const AscendingIterator &other) const;
            bool operator!=(const AscendingIterator &other) const;
            bool operator>(const AscendingIterator &other) const;
            bool operator<(const AscendingIterator &other) const;
            int operator*() const;
            AscendingIterator &operator++();

            AscendingIterator begin();
            AscendingIterator end();
        };

        class PrimeIterator
        {
        private:
                
            const MagicalContainer &container;
            size_t position;

        public:
            PrimeIterator(const MagicalContainer &container);
            PrimeIterator(const PrimeIterator &other);
            ~PrimeIterator();

            PrimeIterator &operator=(const PrimeIterator &other);
            bool operator==(const PrimeIterator &other) const;
            bool operator!=(const PrimeIterator &other) const;
            bool operator>(const PrimeIterator &other) const;
            bool operator<(const PrimeIterator &other) const;
            int operator*() const;
            PrimeIterator &operator++();

            PrimeIterator begin();
            PrimeIterator end();

        };

        class SideCrossIterator
        {
        private:
            MagicalContainer &container;
            size_t position;

        public:
            SideCrossIterator();
            ~SideCrossIterator();
            SideCrossIterator(MagicalContainer &container, size_t pos);
            SideCrossIterator(MagicalContainer &);

            //SideCrossIterator operator&(SideCrossIterator &&) = delete;

            SideCrossIterator &operator=(const SideCrossIterator &other);
            bool operator==(const SideCrossIterator &other) const;
            bool operator!=(const SideCrossIterator &other) const;
            bool operator<(const SideCrossIterator &other) const;
            bool operator>(const SideCrossIterator &other) const;
            SideCrossIterator &operator++();
            int operator*() const;

            SideCrossIterator begin();
            SideCrossIterator end();
        };
    };
}

#endif // MAGICALCONTAINER_HPP
