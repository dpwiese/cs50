0. Pneumonoultramicroscopicsilicovolcanoconiosis is a type of lung disease, and longest word in the Oxford English dictionary.

1. `getrusage` returns a structure containing usage data for a particular process, including how much CPU time was used and more.

2. An `rusage` struct has 16 members.

3. Before and after are passed by reference so as to avoid making duplicate copies of these structures as would be required when passing by value, thus saving time and memory.

4. `main` first looks to see if the user passed in a specific dictionary file, otherwise it will use the default one.
Next it loads the dictionary file to memory using our load function.
Then it opens the text file, and using `fgetc` there is a for loop which gets one character at a time until the end-of-file EOF is found.
If the character is a letter or apostrophe, it stores this as part of the word, otherwise any other character starts that the word has ended.
It then skips over any numbers, looking for the beginning of the next word and starts the process over at the beginning of the loop.

5. `fgetc` is helpful because it gets characters one at a time.

6.  Check and load do not need to be modifiable, so by declaring them as constants when someone else reads the code it is more clear what the intentions are for these variables

7.  I used trie. Each node has a boolean `is_word`, and 27 pointers to other nodes.
Starting from the root node, each pointer is initialized to null, indicating there are no words in the trie, and `is_word` is false, indicating there are no words.
Then as words are added, pointers are connected to new nodes with each character of the word, and at the end of the word is_word is set to true.

8. So far it is pretty fast, but I haven't finished unload yet and probably won't in the minutes I have left before submission.

9. I first need to get unload working, then I will check through to find any places I am doing extra operations.

10. My code surely has bottlenecks, but before I really search for these I would have to finish unload.
