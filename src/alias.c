#include "internal.h"

CmdResult cmd_create_alias_index(str grepFile, str outFile)
{
    str dupSymbol = DUP_SYM;

    // do stuff
    FILE* inputFile = fopen(grepFile.chars, "rb");
    FILE* indexFile = fopen(outFile.chars, "a");

    if (not(inputFile) || not(indexFile)) return (CmdResult){RES_FILE_IO_ERR};

    StrPoolOptions opt = {.pool_idx = POOL_DEFAULT};

    str path = {};
    str lineNo = {};
    str link = {};

    char line[256];
    int lineStartIdx = 0;
    int lineLen = 0;
    int col = 0;

    bool eof = false;
    char ch;

    while (not(lineLen >= 256) && ((ch = getc(inputFile)) != EOF || not(eof)))
    {
        if (ch == EOF) eof = true;

        if (ch == '\n' || ch == ':' || eof)
        {
            str* cur;
            switch (col)
            {
            case 0:
                cur = &path;
                break;
            case 1:
                cur = &lineNo;
                break;
            case 2:
                cur = &link;
                break;
            default:
                cur = NULL;
            }

            if (cur)
            {
                cur->chars = &line[lineStartIdx];
                cur->len = lineLen - lineStartIdx;
            }

            if (ch == '\n' || eof)
            {
                LinkResult res = parse_link(link, 0);
                DEBUG("[%|%] of %", STR(res.link), STR(res.alias), STR(path));

                if (res.found)
                {
                    // TASKLIST:
                    // - handle file dir
                    // - handle existing / non-existing file
                    // - handle deduplication
                    bool isAlias = res.alias.len > 0;
                    IndexEntry indEnt = {.name = isAlias ? res.alias : res.link,
                                         .file_name =
                                             isAlias ? res.link : dupSymbol,
                                         .dir_id = 0,
                                         .is_alias = isAlias,
                                         .file_exists = false};
                    write_file_entry(indEnt, indexFile);
                }

                col = 0;
                lineStartIdx = 0;
                lineLen = 0;
                link = (str){};
                path = (str){};
                lineNo = (str){};
                continue;
            }
            else
            {
                col++;
                lineStartIdx = lineLen + 1;
            }
        }
        line[lineLen++] = ch;
    }

    return (CmdResult){};
}
