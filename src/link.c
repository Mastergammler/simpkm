#include "internal.h"

/*
 * Returns true when a end was found, so the search is exhausted
 */
bool matching_end_found(LinkInfo* info, char c, int i, bool forward)
{
    if (c == LINK_ALIAS)
    {
        info->mid_pos = i;
    }
    else if (c == LINK_START)
    {
        info->start_matches++;
        if (info->start_matches == 2)
        {
            info->start_pos = forward ? i + 1 : i + 2;
            if (not(forward)) return true;
        }
    }
    else if (c == LINK_END)
    {
        info->end_matches++;
        if (info->end_matches == 2)
        {
            // end is exclusive
            info->end_pos = forward ? i - 1 : i;
            if (forward) return true;
        }
    }

    return false;
}

LinkInfo parse(str text, int cursorPos)
{
    LinkInfo info = {};
    if (cursorPos >= text.len) return info;

    for (int i = cursorPos; i >= 0; i--)
    {
        if (matching_end_found(&info, text.chars[i], i, false)) break;
    }

    for (int i = cursorPos + 1; i < text.len; i++)
    {
        if (matching_end_found(&info, text.chars[i], i, true)) break;
    }

    if (info.start_matches == 2 && info.end_matches == 2 &&
        info.start_pos <= info.end_pos && cursorPos >= info.start_pos - 2 &&
        cursorPos <= info.end_pos + 2)
    {
        info.found = true;
    }

    if (info.found && info.mid_pos > 0)
    {
        info.has_alias = true;
    }

    /*DEBUG("sPos: %, ePos: %, nStart: %, nEnd: %", NUM(info.start_pos),
          NUM(info.end_pos), NUM(info.start_matches), NUM(info.end_matches));*/

    return info;
};

LinkResult parse_link(str text, int cursorPos)
{
    LinkInfo info = parse(text, cursorPos);
    str link = info.found
                   ? str_sub(text, info.start_pos,
                             info.has_alias ? info.mid_pos : info.end_pos)
                   : (str){};
    str alias =
        info.has_alias
            ? str_sub(text, info.has_alias ? info.mid_pos + 1 : info.start_pos,
                      info.end_pos)
            : (str){};

    return (LinkResult){
        .found = info.found, .link = str_trim(link), .alias = str_trim(alias)};
}

CmdResult cmd_parse_link(str text, int cursorPos)
{
    DEBUG("Cursor %, Text len: %", NUM(cursorPos), NUM(text.len));

    if (cursorPos < 0) return (CmdResult){RES_INVALID_CURSOR};
    if (text.len < cursorPos) return (CmdResult){RES_INVALID_CURSOR};

    LinkResult res = parse_link(text, cursorPos);
    DEBUG("Link: >> % << alias '%'", STR(res.link), STR(res.alias));

    // Serialized output
    str_printc("%\n%\n%", BOO(res.found), STR(res.link), STR(res.alias));

    return (CmdResult){RES_OK};
}
