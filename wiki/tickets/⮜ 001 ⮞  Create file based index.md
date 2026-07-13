---
created: 2026-07-13T09:10
finished: 
---
#state/open

## Tasks
- [ ] Read all files from the vault
- [ ] Integrate multiple cmd line options
- [ ] Create a index for it
- [ ] Add files for autocomplete and trigger `[[`

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


