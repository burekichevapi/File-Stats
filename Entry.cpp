//
// Created by Amer Delic on 4/2/2020.
//

#include <algorithm>
#include "Entry.hpp"

Entry::Entry(std::string data, size_t locatedAt, size_t timesOccurred)
{
    _data = data;
    _timesOccurred = timesOccurred;
    _firstLocation = locatedAt;
}

void Entry::occurred() { _timesOccurred++; }

const size_t Entry::numberOfOccurrences() const { return _timesOccurred; }

const size_t Entry::firstLocation() const { return _firstLocation; }

const std::string Entry::getData() const { return _data; }

const bool Entry::mostOccurrences(const Entry& e1, const Entry& e2)
{
    return e1.numberOfOccurrences() < e2.numberOfOccurrences();
}

const bool Entry::firstOccurrence(const Entry& e1, const Entry& e2)
{
    if (e1.numberOfOccurrences() == e2.numberOfOccurrences())
        return e1.firstLocation() > e2.firstLocation();

    return mostOccurrences(e1, e2);
}

const bool Entry::greatestValue(const Entry& e1, const Entry& e2)
{
    if (e1.numberOfOccurrences() == e2.numberOfOccurrences())
        return e1.getData() > e2.getData();

    return mostOccurrences(e1, e2);

}