---
created: 2026-07-19T21:10
finished: 
---
#ticket/open

## Tasks
- [ ] Grep all tags, and put them in some kind of index
- [ ] Feed them (all for the start) to [[nivm-cmp]]
- [ ] Trigger on different match `#\w`

## Description
=> [[vault tag index]]

*Grepping tags*
`grep -RnoP --include="*.md "#[^#^\s^\[^\]]{1,}"`
-> Can I invert the pattern inside the []?
=> It also still matches the heading links inside the link
-> Also probably good to exclude things inside of `these` blocks, if possible
