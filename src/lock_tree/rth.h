/* -*- mode: C; c-basic-offset: 4 -*- */
#ident "Copyright (c) 2007-8 Tokutek Inc.  All rights reserved."

#ident "The technology is licensed by the Massachusetts Institute of Technology, Rutgers State University of New Jersey, and the Research Foundation of State University of New York at Stony Brook under United States of America Serial No. 11/760379 and to the patents and/or patent applications resulting from it."

/**
   \file  hash_table.h
   \brief Hash table
  
*/

//Defines BOOL data type.
#include <db.h>
#include <brttypes.h>
#include <rangetree.h>

typedef u_int32_t uint32;

typedef struct __toku_rt_forest toku_rt_forest;
struct __toku_rt_forest {
    toku_range_tree* self_read;
    toku_range_tree* self_write;
};

typedef struct __toku_rth_elt toku_rth_elt;
struct __toku_rth_elt {
    DB_TXN*         key;
    toku_rt_forest  value;
    toku_rth_elt*   next;
};

typedef struct __toku_rth toku_rth;
struct __toku_rth {
    toku_rth_elt**  table;
    uint32          num_keys;
    uint32          array_size;
    uint32          finger_index;
    toku_rth_elt*   finger_ptr;
    BOOL            finger_start;
    BOOL            finger_end;
    /** The user malloc function */
    void*         (*malloc) (size_t);
    /** The user free function */
    void          (*free)   (void*);
    /** The user realloc function */
    void*         (*realloc)(void*, size_t);
};

int  toku_rth_create(toku_rth** ptable,
                     void* (*user_malloc) (size_t),
                     void  (*user_free)   (void*),
                     void* (*user_realloc)(void*, size_t));

toku_rt_forest* toku_rth_find       (toku_rth* table, DB_TXN* key);

void            toku_rth_start_scan (toku_rth* table);

toku_rt_forest* toku_rth_next       (toku_rth* table);

void            toku_rth_delete     (toku_rth* table, DB_TXN* key);

void            toku_rth_close      (toku_rth* table);

int             toku_rth_insert     (toku_rth* table, DB_TXN* key);
