#include "internal.h"

#include "alias.c"
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
    else if (strcmp(argv[argIdx], "alias") == 0)
    {
        if (argc < 3) return (CmdResult){RES_INSUFFICIENT_ARGUMENTS};

        str grepFile = str_static(argv[++argIdx]);
        res = cmd_create_alias_index(grepFile, IndexState.index_file);
    }
    else
    {
        res = (CmdResult){RES_UNKNOWN_COMMAND};
    }

    return res;
}

typedef struct
{
    Timer timer;
    Arena memory;
    AllocContext mem;
    StringMemory strings;

} Program;

static Program Prog;
StringMemory* StrMem;

void init_program(uint64_t memory)
{
    MglibcAllocCtx = &Prog.mem;
    Strings = &Prog.strings;
    Prog.mem = ctx_init_default(&Prog.memory);

    timer_start(&Prog.timer);
    arena_init(&Prog.memory, memory);

    str_pool_prepare(Prog.mem, &Prog.strings, POOL_count);
    define_pool(POOL_DEFAULT, 2024, .is_default = true);
    define_pool(POOL_FILE, 256);
    define_pool(POOL_PRINT, 256, .is_print = true);
    define_pool(POOL_TRANSIENT, 256, .is_transient = true);
    str_pool_finalize(Prog.mem);
}

int main(int argc, char** argv)
{
    init_program(4096);

    IndexState = (IndexStateData){};
    IndexState.file_pool = (StrPoolOptions){.pool_idx = POOL_FILE};
    IndexState.dir_pool = (StrPoolOptions){.pool_idx = POOL_DEFAULT};
    IndexState.index_file = str_static(".index");
    IndexState.paths_file = str_static(".index_paths");
    CmdResult res = handle_args(argc, argv);

    float programRuntime = timer_ms_since_start(&Prog.timer);
    str_printc("%", FLOAT(programRuntime, 3));

    return res.code;
}
