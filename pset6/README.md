# [Problem Set 6: Web Server](http://cdn.cs50.net/2016/x/psets/6/pset6/pset6.html)

### Objectives
- Become familiar with HTTP.
- Apply familiar techniques in unfamiliar contexts.
- Transition from C to web programming.

### Project
Finish the implementation of server.c, a program designed to respond to HTTP requests and serve the requested files located in the /public folder.

### *// TODO*
In server.c:
- Complete the implementation of **lookup**, which returns MIME type for supported extensions, else NULL.
- Complete the implementation of **parse** in such a way that the function parses (i.e., iterates over) line, extracting its absolute-path and query and storing them at abs_path and query, respectively.
- Complete the implementation of load, which loads a file into memory dynamically allocated on heap and stores address of the file in *content and length of the file (in bytes) in *length.
- Complete the implementation of indexes in such a way that the function, given a /path/to/a/directory, returns /path/to/a/directory/index.php if index.php actually exists therein, or /path/to/a/directory/index.html if index.html actually exists therein, or NULL.
