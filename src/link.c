#include "internal.h"

// TODO: a valid link is only between [[..]]
//  or [[..|   BUT NOT |..|
LinkInfo parse(str text, int cursorPos)
{
    LinkInfo info = {};

    for (int i = cursorPos; i >= 0; i--)
    {
        char c = text.chars[i];
        if (c == LINK_ALIAS)
        {
            info.mid_pos = i;
        }
        else if (c == LINK_START)
        {
            info.start_matches++;
            if (info.start_matches == 2) break;

            info.start_pos = i + 1;
        }
        // other link
        else if (c == LINK_END)
        {
            info.start_matches = 0;
            info.start_pos = 0;
            break;
        }
    }

    if (!(info.start_matches == 2)) return info;

    for (int i = cursorPos; i < text.len; i++)
    {
        char c = text.chars[i];
        if (c == LINK_ALIAS)
        {
            info.mid_pos = i;
        }
        else if (c == LINK_END)
        {
            info.end_matches++;
            if (info.end_matches == 2) break;

            // end is exclusive
            info.end_pos = i;
        }
        else if (c == LINK_START)
        {
            info.end_matches = 0;
            info.end_pos = 0;
            break;
        }
    }

    if (info.start_matches == 2 && info.end_matches == 2)
    {
        info.found = true;
    }

    if (info.found && info.mid_pos > 0)
    {
        info.has_alias = true;
    }

    return info;
};

CmdResult cmd_parse_link(str text, int cursorPos)
{
    DEBUG("Cursor %, Text len: %", NUM(cursorPos), NUM(text.len));

    if (cursorPos < 0) return (CmdResult){RES_INVALID_CURSOR};
    if (text.len < cursorPos) return (CmdResult){RES_INVALID_CURSOR};

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

    DEBUG("Link: >> % << alias '%'", STR(link), STR(alias));

    // Serialized output
    str_printc("%\n%\n%", BOO(info.found), STR(link), STR(alias));

    return (CmdResult){RES_OK};
}
