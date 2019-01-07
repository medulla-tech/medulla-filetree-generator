 
#include <iostream>

#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <linux/limits.h>
#include <sys/stat.h>

using namespace std;


//void listdir(const char *name, int indent, FILE * fp, string& result)
void listdir(const char *name, int indent, FILE * fp)
{
    DIR *dir;
    struct dirent *entry;
    char espacea[5] = " {";
    char path[1024];
    char namefile[2024];
    if (!(dir = opendir(name)))
        return;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            // folders 
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                //pass name file  ".." et "." file
                continue;
            //create absolue name directory
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            // uncomment line for display directory to stdout
            //printf("%*s[%s]\n", indent, " ", entry->d_name);
            //prepare ecriture file.
            snprintf(namefile, sizeof(namefile),"%s\"text\" : \"%s\", \"children\" : [",espacea, entry->d_name);
            fprintf(fp,"%s\"text\" : \"%s\", \"children\" : [",espacea, entry->d_name);
            //result += string(namefile);
            strcpy(espacea,",{");
            // result =  result + namefile;
            //cout << result << endl;
            //listdir(path, indent + 2, fp, result);
            listdir(path, indent + 2, fp);
            fprintf(fp, "]}");
            //result += "]";
        } else {
            //file
            // uncomment line for display file name to stdout
            //printf("%*s- %s\n", indent, "", entry->d_name);
        }
    }
    closedir(dir);
}
bool dir_exist(char * path){
    struct stat st;
    if(stat(path,&st) == 0)
        if(st.st_mode & S_IFDIR != 0)
            return true;
    return false;
}
//result pas utilise, mais a utiliser si on veut le fichier genere dans une varaible. 
int main(int argc, char* argv[]) {
    char outfilename[PATH_MAX];
    char filename[PATH_MAX];
    
    if (argc == 1 ) {
        fprintf(stderr, "usage : %s \"dir_start\" [file result json]", argv[0]);
        return -1;
    }

    if (!dir_exist(argv[1])){
        fprintf(stderr, "error arg1 (%s) is not folder", argv[1]);
        return -1;
    }
    if (argc < 3) {
        strcpy(outfilename,"/tmp/file.txt");
    }
    else{
        strcpy(outfilename, argv[2]);
    }
    string dede;
    FILE * fp;
    //string result = "{";
    fp = fopen (outfilename, "w+");
    if (argv[1][0] == '/'){
        strcpy(filename, &argv[1][1]); 
    }else{
        strcpy(filename, argv[1]); 
    }
    fprintf(fp,"{ \"text\" : \"%s\", \"children\" : [",filename);
    //listdir("/", 0, fp, result);
    listdir(argv[1], 0, fp);
    fprintf(fp, "]}");
    fclose(fp);
    //result += "}";
    // cout << result << endl;
    return 0;
}


