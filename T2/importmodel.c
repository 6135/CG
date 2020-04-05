#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include "importmodel.h"
#include "our_strings.h"
#include <unistd.h>

Model model(char* name, int v, int p, int t , int n, int f){
    Model res;
    strcpy(res.name,name);
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

int form_data(char *filename,const char** objsn, const char **objs, const char **objsouth, const char** objsoutc){
    int n = register_objects(filename,objsn);
    register_objects(filename,objs);
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

Model get_object_info(const char* modelpath, char* name){
    FILE *fp;
    fp = fopen(modelpath,"r");
    char buffer[1000];
    int p=0,vt=0,vn=0,f=0;
    while(str_readline(fp,buffer)!=EOF){
        //printf("|%s|\n",str_ndup(buffer,2));
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
    int v = f*3;
    fclose(fp);
    return model(name,v,p,vt,vn,f);
}

void extractOBJdata(const char* modelpath, float positions[][3], float texels[][2], float normals[][3], int faces[][9]){
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

void writeH(const char* filename, Model a)
{
    // 2
    // Create H file
    FILE *fp;
    fp = fopen(filename,"w");
    
    fprintf(fp,"//%s %s\n","This is header file for the model:",a.name);

    // Write statistics
    fprintf(fp,"// Positions: %d\n", a.positions);
    fprintf(fp,"// vt's: %d\n",a.texels); 
    fprintf(fp,"// Normals: %d\n",a.normals); 
    fprintf(fp,"// Faces: %d\n",a.faces); 
    fprintf(fp,"// Vertices: %d\n",a.vertices); 
    
    // Write declarations
    fprintf(fp,"const int %sVertices;\n", a.name);
    fprintf(fp,"const float %sPositions[%d];\n",a.name,a.vertices*3); 
    fprintf(fp,"const float %sTexels[%d];\n",a.name,a.vertices*2); 
    fprintf(fp,"const float %sNormals[%d];\n",a.name,a.vertices*3); 
    
    fclose(fp);
}

void writeCvertices(const char* filename, Model a){
    FILE *fp;printf("Im here");
    fp = fopen(filename,"a");
    
    fprintf(fp,"//%s %s\n","This is .c file for the model:",a.name);

    fprintf(fp,"#include \"%s.h\"\n",a.name);
    fprintf(fp,"const int %sVertices = %d;\n",a.name,a.vertices);
    fclose(fp);
}

void writeCpositions(const char *filename,Model a, int faces[][9], float positions[][3])
{    

    FILE *fp;
    fp = fopen(filename,"a");

    fprintf(fp,"const float %sPositions[%d] = {\n",a.name,a.vertices*3);
    for(int i=0;i<a.faces;i++){
        int va = faces[i][0] -1;
        int vb = faces[i][3] -1;
        int vc = faces[i][6] -1;

        fprintf(fp,"%f, %f, %f,\n",positions[va][0],positions[va][1],positions[va][2]);
        fprintf(fp,"%f, %f, %f,\n",positions[vb][0],positions[vb][1],positions[vb][2]);
        fprintf(fp,"%f, %f, %f,\n",positions[vc][0],positions[vc][1],positions[vc][2]);
    }

    fprintf(fp,"};\n");
    fclose(fp);
}

void writeCtexels(const char* filename,Model a, int faces[][9], float texels[][2])
{
    FILE *fp;
    fp = fopen(filename,"a");

    fprintf(fp,"const float %sTexels[%d] = {\n",a.name,a.vertices*2);

    for(int i = 0; i < a.faces; i++){
        int vta = faces[i][1] - 1;
        int vtb = faces[i][4] - 1;
        int vtc = faces[i][7] - 1;

        fprintf(fp,"%f, %f,\n",texels[vta][0],texels[vta][1]);
        fprintf(fp,"%f, %f,\n",texels[vtb][0],texels[vtb][1]);
        fprintf(fp,"%f, %f,\n",texels[vtc][0],texels[vtc][1]);
    }
    fprintf(fp,"};\n");
    fclose(fp);
}

void writeCnormals(const char* filename,Model a, int faces[][9], float normals[][3])
{
    FILE *fp;
    fp = fopen(filename,"a");

    fprintf(fp,"const float %sNormals[%d] = {\n",a.name,a.vertices*3);

    for(int i = 0; i < a.faces; i++){

        int vna = faces[i][2] - 1;
        int vnb = faces[i][5] - 1;
        int vnc = faces[i][8] - 1;

        fprintf(fp,"%f, %f, %f,\n",normals[vna][0],normals[vna][1],normals[vna][2]);
        fprintf(fp,"%f, %f, %f,\n",normals[vnb][0],normals[vnb][1],normals[vnb][2]);
        fprintf(fp,"%f, %f, %f,\n",normals[vnc][0],normals[vnc][1],normals[vnc][2]);

    }

    fprintf(fp,"};\n");
    fclose(fp);
}

void modelData(Model a,const char* filepath,const char* header,const char* cont){
    float positions[a.positions][3];    // XYZ
    float texels[a.texels][2];          // UV
    float normals[a.normals][3];        // XYZ
    int faces[a.faces][9];              // PTN PTN PTN PTN
    extractOBJdata(filepath, positions, texels, normals, faces);
    
    if(access(header,R_OK)==-1)
        writeH(header,a);

    if(access(cont,R_OK)==-1) {
        writeCvertices(cont,a);
        writeCpositions(cont,a,faces,positions);
        writeCtexels(cont,a,faces,texels);
        writeCnormals(cont,a,faces,normals);
    }
}