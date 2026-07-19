---
created: 2026-07-19T21:10
finished: 2026-07-21T17:13
---
#ticket/close

## Tasks
- [x] Read in the index_links file
- [x] Link parsing remove spaces
- [x] Link parsing, when on top of braces
- [x] Problem with line parsing
- [x] Add links to index file
- [x] Add it to the default index, that nvim-cmp has access to it? 
- [ ] ~~Deduplicate entries~~

**Not yet done**
- Automatically grep the entries
- Deduplicate stuff
- Cleaner plugin handlign etc, checking errors for the tasks
- It's too much for [[nivm-cmp]] to handle, so it lags horribly in the main 
  vault -> I need to pre-filter it!

## Description
- Grep to file in incredibly fast 
 -> `grep -RnoP --include=*.md '(?<!`)\[\[.*?\]\]' . > .index_links`
 -> 130k entries in 300ms / 7MB of data

 **Parsing**
 Format is `./Feature funding.md:2:[[funding|fund]]`
 - `[[normal]]`
 - `[[normal|alias]]`
 - `[[normal#heading]]`
 - `[[myfile.excalidraw|800]]` this is an exception, it should NOT be handeled 
     as an index
 - Exclude links within `...` sections

 **Current case**
 - Approach: Testing for 1 or 2 matches etc
 ```bash
 [[ ... ]] # no problems
     ^
 [[ ... ]] # ] = 0
 ^    
 [[ ... ]] # ] = 0
        ^ # [ = 0
 ```
 => *This is a wrong approach, it's way too complicated
     I'm constantly fighting what I want to do, and it 
     really should not be that complicated!*

**Idea**
Just match start & end pos.
The rest does the other
```bash
[[ ... ]] # nStart = 0 nEnd = 0
    ^    
[[ ... ]] # nStart = 0 nEnd = 1
       ^    
# problem case
[[ ... ]] # nStart = 1, i+1 != START!!!
^
```
- n == 1 -> sets the start/end pos!
 -> DOESN'T WORK, because first hit, might not be last hit!!!!
 => Therefore we need to do it on `n == 2`
- Valid link rules:
 1. exactly `2x[ && 2x]` 
  -> Edge case `[ something [my link]]`
  => Ignore for now (could check via setting a premature value at nStart == 1
 2. `sPos <= ePos`
