#ifndef __CURATOR_DATABASE_H__
#define __CURATOR_DATABASE_H__
#include <sqlite3.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ERROR_MESSAGE_LENGTH 4096
struct CuratorDatabase;

/**
 * @brief Creates a new database.
 * @param fileName the name of the file
 * @return A pointer to the newly opened database.
 */
struct CuratorDatabase *Database__create(const char *fileName);

/**
 * @brief Opens a database.
 * @param fileName the name of the file.
 * @return A pointer to the newly opened database. Returns NULL in case of
 * error.
 */
struct CuratorDatabase *Database__open(const char *fileName);

/**
 * @brief Closes an opened database.
 * @param self The database to be closed.
 */
void Database__close(struct CuratorDatabase *self);

/**
 * @brief Checks if a previous operation has raised an error.
 * @param self The database object to be used
 * @return 1 if an error is present, otherwise 0.
 */
int Database__hasError(struct CuratorDatabase *self);

/**
 * @brief Sets an error to the database.
 * @param self The database object to be used.
 * @param errorMsg The error string.
 */
void Database__setError(struct CuratorDatabase *self, const char *format, ...);
/**
 * @brief Gets an error from the database
 * @param self The database object to be used.
 * @return A string containing the error, on an empty string in case no error
 * exists on the database.
 */
const char *Database__getError(struct CuratorDatabase *self);

/**
 * @brief Clears the last error from the database
 * @param self The database object to be used.
 */
void Database_clearError(struct CuratorDatabase *self);

/// Low Level Operations

sqlite3_stmt *Database__prepareStatement(struct CuratorDatabase *self,
                                         const char *sql);

void Database__finalizeStatement(struct CuratorDatabase *self,
                                 sqlite3_stmt *statement);

int Database__executeStatement(struct CuratorDatabase *self,
                               sqlite3_stmt *statement);

/**
 * @brief Database Structure
 */
struct CuratorDatabase {
  /**
   * Database version
   */
  int version;
  /**
   * Denotes whether the connection to the database is open.
   */
  int isOpened;
  int hasError;
  char *errorMsg;
  const char *fileName;
  sqlite3 *dbPtr;
};

#endif
