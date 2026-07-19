[[deduplication]]

This is pretty pretty easy I just need to have the right sequence


1. Get the file names
2. Grep all files
3. Merge them into the index
4. Sort the Index
5. Deduplicate keeping the last entry (the file exists one)


**Updating the index**
1. Add new files at the end
2. Sort
3. Deduplicate keeping last entry (awk?)
4. Sort again (it should be sorted already no?)

```bash
git status -z | 
awk -b -F '\0' 'BEGIN {RS="\0"} {print substr($0, 4)}'|
tr '\n' '\0' | 
xargs -0 rg -noP --no-heading '(?!\s)\[\[.*?\]\]'
```



