
- [ ] just query all file-names in the directory (recursively)
- [ ] split the names at space
- [ ] create a entry on the index for each of the sub parts
- [ ] parse all the links to capture uncreated ones as well!

```bash
This is one file.md {First file, one file, the file}

# matching list
this - [0]
is - [0]
one - [0,1]
file - [0]
first - [0]
the - [0]

# actual index
0 this is one file.md - [first file,one file,the file]
1 this is another one.md - [Another one]
2 ...
```

- here i match the prefix against this list and then lookup the file
- then return the file with all it's aliases etc -> yea, because i'm not doing fuzzy finding

### Create Index
**Steps**
- [ ] Get all file names of the dir
- [ ] Create index based on files only
- [ ] Parse frontmatter of files (get aliases & include in index)
- [ ] Parse all files & match add uncreated links
- [ ] Keep the index file up to date somehow (file change times etc?)

### Integration
- [ ] Function to read & filter index file based on prefix (quicksearch|sorted index)
- [ ] Parse to lua table and return it

## After doing the debug symbols
- So maybe a binary file would be great as a fast read/write index etc
 -> Also, it seems sensible to split strings & index information
 => Because traversing the index should be super fast, to keep the data very small there
- But the small caveat is, that in order to be able to do this, the binary file is a bit harder to write
 -> Because [[variable length entries]] (lists to files etc)
