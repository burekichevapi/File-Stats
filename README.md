# File-Stats
C++ program that counts the number of words, characters that are not included already in words, special characters, and numbers in a string or file.

**Analysis if Counter constructor with file is used**
The real workhorse of my version is the countMatches method.
This method takes in a customized File object and a regex pattern.
It loops through the file via the std library method getLine and
delimiterizes the file by '\n' and '\0'. Since we need to include
the '\n' in our final count, we used the istream seekg method to
offset the current position of our pointer by -1; then added this 
char to the end of our line. This works great since getLine also
finds the null termination character '\0' and will add it instead 
of '\n', if '\n' is not the delim character. This loop also keeps
track of the _position Counter attribute.

We then call the overloaded countMatches method from the CountMatches loop.
This method takes in a string from CountMatches loop and the regex pattern.
It iterates through all the matches and calls countOccurrenceOf with
each match passed in.


countOccurrenceOf converts each match to whatever the modification
function was passed in. Unless it was the default modification function
which does nothing. Then proceeds to either add the match to
the count map as a new entry object or increments the _timesOccured property
of that Entry object. Through the occured() method. The position of
each Entry is kept track of by the _position attribute.

After all Entries are accounted for, we then call the rankValues
method and pass a custom type called EntryCompareFunction which
is a static function, functor, of the Entry Object. The Priorty
Queue then inserts each Entry object from the count map via
foreach loop. This allows us to dynamically and automatically
sort our Entry objects by the defined functor.

countMatches: O(n) where n is the file size.
countMatches: O(n) where n is the line size.
countOccurrenceOf: O(n) where n is the matched string size that need to be converted to lower case.
rankValues: O(nlog(n)) where n is the size of the count map and log(n) is the insertion

Time Complexity: O(n^2)
Space Complexity: O(n)

----------------------------------------------------------------------------------------------------

**Analysis if Counter constructor with string is used**
Same as above applies, execpt one BIG difference. In this scenerio we
are reading the file into memory first and passing the contents
as a string into the Counter constructor. By doing thing, we are skipping
the call to the file version of countMatches and going directly
to to the string version of countMatches.

The disadvantage here is that the std::string type can hold
up to 4294967291 characters and it will take more memory to 
hold the file in memory. The advantage is reading the file
in first, reduces run time to nlog(n).

countMatches: O(n) where n is the file size.
countOccurrenceOf: O(n) where n is the matched string size that need to be converted to lower case.
rankValues: O(nlog(n)) where n is the size of the count map and log(n) is the insertion

Time Complexity: O(nlog(n))
Space Complexity: O(n)
