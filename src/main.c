#include <measure/module.h>
#include <string/macros.h>
#include <string/module.h>

static StringMemory Strings;

#define PRINT_DEBUG 0

const char LINK_START = '[';
const char LINK_END = ']';
const char LINK_ALIAS = '|';

typedef enum
{
    RES_OK,
    RES_INSUFFICIENT_ARGUMENTS,
    RES_INVALID_CURSOR
} ParserResult;

typedef struct
{
    bool found;
    bool has_alias;
    int start_pos;
    int end_pos;
    int mid_pos;
    int start_matches;
    int end_matches;
} LinkInfo;

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

int main(int argc, char** argv)
{
    Timer t = {};
    timer_start(&t);
    str_init(&Strings, 0, 256, 0, 256);

    if (argc < 3) return RES_INSUFFICIENT_ARGUMENTS;

    str text = str_static(argv[1]);
    int cursorPos = atoi(argv[2]);

#if PRINT_DEBUG
    str_printc("Cursor %, Text len: %", NUM(cursorPos), NUM(text.len));
#endif

    if (cursorPos < 0) return RES_INVALID_CURSOR;
    if (text.len < cursorPos) return RES_INVALID_CURSOR;

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

    float programRuntime = timer_ms_since_start(&t);

#if PRINT_DEBUG

    str_printc("Link: >> % << alias '%'", STR(link), STR(alias));
    str_printc("Program Time | % ms |", FLOAT(programRuntime, 3));

#endif

    // Serialized output
    str_printc("%\n%\n%\n%", FLOAT(programRuntime, 3), BOO(info.found),
               STR(link), STR(alias));

    return RES_OK;
}
