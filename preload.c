/// Since ssh requires `getpwuid` to succeed but jenkins sets the uid/gid
/// without creating a named user, we have to fake that call.

#include <pwd.h>
#include <stdlib.h>
#include <unistd.h>

static struct passwd g_passwd = {
    .pw_name = "jenkins",
    .pw_passwd = "",
    .pw_uid = 0,
    .pw_gid = 0,
    .pw_gecos = "jenkins",
    .pw_dir = NULL,
    .pw_shell = "/bin/sh",
};

struct passwd *getpwuid(uid_t uid) {
    g_passwd.pw_uid = getuid();
    g_passwd.pw_gid = getgid();
    g_passwd.pw_dir = getenv("HOME");
    return &g_passwd;
}
