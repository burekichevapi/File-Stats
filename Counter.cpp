//
// Created by Amer Delic on 3/30/2020.
//

#include "Counter.hpp"

using Entry_CompareFunction = std::function<bool (const Entry&, const Entry&)>;

using Entry_PriorityQ = std::priority_queue<Entry, std::vector<Entry>, Entry_CompareFunction>;

Counter::Counter(File& file, const std::regex& pattern, const Entry_CompareFunction& rankBy, std::function<char(char& c)> modification)
{
    _modifyData = modification;

    countMatches(file, pattern);

    rankValues(rankBy);
}

Counter::Counter(const std::string& contents, const std::regex& pattern, const Entry_CompareFunction& rankBy, std::function<char(char& c)> modification)
{
    _modifyData = modification;

    countMatches(contents, pattern);

    rankValues(rankBy);
}

void Counter::countMatches(File& file, const std::regex& pattern)
{
    std::string line;
    auto stream = file.getStream();

    while(std::getline(*stream, line))
    {
        stream->seekg(-1, std::ios::cur);
        line += stream->get();

        countMatches(line, pattern);
        _position += line.size();
    }
}

void Counter::countMatches(const std::string& str, const std::regex& pattern)
{
    auto match = std::sregex_iterator(str.begin(), str.end(), pattern);

    while(match != std::sregex_iterator())
    {
        countOccurrenceOf(match);
        match++;
    }
}

void Counter::countOccurrenceOf(const std::sregex_iterator& match)
{
    std::string data = match->str();

    std::transform(data.begin(), data.end(), data.begin(), _modifyData);

    bool isNewEntry = !_countMap.count(data);

    if(isNewEntry)
    {
        size_t initialPosition = _position + match->position();

        Entry e(data, initialPosition);

        _countMap.emplace(std::make_pair(data, e));
    }
    else
        _countMap.at(data).occurred();
}

void Counter::rankValues(const Entry_CompareFunction& rankBy)
{
    Entry_PriorityQ q(rankBy);

    for(const auto & pair: _countMap)
        q.emplace(pair.second);

    _rankedEntries = q;
}

Entry_PriorityQ& Counter::getEntries()
{
    return _rankedEntries;
}
