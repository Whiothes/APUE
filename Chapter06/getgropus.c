#include <grp.h>
#include <stdio.h>
#include <unistd.h>
#include <uuid/uuid.h>

int main() {
    int           grpmax = sysconf(_SC_NGROUPS_MAX);
    gid_t         grouplist[grpmax];
    struct group *grp = NULL;

    getgroups(grpmax, grouplist);

    for (int i = 0; i < grpmax; ++i) {
        grp = getgrgid(grouplist[i]);
        printf("%d\t%s\n", grouplist[i], grp->gr_name);
    }
}
