---
created: 2026-08-04T10:21
finished: 2026-08-04T11:40
---
#ticket/closed

## Tasks
- [x] Why is the transient fool getting full?
- [x] Fix the issue
- [x] Filter `.dirs` by default!

## Description
It seems, when i have the vault in a root dir with git files, it has some 
issues, dunno if it always happens?

It's even worse, i get inconsistent outputs. Sometimes the index is just empty,
other times it has overwritten strings in it, it crashes on pool allocation, 
and strangely at different places always?

And there is an [[compile mode]] issue, where it swallows the printfs before ..
-> So i need to do it with run

[[Invalid index output example]]

ALSO: it freaking doen't write anything in the index, despite the first files 
beeing debugged to be written???? Maybe this is a file close issue?
But it's strange nevertheless
=> But when i add a `str_printc` afterwards, then it suddenly works?
=> Probably because [[reset pool]] is called afterwards.
=> But this is exactly what leads to the issue with the index beeing 
   overwritten with tmp values, for whatever reason.
   -> Ah, probably because i actually don't keep the file name ...

**Proper pool handling**
I can not use the [[transient pool]] for things that are not expanding, this is 
just creating a mess! Because the transient pool can be reset at any point, 
that's it's purpose. I mean that is the whole reason it is there.

=> I really should just remove the transient pool, because it just leads to 
[[confusing|confusion]] during development!

**Recursion and pool handling*
For [[directory traversal]], we always need [[stack]] behaviour, because we can 
go in and out of directory levels! This means, we just pop the paths safed in 
the string pool, and the continue, instead of [[reset pool|resetting the pool]] 
completely, because then we mess up paths of the parent dirs.



