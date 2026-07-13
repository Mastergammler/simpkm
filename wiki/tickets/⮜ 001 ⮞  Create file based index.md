---
created: 2026-07-13T09:10
finished: 2026-07-13T22:02
---
#state/closed

## Tasks
- [x] Integrate multiple cmd line options
- [x] Read all files from the vault
- [x] Create a index for it
- [x] Add files for autocomplete and trigger `[[`

## Description

The data format should look something like this, this is what [[nvim-cmp]] expects.
This is what i need to return from my c-tool.


```lua
local vault_index = {
    {
        title = "Rust Book",
        path = "notes/rust/book.md",
        aliases = { "rust", "ownership" }
    },
    {
        title = "Lua Guide",
        path = "notes/lua/guide.md",
        aliases = { "lua", "neovim scripting" }
    },
    {
        title = "Neovim API",
        path = "notes/nvim/api.md",
        aliases = { "api", "vim api" }
    },
}
```

*Question is*
Do it like that, or rather 1 entry per alias, end then just have a alias flag?
It seems more sensible to do this, because then it's more a flat list.
Which is easier to create, easier to filter, it's just simpler.
-> Use [[Flat structures]], as much as possible!


```lua
local vault_index = {
    {
        title = "Rust Book",
        path = "notes/rust/book.md",
        alias = false
    },
    {
        title = "rust",
        path = "notes/rust/book.md",
        alias = true
    },
    {
        title = "ownership",
        path = "notes/rust/book.md",
        alias = true
    },
}
```

**File completion**
- for file completion i actually only need the name & the alias
 -> This is sufficient for the completion, because i don't actually need the path for it yet
 => The path i only need for jumping to notes -> this is a link feature

### Open questions
- Adding the extension filter, added 20x the time for ceration (in obsidian vault from 50m -> 1200ms)
 -> Not quite sure why comparing the ending is that expensive, but i need to find a better solution?
 => I mean when i parse all the files, this will be another issue anyway again?
- I'll have to see how to handle this, because maybe this is too long
 -> But for [[on demand]] parsing, the current approach works well

### Optimizations
- I changed the second file name to `"` when it's the same, that way i save around 40% of data in the file
 -> And this makes ofc parsing for [[lua]] easier (even so the performance was about the same)
