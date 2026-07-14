#ifndef SIMPKM_INTERNAL
#define SIMPKM_INTERNAL

#include <measure/module.h>
#include <string/macros.h>
#include <string/module.h>

#include <dirent.h>

// TASKLIST: [0/1]
//  - parse also when on top of [[ or ]]

static StringMemory Strings;

#define PRINT_DEBUG 0

#define DEBUG(cstr, ...)                                                       \
    if (PRINT_DEBUG) str_printc(cstr, ##__VA_ARGS__)

const char LINK_START = '[';
const char LINK_END = ']';
const char LINK_ALIAS = '|';
const char INDEX_COL_DELIM = ':';
const char NL = '\n';

typedef enum
{
    POOL_DEFAULT,
    POOL_PRINT,
    POOL_TRANSIENT,
    POOL_count
} StrPools;

typedef enum
{
    RES_OK,
    RES_UNKNOWN_COMMAND,
    RES_INSUFFICIENT_ARGUMENTS,
    RES_INVALID_CURSOR,
    RES_FILE_IO_ERR,
} ResultCode;

typedef struct
{
    ResultCode code;
    str cmd_result;
} CmdResult;

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

typedef struct
{
    uint dir_id;
    str dir_path;
} IndexDir;

typedef struct
{
    /* file name or alias */
    str name;
    /* without path info and extension */
    str file_name;
    uint dir_id;
    /* if the current name represents an alias */
    bool is_alias;
    /* if the current files is a created link or actually exists */
    bool file_exists;

} IndexEntry;

typedef struct
{
    FILE* index_file;
    FILE* paths_file;
    uint next_dir_idx;
    uint file_count;
    StrPoolOptions str_opt;

} IndexStateData;

static IndexStateData IndexState;

#endif // simpkm internal
