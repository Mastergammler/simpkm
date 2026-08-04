---
created: 2026-07-21T17:29
finished: 2026-08-04T10:21
---
#ticket/close

## Tasks
- [x] Integrate index creation into the functions
- [x] Deduplicate Files on the index
- [~] ~~Run async? (only create files at first)~~ -> the index task is very 
- [~] ~Filter matched files (it's too much for [[nvim-cmp]]~
- [x] Dedup alias to the link directly

## Description
The basic functionality works, the problem is just, in the main vault, 
it's too much to handle. Searching lags now, because the hughe amount of data
(130k links etc).

The problem is, to properly filter all of it, i need to actually create the 
fuzzy finding logic myself. Else i will only match on the first latter matches,
which is [[not sufficent]] for actually finding other notes that just use 
the words somewhere internally.

So this might be a bit of a bigger project, and i need to see how i can do it.

On thing i can try at first, is ofc the [[index header]]. So just type in the-
file ranges for like 2 letter matches and then only load one section of the 
file. Ofc, the drawback is, then i need to load that file section every time,
dunno how fast this is, or if that even makes sense? But yea, just try it,
something like this i need anyway for alot of other things also.

**On second thought**
I experimented a bit with [[deduplication]] and sorting for the index, and 
this is already sufficent. I could cut down the notes to 70K, which is already 
almost smooth. And i still have duplicates with different paths, (so one from 
the alias index and one from the file one) so this might be cut in half even 
once more. And with that size i don't need to implement all the pre filtering
etc for now. I just need to implement the filtering of the rest, and i'll be 
fine. This is good news!

**Async running**
This doesn't work, because of [[task dependencies]].
All tasks except reading the files depend on each other, while the index file 
task is running very quickly (24ms) so it's neglectable.
*Grep (50%) + Alias (18%) + Dedup(12%)* is what uses 80% of the time. 
Refresh takes another 100ms (15%), but also depends on everything else beeing
finished.

### [[Deduplicating the index]]


*Index write in same buffer*
I had this issue where the data in the index file suddenly was corrupted.
It looked like i wrote some of the expansions into it (-> I should really fix 
the expansion behaviour ot some point, it makes handling pool handling more 
[[complex]] and [[confusing]] ...)

[[⮜ 011 ⮞  Root dir writing issue]] -> it still exists

