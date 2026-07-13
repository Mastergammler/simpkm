# Markdown PKM MOC

#tags/also
#pkm

[[simpkm]]
[[creating a markdown index]]

### Basic Features
- [x] basic text coloring
- [ ] link / files lsp
    - [x] files with spaces in them
    - [x] links without the file ending
    - [ ] file and alias completion
- [x] toggle todo completion
- [x] Adding vault options for base path (project wikis)
- [x] Insert templates
- [ ] cmp for tags
- [ ] Basic command features (daily note ?)

**Follow Links**
- [ ] Trim spaces
- [ ] Case sensitivity handling
- [ ] Search subfolder for filename also (cuz obsidian does this)

**Functions needed**
- [x] Cycle Todo
- [x] Goto-file
- [x] Insert template
- [x] Open daily note (+ template)
- [ ] Create new note -> just `ene`?
- [ ] Open Daily/Weekly notes -> create all that are needed

### Secondary features
- [ ] Page structure
    - [ ] Line limit & note length limit
    - [ ] Switch between flash card & page
- [ ] Create own parser for better coloring
    - [ ] Better todo parsing
    - [ ] Proper block parsing
    - [ ] Adding line limits (visually with parsing end)
    - [ ] Replacing bullets with symbol (& handle nesting)
    - [ ] Gray out link brackets
    - [ ] Handle `***` and `==...==` blocks
    - [ ] Tag coloring
    - [ ] Fix displaying links in headings -> i want another color there
- [ ] Creating own formatter
    - [ ] Auto indent from -> => items
    - [ ] Auto line break (limit 80 etc, & indent accordingly)
- [ ] Parse templates
    - [ ] Dates (alot of them)
    - [ ] File names etc

# Shortcuts etc
- [ ] Prev/next funciton for every note (check for prev/next text)

### Advanced Features
- [ ] Creating column like plugin (nvim interaction stuff etc)                 
- [ ] Dataview like queries & display
- [ ] Ctrl + K - hover note (show note preview / frontmatter?)

### Things to fix
- [ ] Fix jumping not using a proper stack list!
- [ ] no bold/cursive font?
- [ ] missign symbols/devicons
- [ ] excalidraw compatibility
- [ ] table edit plugin

## Advanced Features
- Some [[dataview]] like querying -> maybe possible with cmp

## Terminal
- I think an image renderer would be required
 -> So i probably would try [[ghostty]] first
 => It seem it can support svg rendering as well

## Nvim Pluginso
- [[blink.cmp]] seems to be a modern replacement for cmp atm
 -> So maybe i should switch? 

Use a lua load to create the table from the returned data
 -> Add the other data as well (alias etc)

**Serialization between lua and c**

```lua
local str = [[
{
    { label = "Rust Book", kind = Normal },
    { label = "Lua Guide", kind = Alias },
}
]]
local tbl = assert(load("return " .. str))()
```
