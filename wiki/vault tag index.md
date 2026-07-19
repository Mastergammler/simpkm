# [[tag]] [[index]]

## Tasks

## Basic approach

The tag index should be done something like this

There is an [[index header]] which declares where in the file the corresponding entries start.
So the consumer of the file, can just read that section, for the lines actually needed.
The header tries to keep the found count as small as possible, for efficient lookup.

```bash
#a line 70:101
#b line 102:122
#..
#z line 3590:3617
```
- This could be done super efficiently in binary format, just an array of INT, and index into via ascii offset.
 -> That way i know the starting point for each letter, and have a small load & search window
 => Maybe add a start and end?
 - The splits will be created like this:
 -> That way the collection is kept small (if necessary, for tags it's probably fine without it)
 => And then the lookup can skip multiple files already during search
```bash
#aa 60 matches
#ab 75 matches
#ac 30 matches
#a? 23 matches
#b 12 matches
#c 17 matches
```
- It will be split up based on starting letters per tag
 -> And the index will manage the file, so that only ever 100 entries exist per double letter
 => If it get's bigger, it will split for another letter match 
 > Although, this then wouldn't work as well for querying anymore
 > Because then, 


