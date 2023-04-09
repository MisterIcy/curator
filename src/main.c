#include <stdio.h>

#include "database/database.h"
#include <sqlite3.h>

int main(int argc, char **argv) {

  struct CuratorDatabase *db = Database__create("test.sqlite");
  Database__setError(db, "test error");
  sqlite3_stmt *stmt =
      Database__prepareStatement(db, "CREATE TABLE scenes (id INT)");
  int result = Database__executeStatement(db, stmt);

  if (result != SQLITE_OK) {
    printf("Error: %s\n", Database__getError(db));
  }

  Database__close(db);

  return 0;
}
