#include "database.h"
#include <stdarg.h>
#include <string.h>

struct CuratorDatabase *Database__create(const char *fileName) {
  struct CuratorDatabase *db =
      (struct CuratorDatabase *)malloc(sizeof(struct CuratorDatabase));

  db->fileName = fileName;
  int result = sqlite3_open(db->fileName, &db->dbPtr);
  if (result != SQLITE_OK) {
    Database__setError(db, "Unable to create a new database");
    db->dbPtr = 0;
    return db;
  }
  db->isOpened = 1;

  return db;
}

struct CuratorDatabase *Database__open(const char *fileName) {
  return Database__create(fileName);
}

void Database__close(struct CuratorDatabase *self) {
  if (self == 0) {
    return;
  }

  if (self->dbPtr == 0) {
    return;
  }

  int result = sqlite3_close(self->dbPtr);

  if (result != SQLITE_OK) {
    // Force close
  }

  free(self);
}

int Database__hasError(struct CuratorDatabase *self) {
  if (self == 0) {
    return 0;
  }

  return self->hasError;
}

void Database__setError(struct CuratorDatabase *self, const char *format, ...) {
  if (self == 0) {
    return;
  }

  if (self->hasError && self->errorMsg != 0) {
    // free((void *)self->errorMsg);
  }

  if (format == 0) {
    return;
  }

  char buffer[MAX_ERROR_MESSAGE_LENGTH];
  memset(buffer, 0, sizeof(buffer));
  va_list ap;
  int retVal;
  va_start(ap, format);
  (void)vsnprintf(buffer, MAX_ERROR_MESSAGE_LENGTH - 1, format, ap);
  va_end(ap);
  self->errorMsg = buffer;
  self->hasError = 1;
}

const char *Database__getError(struct CuratorDatabase *self) {
  if (self == 0) {
    return "";
  }

  if (self->hasError == 0) {
    return "";
  }

  if (self->errorMsg == 0) {
    return "";
  }

  return (const char *)self->errorMsg;
}

void Database__clearError(struct CuratorDatabase *self) {
  if (self == 0) {
    return;
  }

  if (self->hasError == 0) {
    return;
  }

  self->hasError = 0;

  if (self->errorMsg == 0) {
    return;
  }

  free(self->errorMsg);
}

sqlite3_stmt *Database__prepareStatement(struct CuratorDatabase *self,
                                         const char *sql) {
  if (self == 0) {
    return 0;
  }

  if (self->dbPtr == 0 || self->isOpened == 0) {
    return 0;
  }

  sqlite3_stmt *statement;
  int result = sqlite3_prepare_v3(self->dbPtr, sql, -1, 0, &statement, 0);
  if (result != SQLITE_OK) {
    Database__setError(self, "[%d] Unable to prepare statement! (%s)",
                       sqlite3_errcode(self->dbPtr),
                       sqlite3_errmsg(self->dbPtr));

    return 0;
  }

  return statement;
}

void Database__finalizeStatement(struct CuratorDatabase *self,
                                 sqlite3_stmt *statement) {
  if (self == 0 || self->dbPtr == 0 || statement == 0) {
    return;
  }

  int result = sqlite3_finalize(statement);
  if (result != SQLITE_OK) {
    Database__setError(self, "[%d] Unable to finalize statement: %s",
                       sqlite3_errcode(self->dbPtr),
                       sqlite3_errmsg(self->dbPtr));
  }
}

int Database__executeStatement(struct CuratorDatabase *self,
                               sqlite3_stmt *statement) {
  if (self == 0 || self->dbPtr == 0 || statement == 0) {
    return -1;
  }

  int result = sqlite3_step(statement);
  if (result != SQLITE_OK) {
    Database__setError(self, "[%d] Unable to execute statement: %s",
                       sqlite3_errcode(self->dbPtr),
                       sqlite3_errmsg(self->dbPtr));
  }

  return result;
}
