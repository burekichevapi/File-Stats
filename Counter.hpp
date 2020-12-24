//
// Created by Amer Delic on 3/30/2020.
//

#ifndef COUNTER_HPP
#define COUNTER_HPP

#include <string>
#include <regex>
#include <map>
#include "Entry.hpp"
#include "File.hpp"
#include <queue>

using Entry_CompareFunction = std::function<bool (const Entry&, const Entry&)>;

using Entry_PriorityQ = std::priority_queue<Entry, std::vector<Entry>, Entry_CompareFunction>;

class Counter
{
    Entry_PriorityQ _rankedEntries;

    std::map<std::string, Entry> _countMap;

    size_t _position = 0;

    std::function<char(char& c)> _modifyData;

    static char noModification(const char& c) {return c;};

    void countMatches(File& file, const std::regex& pattern);

    void countMatches(const std::string& str, const std::regex& pattern);

    void rankValues(const Entry_CompareFunction& rankBy);

    void countOccurrenceOf(const std::sregex_iterator& match);

public:

    Counter(File& file, const std::regex& pattern, const Entry_CompareFunction& rankBy, std::function<char(char& c)> modification = noModification);

    Counter(const std::string& contents, const std::regex& pattern, const Entry_CompareFunction& rankBy, std::function<char(char& c)> modification = noModification);

    Entry_PriorityQ& getEntries();

};

#endif
