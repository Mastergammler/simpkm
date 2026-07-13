#vim #nvim

[[nvim_basics]]

**Vim basics**
- `gf` - goto file

> Drawback: file needs to exist
> It doesn't support spaces etc -> not obsidian compatible!
> => Then using statement notes woludn't work

*BUT:* 
- This might be a good approach for a minimal setup on a server etc
-> Because i don't need to install anything

==Hello world==

- `ctrl + o/i` - go backward / forward
> In nvim i mapped this to ctrl + k/l

*Searching tags etc*
`:vim /#mytag/ *.*` - then `:copen` -> Shows all the tags
`:cnext/cprex` - move between the entries (default shortcut ]q, [q) ([q]uickfix)
-> ]Q [Q last/first entry


