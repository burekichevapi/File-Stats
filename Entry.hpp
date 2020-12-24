//
// Created by Amer Delic on 3/30/2020.
//

#ifndef ENTRY_HPP
#define ENTRY_HPP

#include <string>
#include <functional>

class Entry
{
    std::string _data;
    size_t _timesOccurred;
    size_t _firstLocation;

public:
    Entry(std::string data, size_t locatedAt, size_t timesOccurred = 1);

    void occurred();

    const size_t numberOfOccurrences() const;

    const size_t firstLocation() const;

    const std::string getData() const;

    static const bool mostOccurrences(const Entry& e1, const Entry& e2);

    static const bool firstOccurrence(const Entry& e1, const Entry& e2);

    static const bool greatestValue(const Entry& e1, const Entry& e2);

};

#endif
