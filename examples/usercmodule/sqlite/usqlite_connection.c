/*
MIT License

Copyright(c) 2021 Elvin Slavik

Permission is hereby granted, free of charge, to any person obtaining a copy
of this softwareand associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and /or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright noticeand this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "usqlite.h"

#include "py/objstr.h"
// ------------------------------------------------------------------------------

//database interface funcs
mp_obj_t usqlite_insertSoh(size_t n_args, const mp_obj_t* args);
mp_obj_t usqlite_initializeDatabase(mp_obj_t self_in);
mp_obj_t usqlite_fetchSoh(size_t n_args,const mp_obj_t* args);
mp_obj_t usqlite_logEvent(size_t n_args, const mp_obj_t* args);
mp_obj_t usqlite_insertCommand(size_t n_args, const mp_obj_t* args);
mp_obj_t usqlite_getNextCommand(mp_obj_t self_in);
mp_obj_t usqlite_deleteCommand(mp_obj_t self_in, mp_obj_t index);
mp_obj_t usqlite_insertPayloadData(size_t n_args, const mp_obj_t* args);
mp_obj_t usqlite_fetchPayloadData(size_t n_args,const mp_obj_t* args);
mp_obj_t usqlite_deletePayloadDataID(mp_obj_t self_in, mp_obj_t index);
mp_obj_t usqlite_createUplink(size_t n_args, const mp_obj_t* args);
mp_obj_t usqlite_fetchDataBlobInto(size_t n_args, const mp_obj_t* args);
mp_obj_t usqlite_writeDataBlob(size_t n_args, const mp_obj_t* args);
mp_obj_t usqlite_getMissingPacketIds(size_t n_args, const mp_obj_t* args);
mp_obj_t usqlite_getMissingPacketIds1(size_t n_args, const mp_obj_t* args);
mp_obj_t usqlite_setUplinkPacketReceived(size_t n_args, const mp_obj_t* args);
mp_obj_t usqlite_deleteEntry(size_t n_args, const mp_obj_t* args);
mp_obj_t usqlite_insertConfig(size_t n_args, const mp_obj_t* args);
mp_obj_t usqlite_fetchConfig(size_t n_args, const mp_obj_t* args);
mp_obj_t usqlite_getNextDownlinkID(mp_obj_t self_in);
mp_obj_t usqlite_getNextDownlink(mp_obj_t self_in);
mp_obj_t usqlite_createDownlink(size_t n_args, const mp_obj_t* args);
mp_obj_t usqlite_createDownlinkEmpty(size_t n_args, const mp_obj_t* args);
mp_obj_t usqlite_getTableSize(size_t n_args, const mp_obj_t* args);


MP_DEFINE_CONST_FUN_OBJ_1(usqlite_initializeDatabase_obj, usqlite_initializeDatabase);

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_insertSoh_obj, 3, 3 ,usqlite_insertSoh);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_fetchSoh_obj, 2, 4 ,usqlite_fetchSoh);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_logEvent_obj, 5, 5 ,usqlite_logEvent);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_insertCommand_obj, 4, 4 ,usqlite_insertCommand);
MP_DEFINE_CONST_FUN_OBJ_1(usqlite_getNextCommand_obj, usqlite_getNextCommand);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_deleteCommand_obj,2,2, usqlite_deleteCommand);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_insertPayloadData_obj, 4, 5 ,usqlite_insertPayloadData);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_fetchPayloadData_obj,2, 3,  usqlite_fetchPayloadData);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_deletePayloadDataID_obj,2,2, usqlite_deletePayloadDataID);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_createUplink_obj, 4, 4 ,usqlite_createUplink);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_fetchDataBlobInto_obj, 6, 6 ,usqlite_fetchDataBlobInto);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_writeDataBlob_obj, 6, 6 ,usqlite_writeDataBlob);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_getMissingPacketIds_obj,2,2, usqlite_getMissingPacketIds);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_setUplinkPacketReceived_obj, 3, 4 ,usqlite_setUplinkPacketReceived);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_deleteEntry_obj, 3, 4 ,usqlite_deleteEntry);

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_insertConfig_obj, 2, 3 ,usqlite_insertConfig);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_fetchConfig_obj, 2, 3 ,usqlite_fetchConfig);

MP_DEFINE_CONST_FUN_OBJ_1(usqlite_getNextDownlink_obj, usqlite_getNextDownlink);
MP_DEFINE_CONST_FUN_OBJ_1(usqlite_getNextDownlinkID_obj, usqlite_getNextDownlinkID);

MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_createDownlink_obj, 1, 5 ,usqlite_createDownlink);
MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_createDownlinkEmpty_obj, 1, 5 ,usqlite_createDownlinkEmpty);


MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_getTableSize_obj, 1, 2 ,usqlite_getTableSize);


STATIC mp_obj_t usqlite_connection_close(mp_obj_t self_in);

// ------------------------------------------------------------------------------

STATIC mp_obj_t usqlite_connection_make_new(const mp_obj_type_t *type, size_t n_args, size_t n_kw, const mp_obj_t *args) {
    usqlite_connection_t *self = m_new_obj(usqlite_connection_t);

    self->base.type = &usqlite_connection_type;
    self->db = (sqlite3 *)MP_OBJ_TO_PTR(args[0]);
    self->row_type = MP_QSTR_tuple;
    mp_obj_list_init(&self->cursors, 0);

    return MP_OBJ_FROM_PTR(self);
}

// ------------------------------------------------------------------------------

STATIC void usqlite_connection_print(const mp_print_t *print, mp_obj_t self_in, mp_print_kind_t kind) {
    usqlite_connection_t *self = MP_OBJ_TO_PTR(self_in);

    mp_printf(print, "<%s '%s'>", mp_obj_get_type_str(self_in), self->db ? sqlite3_db_filename(self->db, NULL) : "");
}

// ------------------------------------------------------------------------------

STATIC mp_obj_t usqlite_connection_close(mp_obj_t self_in) {
    LOGFUNC;

    usqlite_connection_t *self = (usqlite_connection_t *)MP_OBJ_TO_PTR(self_in);
    if (!self->db) {
        return mp_const_none;
    }
	/*
    for (size_t i = 0; i < self->cursors.len; i++)
    {
        mp_obj_t cursor = self->cursors.items[i];
        self->cursors.items[0] = mp_const_none;
        usqlite_cursor_close(cursor);
        #if MICROPY_MALLOC_USES_ALLOCATED_SIZE
        m_free(MP_OBJ_TO_PTR(cursor), sizeof(usqlite_cursor_t));
        #else
        m_free(MP_OBJ_TO_PTR(cursor));
        #endif
    }
	*/
    usqlite_logprintf(___FUNC___ " closing '%s'\n", sqlite3_db_filename(self->db, NULL));
    sqlite3_close(self->db);
    self->db = NULL;

    return mp_const_none;
}

MP_DEFINE_CONST_FUN_OBJ_1(usqlite_connection_close_obj, usqlite_connection_close);

// ------------------------------------------------------------------------------

STATIC mp_obj_t usqlite_connection_del(mp_obj_t self_in) {
    usqlite_logprintf(___FUNC___, "\n");

    usqlite_connection_close(self_in);

    return mp_const_none;
};

MP_DEFINE_CONST_FUN_OBJ_1(usqlite_connection_del_obj, usqlite_connection_del);

// ------------------------------------------------------------------------------

STATIC mp_obj_t usqlite_connection_cursor(mp_obj_t self_in) {
    usqlite_connection_t *self = MP_OBJ_TO_PTR(self_in);

    mp_obj_t args[2] =
    {
        MP_OBJ_FROM_PTR(self),
        mp_const_none
    };

    #if defined(MP_OBJ_TYPE_GET_SLOT)
    return MP_OBJ_TYPE_GET_SLOT(&usqlite_cursor_type, make_new)(NULL, MP_ARRAY_SIZE(args), 0, args);
    #else
    return usqlite_cursor_type.make_new(NULL, MP_ARRAY_SIZE(args), 0, args);
    #endif
}

STATIC MP_DEFINE_CONST_FUN_OBJ_1(usqlite_connection_cursor_obj, usqlite_connection_cursor);

// ------------------------------------------------------------------------------

STATIC mp_obj_t usqlite_connection_execute(size_t n_args, const mp_obj_t *args) {
    usqlite_connection_t *self = MP_OBJ_TO_PTR(args[0]);

    mp_obj_t xargs[4] =
    {
        MP_OBJ_FROM_PTR(self),
        mp_const_false,
        args[1]
    };

    size_t nxargs = 3;

    if (n_args == 3) {
        xargs[3] = args[2];
        nxargs++;
    }

    #if defined(MP_OBJ_TYPE_GET_SLOT)
    return MP_OBJ_TYPE_GET_SLOT(&usqlite_cursor_type, make_new)(NULL, nxargs, 0, xargs);
    #else
    return usqlite_cursor_type.make_new(NULL, nxargs, 0, xargs);
    #endif
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_connection_execute_obj, 2, 3, usqlite_connection_execute);

// ------------------------------------------------------------------------------

STATIC mp_obj_t usqlite_connection_executemany(mp_obj_t self_in, mp_obj_t sql) {
    usqlite_connection_t *self = MP_OBJ_TO_PTR(self_in);

    mp_obj_t args[3] =
    {
        MP_OBJ_FROM_PTR(self),
        mp_const_true,
        sql
    };

    #if defined(MP_OBJ_TYPE_GET_SLOT)
    return MP_OBJ_TYPE_GET_SLOT(&usqlite_cursor_type, make_new)(NULL, MP_ARRAY_SIZE(args), 0, args);
    #else
    return usqlite_cursor_type.make_new(NULL, MP_ARRAY_SIZE(args), 0, args);
    #endif
}

STATIC MP_DEFINE_CONST_FUN_OBJ_2(usqlite_connection_executemany_obj, usqlite_connection_executemany);

// ------------------------------------------------------------------------------

STATIC int traceCallback(unsigned uMask, void *context, void *p, void *x) {
    usqlite_connection_t *self = (usqlite_connection_t *)context;
    sqlite3_stmt *stmt = (sqlite3_stmt *)p;
    char *xsql = sqlite3_expanded_sql(stmt);
    if (xsql) {
        mp_call_function_1(self->trace_callback, mp_obj_new_str(xsql, strlen(xsql)));
        sqlite3_free(xsql);
    } else {
        const char *sql = sqlite3_sql(stmt);
        mp_call_function_1(self->trace_callback, mp_obj_new_str(sql, strlen(sql)));
    }

    return 0;
}

STATIC mp_obj_t usqlite_connection_set_trace_callback(mp_obj_t self_in, mp_obj_t callback) {
    usqlite_connection_t *self = MP_OBJ_TO_PTR(self_in);

    if (callback == mp_const_none) {
        self->trace_callback = mp_const_none;
        sqlite3_trace_v2(self->db, 0, NULL, NULL);
    } else if (mp_obj_is_callable(callback)) {
        self->trace_callback = callback;
        sqlite3_trace_v2(self->db, SQLITE_TRACE_STMT, traceCallback, self);
    } else {
        mp_raise_msg(&mp_type_ValueError, MP_ERROR_TEXT("Invalid callback"));
    }

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_2(usqlite_connection_set_trace_callback_obj, usqlite_connection_set_trace_callback);

// ------------------------------------------------------------------------------

void usqlite_connection_register(usqlite_connection_t *connection, mp_obj_t cursor) {
    mp_obj_t cursors = MP_OBJ_FROM_PTR(&connection->cursors);
    mp_obj_list_append(cursors, cursor);
}

// ------------------------------------------------------------------------------

void usqlite_connection_deregister(usqlite_connection_t *connection, mp_obj_t cursor) {
    mp_obj_t cursors = MP_OBJ_FROM_PTR(&connection->cursors);
    mp_obj_list_remove(cursors, cursor);
}

// ------------------------------------------------------------------------------

STATIC void usqlite_connection_attr(mp_obj_t self_in, qstr attr, mp_obj_t *dest) {
    usqlite_connection_t *self = (usqlite_connection_t *)self_in;

    if (dest[0] == MP_OBJ_NULL) {
        if ((usqlite_lookup(self_in, attr, dest))) {
            return;
        }

        switch (attr)
        {
            case MP_QSTR_row_type:
                dest[0] = MP_OBJ_NEW_QSTR(self->row_type);
                break;

            case MP_QSTR_total_changes:
                dest[0] = mp_obj_new_int(sqlite3_total_changes(self->db));
                break;
        }
    } else if (dest[1] != MP_OBJ_NULL) {
        switch (attr)
        {
            case MP_QSTR_row_type:
                self->row_type = mp_obj_str_get_qstr(dest[1]);
                dest[0] = MP_OBJ_NULL;
                break;
        }

        // delete/store attribute
    }
}

// ------------------------------------------------------------------------------

STATIC mp_obj_t usqlite_connection_exit(size_t n_args, const mp_obj_t *args) {
    usqlite_logprintf(___FUNC___ "\n");

    usqlite_connection_close(args[0]);

    return mp_const_none;
}

STATIC MP_DEFINE_CONST_FUN_OBJ_VAR_BETWEEN(usqlite_connection_exit_obj, 4, 4, usqlite_connection_exit);

// ------------------------------------------------------------------------------

STATIC const mp_rom_map_elem_t usqlite_connection_locals_dict_table[] =
{
    { MP_ROM_QSTR(MP_QSTR___del__),             MP_ROM_PTR(&usqlite_connection_del_obj) },
    { MP_ROM_QSTR(MP_QSTR___enter__),           MP_ROM_PTR(&mp_identity_obj) },
    { MP_ROM_QSTR(MP_QSTR___exit__),            MP_ROM_PTR(&usqlite_connection_exit_obj) },

    { MP_ROM_QSTR(MP_QSTR_close),               MP_ROM_PTR(&usqlite_connection_close_obj) },
    { MP_ROM_QSTR(MP_QSTR_cursor),              MP_ROM_PTR(&usqlite_connection_cursor_obj) },
    { MP_ROM_QSTR(MP_QSTR_execute),             MP_ROM_PTR(&usqlite_connection_execute_obj) },
    { MP_ROM_QSTR(MP_QSTR_executemany),         MP_ROM_PTR(&usqlite_connection_executemany_obj) },
    { MP_ROM_QSTR(MP_QSTR_set_trace_callback),  MP_ROM_PTR(&usqlite_connection_set_trace_callback_obj) },
    
	{ MP_ROM_QSTR(MP_QSTR_insertSoh),  MP_ROM_PTR(&usqlite_insertSoh_obj) },
	{ MP_ROM_QSTR(MP_QSTR_initializeDatabase),  MP_ROM_PTR(&usqlite_initializeDatabase_obj) },
	{ MP_ROM_QSTR(MP_QSTR_fetchSoh),  MP_ROM_PTR(&usqlite_fetchSoh_obj) },
	{ MP_ROM_QSTR(MP_QSTR_logEvent),  MP_ROM_PTR(&usqlite_logEvent_obj) },
	{ MP_ROM_QSTR(MP_QSTR_insertCommand),  MP_ROM_PTR(&usqlite_insertCommand_obj) },
	{ MP_ROM_QSTR(MP_QSTR_getNextCommand),  MP_ROM_PTR(&usqlite_getNextCommand_obj) },
	{ MP_ROM_QSTR(MP_QSTR_deleteCommand),  MP_ROM_PTR(&usqlite_deleteCommand_obj) },
	{ MP_ROM_QSTR(MP_QSTR_insertPayloadData),  MP_ROM_PTR(&usqlite_insertPayloadData_obj) },
	{ MP_ROM_QSTR(MP_QSTR_fetchPayloadData),  MP_ROM_PTR(&usqlite_fetchPayloadData_obj) },
	{ MP_ROM_QSTR(MP_QSTR_deletePayloadDataID),  MP_ROM_PTR(&usqlite_deletePayloadDataID_obj) },
	{ MP_ROM_QSTR(MP_QSTR_createUplink),  MP_ROM_PTR(&usqlite_createUplink_obj) },
	{ MP_ROM_QSTR(MP_QSTR_fetchDataBlobInto),  MP_ROM_PTR(&usqlite_fetchDataBlobInto_obj) },
	{ MP_ROM_QSTR(MP_QSTR_writeDataBlob),  MP_ROM_PTR(&usqlite_writeDataBlob_obj) },
	{ MP_ROM_QSTR(MP_QSTR_getMissingPacketIds),  MP_ROM_PTR(&usqlite_getMissingPacketIds_obj) },
	{ MP_ROM_QSTR(MP_QSTR_setUplinkPacketReceived),  MP_ROM_PTR(&usqlite_setUplinkPacketReceived_obj) },
	{ MP_ROM_QSTR(MP_QSTR_deleteEntry),  MP_ROM_PTR(&usqlite_deleteEntry_obj) },
	{ MP_ROM_QSTR(MP_QSTR_insertConfig),  MP_ROM_PTR(&usqlite_insertConfig_obj) },
	{ MP_ROM_QSTR(MP_QSTR_fetchConfig),  MP_ROM_PTR(&usqlite_fetchConfig_obj) },
	{ MP_ROM_QSTR(MP_QSTR_getNextDownlink),  MP_ROM_PTR(&usqlite_getNextDownlink_obj) },
	{ MP_ROM_QSTR(MP_QSTR_getNextDownlinkID),  MP_ROM_PTR(&usqlite_getNextDownlinkID_obj) },
	{ MP_ROM_QSTR(MP_QSTR_createDownlink),  MP_ROM_PTR(&usqlite_createDownlink_obj) },
	{ MP_ROM_QSTR(MP_QSTR_createDownlinkEmpty),  MP_ROM_PTR(&usqlite_createDownlinkEmpty_obj) },
	{ MP_ROM_QSTR(MP_QSTR_getTableSize),  MP_ROM_PTR(&usqlite_getTableSize_obj) },
};

MP_DEFINE_CONST_DICT(usqlite_connection_locals_dict, usqlite_connection_locals_dict_table);

// ------------------------------------------------------------------------------

#if defined(MP_DEFINE_CONST_OBJ_TYPE)
MP_DEFINE_CONST_OBJ_TYPE(
    usqlite_connection_type,
    MP_QSTR_Connection,
    MP_TYPE_FLAG_NONE,
    make_new, usqlite_connection_make_new,
    print, usqlite_connection_print,
    attr, usqlite_connection_attr,
    locals_dict, &usqlite_connection_locals_dict
    );
#else
const mp_obj_type_t usqlite_connection_type =
{
    { &mp_type_type },
    .name = MP_QSTR_Connection,
    .print = usqlite_connection_print,
    .make_new = usqlite_connection_make_new,
    .locals_dict = (mp_obj_dict_t *)&usqlite_connection_locals_dict,
    .attr = usqlite_connection_attr,
};
#endif

// ------------------------------------------------------------------------------
