#include "internal.h"

#include "index.c"
#include "link.c"

CmdResult handle_args(int argc, char** argv)
{
    CmdResult res = {};
    int argIdx = 1;

    if (argc < 2) return (CmdResult){RES_INSUFFICIENT_ARGUMENTS};

    if (strcmp(argv[argIdx], "link") == 0)
    {
        if (argc < 4) return (CmdResult){RES_INSUFFICIENT_ARGUMENTS};

        str text = str_static(argv[++argIdx]);
        int cursorPos = atoi(argv[++argIdx]);

        res = cmd_parse_link(text, cursorPos);
    }
    else if (strcmp(argv[argIdx], "index") == 0)
    {
        if (argc < 3) return (CmdResult){RES_INSUFFICIENT_ARGUMENTS};

        str searchPath = str_static(argv[++argIdx]);
        res = cmd_create_index(searchPath);
    }
    else
    {
        res = (CmdResult){RES_UNKNOWN_COMMAND};
    }

    return res;
}

int main(int argc, char** argv)
{
    Timer t = {};
    timer_start(&t);
    str_init(&Strings, 256, 256, 256, 256);

    CmdResult res = handle_args(argc, argv);

    float programRuntime = timer_ms_since_start(&t);
    str_printc("%", FLOAT(programRuntime, 3));

    return res.code;
}
