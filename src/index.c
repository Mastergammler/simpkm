#include "internal.h"

void write_dir_entry(IndexDir dirEntry)
{
    // TODO: int does not support uint yet?!
    str num = str_formatc_opt(IndexState.str_opt, "%", NUM(dirEntry.dir_id));
    fwrite(num.chars, 1, num.len, IndexState.paths);
    fputc(INDEX_COL_DELIM, IndexState.paths);
    fwrite(dirEntry.dir_path.chars, 1, dirEntry.dir_path.len, IndexState.paths);
    fputc(NL, IndexState.paths);

    str_pool_reset(IndexState.str_opt);
}

void write_file_entry(IndexEntry entry, FILE* out)
{
    str nums = str_formatc_opt(IndexState.str_opt, "%:%:%", NUM(entry.dir_id),
                               NUM(entry.is_alias), NUM(entry.file_exists));

    fwrite(entry.name.chars, 1, entry.name.len, out);
    fputc(INDEX_COL_DELIM, out);
    fwrite(entry.file_name.chars, 1, entry.file_name.len, out);
    fputc(INDEX_COL_DELIM, out);
    fwrite(nums.chars, 1, nums.len, out);
    fputc(NL, out);

    str_pool_reset(IndexState.str_opt);
}

int search_dir(IndexDir dir)
{
    str dupSymbol = DUP_SYM;
    str mdExt = str_static(".md");
    DIR* unixDir = opendir(dir.dir_path.chars);
    if (unixDir == NULL)
    {
        str_printc("Unable to open directory: %", STR(dir.dir_path));
        return RES_FILE_IO_ERR;
    }

    struct dirent* entry;
    while ((entry = readdir(unixDir)))
    {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        if (entry->d_type == DT_DIR)
        {
            StrPoolOptions frame = {.pool_idx = POOL_DEFAULT};
            str dirName = str_alloc_opt(frame, entry->d_name);
            DEBUG("DIR: %", STR(dirName));
            // transient string buffer etc
            str subdirPath =
                str_formatc_opt(frame, "%/%", STR(dir.dir_path), STR(dirName));
            IndexDir subdir = {IndexState.next_dir_idx++, subdirPath};
            write_dir_entry(subdir);
            search_dir(subdir);
            str_pool_reset(frame);
        }
        else
        {
            str fileName = str_alloc_opt(IndexState.str_opt, entry->d_name);

            // PERF: I had probably a TLB miss here, is was using
            //  256 B pool sizes for the allocation
            //  The time for adding the ends_with lookup increased runtime
            //  by around 20x
            bool isMd = str_ends_with(fileName, mdExt);
            if (isMd)
            {
                DEBUG("FILE: %", STR(fileName));
                StrSplitResult split = str_split_last(fileName, '.');
                IndexEntry indEnt = {.name = split.head,
                                     .file_name = dupSymbol,
                                     .dir_id = dir.dir_id,
                                     .is_alias = false,
                                     .file_exists = true};
                write_file_entry(indEnt, IndexState.index);
                IndexState.file_count++;
            }
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

    str_pool_reset((StrPoolOptions){POOL_TRANSIENT});
    str_pool_reset((StrPoolOptions){POOL_DEFAULT});
    fclose(IndexState.index);
    fclose(IndexState.paths);

    DEBUG("Files: %", NUM(IndexState.file_count));

    return (CmdResult){RES_OK};
}
