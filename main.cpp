#include <iostream>
#include <iomanip>
#include <chrono>
#include "File.hpp"
#include "Counter.hpp"

void printTop(Entry_PriorityQ &entries, size_t top, std::string type)
{
    std::cout << std::endl
              << "Top " << top << " " << type << ": " << std::endl;
    std::cout << "RANK" << std::setw(20) << "ENTRY" << std::setw(20) << "TIMES OCCURRED"
              << std::setw(20) << "\tFIRST LOCATION" << std::setw(17) << "ASCII VALUE" << std::endl;

    size_t rank = 1;

    while (rank <= top && !entries.empty())
    {
        if ((int)*entries.top().getData().c_str() < 0)
        {
            entries.pop();
            continue;
        }

        std::cout << rank++ << "." << std::setw(20);

        if (entries.top().getData() == " ")
            std::cout << "space";
        else if (entries.top().getData() == "\n")
            std::cout << "\\n";
        else if (entries.top().getData() == "\t")
            std::cout << "\\t";
        else if (entries.top().getData() == "\r")
            std::cout << "\\r";
        else if (entries.top().getData() == "\f")
            std::cout << "\\f";
        else if (entries.top().getData() == "\v")
            std::cout << "\\v";
        else
            std::cout << entries.top().getData();

        std::cout << std::setw(17) << entries.top().numberOfOccurrences() << std::setw(20)
                  << entries.top().firstLocation() << std::setw(17);

        int ascii = 0;

        for (size_t i = 0; i < entries.top().getData().length(); i++)
            ascii += (int)entries.top().getData()[i];

        std::cout << ascii << std::endl;

        entries.pop();
    }
}

int main()
{
    auto start = std::chrono::high_resolution_clock::now();

    auto testFiles = {"test0", "test1", "test2", "test3", "moby_dick.txt"};

    for (auto &fileName : testFiles)
    {
        auto file = File::openFile(fileName);

        if (!file.canOpen())
        {
            std::cout << "\n\nError opening " << fileName << "\n\n";
            continue;
        }

        auto start = std::chrono::high_resolution_clock::now();

        std::string contents = file.getContent();

        size_t top = 10;
        std::cout << "\n\n****************************** " << fileName << " ******************************";

        std::regex patternChars(R"(.|\s)");
        Counter countChars(contents, patternChars, Entry::greatestValue); //if string O(nlog(n))
        //Counter countChars(file, patternChars, Entry::greatestValue);//if File O(n^2)
        printTop(countChars.getEntries(), top, "characters");

        std::regex patternSpecialChars(R"([^[:alnum:]]|\s)");
        Counter countSpecialChars(contents, patternSpecialChars, Entry::greatestValue); //if string O(nlog(n))
        //Counter countSpecialChars(file, patternSpecialChars, Entry::greatestValue);//if File O(n^2)
        printTop(countSpecialChars.getEntries(), top, "special characters");

        std::regex patternWords(R"([[:alpha:]]+)");
        auto toLowerAllMatches = [](char &c) { return std::tolower(c); };
        Counter countWords(contents, patternWords, Entry::firstOccurrence, toLowerAllMatches); //if string O(nlog(n))
        //Counter countWords(file, patternWords, Entry::firstOccurrence, toLowerAllMatches);//if File O(n^2)
        printTop(countWords.getEntries(), top, "words");

        std::regex patternNumbers(R"(\d+)");
        Counter countNumbers(contents, patternNumbers, Entry::firstOccurrence); //if string O(nlog(n))
        //Counter countNumbers(file, patternNumbers, Entry::firstOccurrence);//if File O(n^2)
        printTop(countNumbers.getEntries(), top, "numbers");

        auto stop = std::chrono::high_resolution_clock::now();
        auto durationMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
        std::cout << "\nTime in Microseconds for " << fileName << ": " << durationMicroseconds.count() << std::endl;

        auto durationSeconds = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
        std::cout << "Time in Seconds for " << fileName << ": " << durationSeconds.count() << std::endl;
    }

    auto stop = std::chrono::high_resolution_clock::now();
    auto durationMicroseconds = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    std::cout << "\n\nTotal time in Microseconds: " << durationMicroseconds.count() << std::endl;

    auto durationSeconds = std::chrono::duration_cast<std::chrono::seconds>(stop - start);
    std::cout << "Total time in Seconds: " << durationSeconds.count() << std::endl;

    return 0;
}
