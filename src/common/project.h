#ifndef __CURATOR_COMMON_PROJECT_H__
#define __CURATOR_COMMON_PROJECT_H__

#include "../database/database.h"

struct CuratorProject;
struct CuratorProjectMeta;

struct CuratorProject* Project__create(
        const char* title,
        const char* location);

struct CuratorProject* Project__open(
        const char* location
        );

void Project__close(struct CuratorProject* self);


struct CuratorProject {
    int version;
    char* title;
    struct CuratorDatabase* db;
    struct CuratorProjectMeta* meta;
};

struct CuratorProjectMeta {
    char* author;
};

#endif
