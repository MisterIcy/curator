#include "project.h"

struct CuratorProject* Project__create(const char* title, const char* location)
{
    struct CuratorProject* project = (struct CuratorProject*)malloc(sizeof(struct CuratorProject));

    // Check if we have access to the location.
    // If not, return null
    
    // Create a new database and initialize the project
    
    struct CuratorDatabase* db = Database__create("filename.curator");
    if (db == 0) {
        // Error!
    }

    project->db = db;

    return project;
}
