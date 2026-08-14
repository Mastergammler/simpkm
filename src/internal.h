#ifndef SIMPKM_INTERNAL
#define SIMPKM_INTERNAL

#include <measure/module.h>
#include <string/macros.h>
#include <string/module.h>

#include <dirent.h>
#include <stdint.h>

// TASKLIST: [1/1]
//  ✔ parse also when on top of [[ or ]]

static StringMemory* Strings;

#define PRINT_DEBUG 0
#define PRINT_TRACE 0

#define DEBUG(cstr, ...)                                                       \
    if (PRINT_DEBUG) str_printc(cstr, ##__VA_ARGS__)

#define TRACE(cstr, ...)                                                       \
    if (PRINT_TRACE) str_printc(cstr, ##__VA_ARGS__)

#define not(cond) !(cond)
#define DUP_SYM str_static("\"")
#define EXCLUDE_DIR_START str_static(".")

const char LINK_START = '[';
const char LINK_END = ']';
const char LINK_ALIAS = '|';
const char INDEX_COL_DELIM = ':';
const char NL = '\n';

typedef enum
{
    POOL_DEFAULT,
    POOL_FILE,
    POOL_PRINT,
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
    str link;
    str alias;
} LinkResult;

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
    uint32_t dir_id;
    str dir_path;
} IndexDir;

typedef struct
{
    /* file name or alias */
    str name;
    /* without path info and extension */
    str file_name;
    uint32_t dir_id;
    /* if the current name represents an alias */
    bool is_alias;
    /* if the current files is a created link or actually exists */
    bool file_exists;

} IndexEntry;

typedef struct
{
    str index_file;
    str paths_file;

    FILE* index;
    FILE* paths;
    uint32_t next_dir_idx;
    uint32_t file_count;

    // NOTE: files and dirs have different lifetimes
    //-> So they need to have their own pool!
    StrPoolOptions file_pool;
    StrPoolOptions dir_pool;

} IndexStateData;

static IndexStateData IndexState;

LinkResult parse_link(str text, int cursorPos);
void write_file_entry(IndexEntry entry, FILE* out);

#endif // simpkm internal
