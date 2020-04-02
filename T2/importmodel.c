#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include "importmodel.h"
#include "our_strings.h"

Model model(int v, int p, int t , int n, int f){
    Model res;
    res.vertices = v;
    res.positions = p;
    res.texels = t;
    res.normals = n;
    res.faces = f;
    return res;
}
Vertix vertix(float x, float y, float z){
    Vertix res;
    res.x=x;
    res.y=y;
    res.z=z;
    return res;
}
int register_objects(char* filename, const char** object_names){
    FILE *f;
    f = fopen(filename,"r");
    return strings_readwords(f,object_names);

}

const char *to_format(const char *word, char *format){
    char wordb[100];
    strcpy(wordb,word);
    strcat(wordb,format);
    return str_dup(wordb);
}

void all_to_format(const char** objs,int n, char*format){
    for(int i = 0; i<n ;i++){
        objs[i]=str_dup(to_format(objs[i],format));
    }
}

int form_data(char *filename, const char **objs, const char **objsouth, const char** objsoutc){
    int n = register_objects(filename,objs);
    register_objects(filename,objsouth);
    register_objects(filename,objsoutc);
    all_to_format(objs,n,".obj");
    all_to_format(objsouth,n,".h");
    all_to_format(objsoutc,n,".c");
    return n;
}

void model_info_print(Model a){
    printf("ver: %d pos: %d tex: %d norm: %d f: %d",a.vertices,a.positions,a.texels,a.normals,a.faces);
}

Model get_object_info(char* modelpath){
    FILE *fp;
    fp = fopen(modelpath,"r");
    char buffer[1000];
    int p=0,vt=0,vn=0,f=0;
    while(str_readline(fp,buffer)!=EOF){
        printf("|%s|\n",str_ndup(buffer,2));
        const char* substr = str_ndup(buffer,2);

        if(strcmp(substr,"v ")==0){
            p++;
        } else if(strcmp(substr,"vt")==0){
            vt++;
        } else if(strcmp(substr,"vn")==0){
           vn++;
        } else if(strcmp(substr,"f ")==0){
            f++;
        }
    }
    int v = f*4;
    fclose(fp);
    return model(v,p,vt,vn,f);
}

void extractOBJdata(char* modelpath, float positions[][3], float texels[][2], float normals[][3], int faces[][12]){
    FILE *fp;
    fp = fopen(modelpath,"r");
    char buffer[1000];
    int p=0,vt=0,vn=0,f=0;
    while(str_readline(fp,buffer)!=EOF){
        //printf("|%s|\n",str_ndup(buffer,2));
        const char* substr = str_ndup(buffer,2);

        if(strcmp(substr,"v ")==0){
            char *l = (char *) malloc(strlen(buffer) + 1);
            strcpy(l,buffer);
            strtok(l, " ");
            for(int i=0; i<3; i++)
                positions[p][i] = atof(strtok(NULL, " "));
                    
            p++;
            free(l);
        } else if(strcmp(substr,"vt") == 0) {
            char *l = (char *) malloc(strlen(buffer) + 1);
            strcpy(l,buffer);                    
            strtok(l, " ");
            for(int i=0; i<2; i++)
                texels[vt][i] = atof(strtok(NULL, " "));
                    
            vt++;
            free(l);
        } else if(strcmp(substr,"vn") == 0) {
            char *l = (char *) malloc(strlen(buffer) + 1);
            strcpy(l,buffer);                    
            strtok(l, " ");
            for(int i=0; i<3; i++)
                normals[vn][i] = atof(strtok(NULL, " "));
                    
            vn++;
            free(l);
        } else if(strcmp(substr,"f ") == 0) {
            char *l = (char *) malloc(strlen(buffer) + 1);
            strcpy(l,buffer);                    
            strtok(l, " ");
            for(int i=0; i<12; i++)
                faces[f][i] = atof(strtok(NULL, " /"));
       
            f++;
            free(l);
        }
        ;
    }
    fclose(fp);

}