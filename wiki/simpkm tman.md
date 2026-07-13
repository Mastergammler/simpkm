# [[simpkm]] [[task management]] 
[[pkm]]

**Idea**
- Local ticketing system, [[markdown]] based.
- 1 Ticket = 1 File
- State tracking with tags only `state/inprogress` etc

*Goal*
Replacing the [[gitlab]] [[web-ui]] because it is clunky

**Definitions**
- *Task Todos:* Get a Ticket, ticke todos are task based
- *[[Tasklist]]:* Is a file based todo system, for in code

### [[taglist]]

Showing a list of tags and done tickets, just filter by tag

```
#ui [3/5]
#audio [1/2]
#engine [15/32]
```

Can also show kind of milestones
```
#milstone/demo [3/5]
- ⮜ 125 ⮞  Implementing Mechanics (done)
- ⮜ 136 ⮞  Implementing Other thing (done)
- ⮜ 133 ⮞  Integrate Level loading (done)
- ⮜ 134 ⮞  Another one (open)
- ⮜ 135 ⮞  Integrating next stuff (open)
#milestone/release [23/77]
```

### File Names
- [[#myfile]] => starting with `#` is not a good idea, because heading not ref parsing
 -> It would also kind of conflict with tags
- How about a `|` -> doesn't work, because it's the alias separator for parsing
 -> Even thou `|125| My Ticket` looks kind of neat
 - How about `«125» My Ticket` -> looks also kind of neat
  -> [[«125» Ticket Testing]]
- Or this? `¦125¦ My Ticket`, dunno if that is nicer?
 -> Because it still doesn't look as neat
- `⮜ 125 ⮞  My Ticket` -> [[⮜ 125 ⮞  My Ticket]]
 -> Yea, i think i'll just stick to 2 spaces!


## TASK OVERVIEW

**Functions**
- [x] Create next ticket note (with ticket number)
    - [x] Next ticket number function (last item in folder)
    - [x] Create a note in tickets folder (vault option)
- [ ] Show a ticket list (open tickets in maybe in quick fix?)

**Improvements**
- [ ] Auto adding alias for ticket -> *Ticket-124* etc


