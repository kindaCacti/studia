# WORD COUNTER
## What is it?
This app works as a word counter. You can add words and remove them, and the app counts occurrences of each word.
## How does it work?
To run the code please use `cmake`\
\
\
I build two classes, one named Counter and one named Entry. You can add words in O(n) time by doing

```
std::vector<std::string> words = {"ala", "ma", "kota", "kota"};
Counter c;
for(std::string word : words){
    c += word;
}
```
Then the counter will have three words "ala", "ma", "kota", but the last word will have 2 occurrences.\
We can also take in words directly from `istream`, like:
```
Counter c;
ifstream file("words.txt");
while(file>>c);
```
You can also remove words in O(n) time like:
```
std::vector<std::string> words = {"ala", "ma", "kota", "kota"};
Counter c;
for(std::string word : words){
    c += word;
}
std::string wordToRemove = "ala";
c -= wordToRemove;
```
In the counter there are also implemented two different iterators named: `iterator` and `fiterator`.
First one goes through the words in alphabetical order. So if we have words as given earlier, then our iterator will go through them like: `ala, kota, ma`. This iterator has `++` operator, which works in O(1) time. You can use it like:
```
auto it = c.begin();
while(it != c.end()){
    cout<<(*it);
    it++;
}
```
The counter also has `fiterator` which works by going through our words in increasing order looking at word occurrences, and if the occurrences are the same, then alphabetically. This iterator works in O(n) time. You can use it like:
```
auto it = c.fbegin();
while(it != c.fend()){
    cout<<(*it);
    it++;
}
```

## Times:
Reading moby_dick.txt took: `2500ms`\
Writing to file using fiterator took: `9373ms`\
Writing to file using iterator took: `8ms`