# Handling inline images

I would still like to use [[excalidraw]] in order to create my graphics,
because it's a very simple but convenient way of doing that.

Therefore i need the [[image.nvim]] plugin which can handle svg and png files,
through the [[kitty image protocol]]. It also needs [[imagemagick]] and 
[[luarocks]] as a dependency in order to trigger the conversion pipeline.

**Approach**
- [[image.nvim]]
- use [[png|pngs]]
- convert links with function

> These are the first steps for the integration, which i guess, works for the 
> start, but might become annoying later. But this should work for now

### Problems
- Rendering [[svg|svgs]] lags as shit, and doesn't render excalidraw correctly
 -> Therefore i would need to use the [[png]] files of excalidraw
 => These can also be scaled with [[image.nvim]] somehow, dunno how yet
- I also need to convert the current links & retrigger the 
  [[obsidian excalidraw]] plugin to rerender those 
  -> I guess i have to do this on demand, or run a script or something
- The paths can not contain whitespaces, which the excalidraw plugin adds 
  by default, so i need to convert these as well ...
- **excalidraw compatibility** - when i replace the links, i can not open it in 
  via excalidraw anymore, because it doesn't find it ...

**Size issues etc**
I now get scaling issues, and have worse quality, while using way more space.
The png uses around 8x the space, while still beeing actually too small.
This is just insanely much if i end up with 10x - 20x the size ...
-> I need a proper excalidraw renderer i suppose

