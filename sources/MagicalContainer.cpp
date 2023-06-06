#include "MagicalContainer.hpp"

using namespace ariel;
using namespace std;

MagicalContainer::MagicalContainer()
{
}

void MagicalContainer::addElement(int element)
{
    auto it = lower_bound(elements.begin(), elements.end(), element);
    elements.insert(it, element);

    primesIndices.clear();
    for (size_t i = 0; i < elements.size(); ++i)
    {
        if (isPrime(elements[i]))
        {
            primesIndices.push_back(&elements[i]);
        }
    }
}

void MagicalContainer::removeElement(int element)
{
    auto it = lower_bound(elements.begin(), elements.end(), element);
    if (it != elements.end() && *it == element)
    {
        elements.erase(it);
    }
    else
    {
        throw std::runtime_error("Element not found in the container");
    }

    // Rebuild the primesIndixes vector after erasing an element
    primesIndices.clear();
    for (size_t i = 0; i < elements.size(); ++i)
    {
        if (isPrime(elements[i]))
        {
            primesIndices.push_back(&elements[i]);
        }
    }
}

size_t MagicalContainer::size() const
{
    return elements.size();
}

int MagicalContainer::operator[](size_t index) const
{
    if (index >= elements.size())
    {
        throw std::out_of_range("Index out of range");
    }
    return elements[index];
}

vector<int> MagicalContainer::getElements() const
{
    return elements;
}

bool MagicalContainer::isPrime(int num) const
{
    if (num <= 1)
        return false;
    if (num == 2)
        return true;
    if (num % 2 == 0)
        return false;
    for (int i = 3; i * i <= num; i += 2)
    {
        if (num % i == 0)
            return false;
    }
    return true;
}

////////////////////////////////////////////////////////////AscendingIterator///////////////////////////////////////////////////////////

MagicalContainer::AscendingIterator::AscendingIterator(const MagicalContainer &container)
    : container(container), position(0)
{
}

// Copy Constructor
MagicalContainer::AscendingIterator::AscendingIterator(const AscendingIterator &other)
    : container(other.container), position(other.position)
{
}

// MagicalContainer::AscendingIterator::AscendingIterator(AscendingIterator &&other) noexcept
//     : container(std::move(other.container)), position(other.position)
// {
// }


// MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(AscendingIterator &&other) noexcept
// {
//     if (this != &other)
//     {
//         container = std::move(other.container);
//         position = other.position;
//     }
//     return *this;
// }
// Destructor
MagicalContainer::AscendingIterator::~AscendingIterator()
{
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator=(const AscendingIterator &other)
{
    if (&container != &other.container)
    {
        throw std::runtime_error("Iterators are pointing to different containers");
    }
    if (this != &other)
    {
        this->position = other.position;
    }
    return *this;
}

bool MagicalContainer::AscendingIterator::operator==(const AscendingIterator &other) const
{
    return (position == other.position) && (&container == &other.container);
}

bool MagicalContainer::AscendingIterator::operator>(const AscendingIterator &other) const
{
    if (position >= container.size() || other.position >= container.size())
    {
        return false; // Comparing beyond the end of the container, return false
    }
    return position > other.position;
}

bool MagicalContainer::AscendingIterator::operator<(const AscendingIterator &other) const
{
    if (position >= container.size() || other.position >= container.size())
    {
        return false; // Comparing beyond the end of the container, return false
    }
    return position < other.position;
}

bool MagicalContainer::AscendingIterator::operator!=(const AscendingIterator &other) const
{
    return position != other.position;
}

int MagicalContainer::AscendingIterator::operator*() const
{
    if (position >= container.size())
    {
        throw std::out_of_range("Iterator out of range");
    }
    return container[position];
}

MagicalContainer::AscendingIterator &MagicalContainer::AscendingIterator::operator++()
{
    if (position >= container.size())
    {
        throw std::runtime_error("Iterator increment beyond end");
    }
    position++;
    return *this;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::begin()
{
    AscendingIterator iter(container);
    iter.position = 0; // Assuming that position 0 always points to the smallest element.
    return iter;
}

MagicalContainer::AscendingIterator MagicalContainer::AscendingIterator::end()
{
    AscendingIterator iter(container);
    iter.position = container.size(); // One past the largest element.
    return iter;
}

//////////////////////////////////////////////////////PrimeIterator////////////////////////////////////////////////////////////////////
// PrimeIterator
MagicalContainer::PrimeIterator::PrimeIterator(const MagicalContainer &container)
    : container(container), position(0)
{
}

MagicalContainer::PrimeIterator::PrimeIterator(const PrimeIterator &other)
    : container(other.container), position(other.position)
{
}

MagicalContainer::PrimeIterator::~PrimeIterator() {}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator=(const PrimeIterator &other)
{
    if (&container != &other.container)
    {
        throw std::runtime_error("Iterators are pointing to different containers");
    }
    if (this != &other)
    {
        this->position = other.position;
    }
    return *this;
}

bool MagicalContainer::PrimeIterator::operator==(const PrimeIterator &other) const
{
    return (position == other.position) && (&container == &other.container);
}

bool MagicalContainer::PrimeIterator::operator!=(const PrimeIterator &other) const
{
    return !(*this == other);
}

bool MagicalContainer::PrimeIterator::operator>(const PrimeIterator &other) const
{
    return position > other.position;
}

bool MagicalContainer::PrimeIterator::operator<(const PrimeIterator &other) const
{
    return position < other.position;
}

int MagicalContainer::PrimeIterator::operator*() const
{
    if (position >= container.primesIndices.size())
    {
        throw std::out_of_range("Iterator out of range");
    }
    return *container.primesIndices[position];
}

MagicalContainer::PrimeIterator &MagicalContainer::PrimeIterator::operator++()
{
    if (position >= container.primesIndices.size())
    {
        throw std::runtime_error("Iterator increment beyond end");
    }
    position++;
    return *this;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::begin()
{
    PrimeIterator iter(container);
    iter.position = 0; // Assuming that position 0 always points to the first element.
    return iter;
}

MagicalContainer::PrimeIterator MagicalContainer::PrimeIterator::end()
{
    PrimeIterator iter(container);
    iter.position = container.primesIndices.size(); // One past the last element.
    return iter;
}

////////////////////////////////////////////////SideCrossIterator////////////////////////////////////////////////////////////////////////////////

MagicalContainer::SideCrossIterator::~SideCrossIterator()
{
}
//was built in this way for the sidecross to iterate from the begining and the end and to satisfy the O(1). 
MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& magicalContainer, size_t pos)
    : container(magicalContainer), position(pos)
{
}

MagicalContainer::SideCrossIterator::SideCrossIterator(MagicalContainer& magicalContainer)
    : container(magicalContainer), position(0)
{
}

int MagicalContainer::SideCrossIterator::operator*() const
{
    size_t index;
    if (position % 2 == 0)
    {
        index = position / 2;
    }
    else
    {
        index = container.size() - 1 - ((position - 1) / 2);
    }
    return container[index];
}


MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator=(const SideCrossIterator& other)
{
    if (&container != &other.container)
    {
        throw std::runtime_error("comparing different containers");
    }
    if (this != &other)
    {
        position = other.position;
    }
    return *this;
}
    
bool MagicalContainer::SideCrossIterator::operator!=(const SideCrossIterator& other) const
{
    return !(*this == other);
}

bool MagicalContainer::SideCrossIterator::operator==(const SideCrossIterator& other) const
{
    return &container == &other.container && position == other.position;
}

bool MagicalContainer::SideCrossIterator::operator>(const SideCrossIterator& other) const
{
    return position > other.position;
}

MagicalContainer::SideCrossIterator& MagicalContainer::SideCrossIterator::operator++()
{
    if (*this == end() || position >= container.size())
    {
        throw runtime_error("Out of bounds!");
    }
    position++;
    return *this;
}

bool MagicalContainer::SideCrossIterator::operator<(const SideCrossIterator& other) const
{
    return position < other.position;
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::begin()
{
    return SideCrossIterator(container, 0);
}

MagicalContainer::SideCrossIterator MagicalContainer::SideCrossIterator::end()
{
    return SideCrossIterator(container, container.size());
}