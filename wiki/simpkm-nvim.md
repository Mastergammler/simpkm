# Simple PKM [[nvim]] plugin

```lua
{
    target = "File",
    label = "My file",
    source = "my file.md"
}

Link = {
    target = "Name",
    label = "Alias"
}

Note = {
    path = "notes/myfile etc.md",
    title = "Myfile etc"
}
```

## Layout suggestion

```bash
lua/wiki/

  init.lua              -- entry point

  config.lua            -- vault path, settings

  core/
    files.lua           -- scan/create/open notes
    links.lua           -- parse [[link|alias]]
    resolve.lua         -- resolve name → file
    backlinks.lua       -- reverse index (grep-based initially)

  ui/
    jump.lua            -- gf / follow link
    rename.lua          -- rename + refactor links
    render.lua          -- optional visual decoration layer

  completion/
    wiki.lua            -- [[link]] completion source

  index/
    cache.lua           -- optional later optimization
```

## Building steps

1. Jump to wiki links with gf
2. Auto create missing notes
3. Completion source for [[..]]
4. Backlinks
5. Makrdown rendering enhancements
6. (Opt) Inline images

