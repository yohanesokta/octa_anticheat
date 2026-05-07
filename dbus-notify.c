#include <dbus-1.0/dbus/dbus.h>
#include <stdio.h>
#include <stdint.h>

int main() {
    DBusError err;
    DBusConnection* conn;
    DBusMessage* msg;

    dbus_error_init(&err);

    // connect ke session bus
    conn = dbus_bus_get(DBUS_BUS_SESSION, &err);

    if (dbus_error_is_set(&err)) {
        fprintf(stderr, "DBus Error: %s\n", err.message);
        dbus_error_free(&err);
        return 1;
    }

    if (!conn) {
        fprintf(stderr, "Failed connect DBus\n");
        return 1;
    }

    // buat method call
    msg = dbus_message_new_method_call(
        "org.freedesktop.Notifications",
        "/org/freedesktop/Notifications",
        "org.freedesktop.Notifications",
        "Notify"
    );

    if (!msg) {
        fprintf(stderr, "Message NULL\n");
        return 1;
    }

    // argument
    const char* app_name = "OCTA";
    uint32_t replaces_id = 0;
    const char* app_icon = "";
    const char* summary = "OCTA Anti Cheat";
    const char* body = "Cheat detected!";
    int32_t timeout = 5000;

    DBusMessageIter args;

    dbus_message_iter_init_append(msg, &args);

    dbus_message_iter_append_basic(
        &args,
        DBUS_TYPE_STRING,
        &app_name
    );

    dbus_message_iter_append_basic(
        &args,
        DBUS_TYPE_UINT32,
        &replaces_id
    );

    dbus_message_iter_append_basic(
        &args,
        DBUS_TYPE_STRING,
        &app_icon
    );

    dbus_message_iter_append_basic(
        &args,
        DBUS_TYPE_STRING,
        &summary
    );

    dbus_message_iter_append_basic(
        &args,
        DBUS_TYPE_STRING,
        &body
    );

    // actions array kosong
    DBusMessageIter actions;

    dbus_message_iter_open_container(
        &args,
        DBUS_TYPE_ARRAY,
        "s",
        &actions
    );

    dbus_message_iter_close_container(
        &args,
        &actions
    );

    // hints dict kosong
    DBusMessageIter hints;

    dbus_message_iter_open_container(
        &args,
        DBUS_TYPE_ARRAY,
        "{sv}",
        &hints
    );

    dbus_message_iter_close_container(
        &args,
        &hints
    );

    dbus_message_iter_append_basic(
        &args,
        DBUS_TYPE_INT32,
        &timeout
    );

    // kirim message
    if (!dbus_connection_send(conn, msg, NULL)) {
        fprintf(stderr, "Failed send message\n");
        return 1;
    }

    dbus_connection_flush(conn);

    dbus_message_unref(msg);

    printf("Notification sent!\n");

    return 0;
}
