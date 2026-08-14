#include "internal.h"

void write_dir_entry(IndexDir dirEntry)
{
    // TODO: int does not support uint yet?!
    str num = str_formatc_opt(IndexState.file_pool, "%", fmt_n(dirEntry.dir_id));
    fwrite(num.chars, 1, num.len, IndexState.paths);
    fputc(INDEX_COL_DELIM, IndexState.paths);
    fwrite(dirEntry.dir_path.chars, 1, dirEntry.dir_path.len, IndexState.paths);
    fputc(NL, IndexState.paths);

    str_pool_reset(IndexState.file_pool);
}

void write_file_entry(IndexEntry entry, FILE* out)
{
    str nums = str_formatc_opt(IndexState.file_pool, "%:%:%", fmt_n(entry.dir_id),
                               fmt_n(entry.is_alias), fmt_n(entry.file_exists));

    fwrite(entry.name.chars, 1, entry.name.len, out);
    fputc(INDEX_COL_DELIM, out);
    fwrite(entry.file_name.chars, 1, entry.file_name.len, out);
    fputc(INDEX_COL_DELIM, out);
    fwrite(nums.chars, 1, nums.len, out);
    fputc(NL, out);

    str_pool_reset(IndexState.file_pool);
}

int search_dir(IndexDir dir)
{
    str dupSymbol = DUP_SYM;
    str mdExt = str_static(".md");
    DIR* unixDir = opendir(dir.dir_path.chars);
    if (unixDir == NULL)
    {
        str_printc("Unable to open directory: %", fmt_s(dir.dir_path));
        return RES_FILE_IO_ERR;
    }

    struct dirent* entry;
    while ((entry = readdir(unixDir)))
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (entry->d_type == DT_DIR)
        {
            // Excluding directories starting with '.' by default,
            // because those almost never hold important files for us
            if (entry->d_name[0] == '.') continue;

            uint64_t prevPos =
                Strings->pools[IndexState.dir_pool.pool_idx].cursor_idx;
            str dirName = str_alloc_opt(IndexState.dir_pool, entry->d_name);
            DEBUG("DIR: %/%", fmt_s(dir.dir_path), fmt_s(dirName));
            str subdirPath = str_formatc_opt(IndexState.dir_pool, "%/%",
                                             fmt_s(dir.dir_path), fmt_s(dirName));
            IndexDir subdir = {IndexState.next_dir_idx++, subdirPath};
            write_dir_entry(subdir);
            search_dir(subdir);

            // NOTE: for recursive traversal WE CAN NOT reset the whole pool.
            //  We use this like a stack instead, and just pop the end, after
            //  we finished: Recursion == Stack behaviour
            str_pool_reset_to(IndexState.dir_pool, prevPos);
        }
        else
        {
            str fileName = str_alloc_opt(IndexState.file_pool, entry->d_name);
            TRACE("Checking file: %", fmt_s(fileName));

            // PERF: I had probably a TLB miss here, is was using
            //  256 B pool sizes for the allocation
            //  The time for adding the ends_with lookup increased runtime
            //  by around 20x
            bool isMd = str_ends_with(fileName, mdExt);
            if (isMd)
            {
                DEBUG("FILE: %", fmt_s(fileName));
                StrSplitResult split = str_split_last(fileName, '.');
                IndexEntry indEnt = {.name = split.head,
                                     .file_name = dupSymbol,
                                     .dir_id = dir.dir_id,
                                     .is_alias = false,
                                     .file_exists = true};
                write_file_entry(indEnt, IndexState.index);
                IndexState.file_count++;
            }

            str_pool_reset(IndexState.file_pool);
        }
    }

    return RES_OK;
}

CmdResult cmd_create_index(str searchPath)
{
    IndexState.index = fopen(IndexState.index_file.chars, "wb");
    IndexState.paths = fopen(IndexState.paths_file.chars, "wb");

    IndexDir cwd = {IndexState.next_dir_idx++, str_static(".")};
    write_dir_entry(cwd);
    IndexDir basePath = {IndexState.next_dir_idx++, searchPath};
    write_dir_entry(basePath);

    search_dir(basePath);

    str_pool_reset(IndexState.dir_pool);
    str_pool_reset(IndexState.file_pool);
    fclose(IndexState.index);
    fclose(IndexState.paths);

    DEBUG("Files: %", fmt_n(IndexState.file_count));

    return (CmdResult){RES_OK};
}
