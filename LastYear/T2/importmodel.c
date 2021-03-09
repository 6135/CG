#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <limits.h>
#include <string.h>
#include "importmodel.h"
#include "our_strings.h"
#include <unistd.h>

Model model(const char* name, int v, int p, int t , int n, int f, int materials){
    Model res;
    strcpy(res.name,name);
    res.vertices = v;
    res.positions = p;
    res.texels = t;
    res.normals = n;
    res.faces = f;
    res.materials = materials;
    return res;
}

Vertix vertix(float x, float y, float z){
    Vertix res;
    res.x=x;
    res.y=y;
    res.z=z;
    return res;
}
Texture reg_texture(const char*name, float Ns,float Ni, float d, float illum,float* Ka,float* Kd, float *Ks,float* Ke){
    Texture res;
    strcpy(res.name,name);
    res.Ns = Ns;  res.Ni = Ni;  res.d = d;  res.illum = illum;
    memcpy(res.Ka,Ka,3);    memcpy(res.Kd,Kd,3);    memcpy(res.Ks,Ks,3);    memcpy(res.Ke,Ke,3);
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

void reverse_all_to_format(const char** objs, int n,const char* prefix){
    const char* word = (const char*) malloc(100*sizeof(char));
    for(int i = 0; i < n; i++) {
        word = str_dup(prefix);
        char buff[100];
        strcpy(buff,word);
        strcat(buff,objs[i]);
        objs[i]=str_dup(buff);
    }
}

int form_data(char *filename,const char** objsn, const char **objs, const char **objsouth, const char** objsoutc, const char** objstxt){
    int n = register_objects(filename,objsn);
    register_objects(filename,objs);
    register_objects(filename,objsouth);
    register_objects(filename,objsoutc);
    register_objects(filename,objstxt);

    all_to_format(objs,n,".obj");
    all_to_format(objsouth,n,".h");
    all_to_format(objsoutc,n,".c");
    all_to_format(objstxt,n,".mtl");
    
    reverse_all_to_format(objs,n,"resources/");
    reverse_all_to_format(objsouth,n,"resources/");
    reverse_all_to_format(objsoutc,n,"resources/");
    reverse_all_to_format(objstxt,n,"resources/");
    return n;
}

int get_object_textures(const char* filepath){
    FILE *fp;
    fp = fopen(filepath,"r");
    char buffer[1000];
    int materials = 0;
    while(str_readline(fp,buffer)!=EOF){
        char substr[3];
        strncpy(substr,buffer,3);
        substr[2]='\0';

        if(strcmp(substr,"ne")==0)
            materials++;
    }
    return materials;
}
Model get_object_info(const char* modelpath,const char* name, const char* mtlpath){
    FILE *fp;
    fp = fopen(modelpath,"r");
    char buffer[1000];
    int p=0,vt=0,vn=0,f=0;
    while(str_readline(fp,buffer)!=EOF){
        //printf("|%s|\n",str_ndup(buffer,2));
        char substr[3];
        strncpy(substr,buffer,3);
        substr[2]='\0';
        
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
    int materials = get_object_textures(mtlpath);
    return model(name,v,p,vt,vn,f,materials);
}
void extractMTLdata(const char* filepath,const char** materials, float** diffuses, float** speculars){
    int m = 0,d = 0,s = 0;
    FILE *fp;
    printf("\tMTL File: %s\n",filepath);
    fp = fopen(filepath,"r");
    
    char* buffer = malloc(1000*sizeof(char));
    while(str_readline(fp,buffer)!=EOF) {
        char substr[3];
        strncpy(substr,buffer,3);
        substr[2]='\0';
        //printf("\t\t...line: %s ...\n",buffer);

        if(strcmp(substr,"ne") == 0) {
            materials[m++]=str_dup(buffer+7);
            //printf("\t\t\t...material added, moving on...\n");
        } else if(strcmp(substr,"Kd") == 0) {
            // Copy line for parsing
            char* l = malloc(strlen(buffer)*sizeof(char));
            memcpy(l, buffer, strlen(buffer)+1);
                    
            strtok(l, " ");
            for(int i=0; i<3; i++)
                diffuses[d][i] = atof(strtok(NULL, " "));
                    
            free(l);
            d++;
        } else if(strcmp(substr,"Ks") == 0) {
            char* l = malloc(strlen(buffer)*sizeof(char));
            memcpy(l, buffer, strlen(buffer)+1);
                    
            strtok(l, " ");
            for(int i=0; i<3; i++)
                speculars[s][i] = atof(strtok(NULL, " "));
                    
            free(l);
            s++;
        }
    }
}

void extractOBJdata(const char* modelpath, float** positions, float** texels, float** normals, int** faces,const char** materials, int m){
    FILE *fp;
    fp = fopen(modelpath,"r");
    char* buffer = malloc(10000 * sizeof(char));
    int p=0,vt=0,vn=0,f=0,res = 0,com = 0,mtl;
    printf("\t... data ...\n");
    while((com = str_readline(fp,buffer))!=EOF){
        res++;
        
        char substr[3];
        strncpy(substr,buffer,3);
        substr[2]='\0';
        //printf("\t\t... LINE %s Subs: %s ...\n",buffer,substr);
        if(strcmp(substr,"us")==0){
            char* l = "usemtl ";
            char* material = malloc(100*sizeof(char));
            strcpy(material,buffer+7);
            //printf("\t\t\t--- material %s\n",material);
            for(int i=0; i<m; i++) {
                if(strcmp(material,materials[i]) == 0)
                    mtl = i;
            }  
            free(l);    free(material);      
        }
        else if(strcmp(substr,"v ")==0){
            char *l = (char *) malloc((strlen(buffer) + 1)*sizeof(char));
            strcpy(l,buffer);
            strtok(l, " ");
            for(int i=0; i<3; i++)
                positions[p][i] = atof(strtok(NULL, " "));
                    
            p++;
            free(l);
        } else if(strcmp(substr,"vt") == 0) {
            char *l = (char *) malloc((strlen(buffer) + 1)*sizeof(char));
            strcpy(l,buffer);                    
            strtok(l, " ");
            for(int i=0; i<2; i++)
                texels[vt][i] = atof(strtok(NULL, " "));
                    
            vt++;
            free(l);
        } else if(strcmp(substr,"vn") == 0) {
            char *l = (char *) malloc((strlen(buffer) + 1)*sizeof(char));
            strcpy(l,buffer);                    
            strtok(l, " ");
            for(int i=0; i<3; i++)
                normals[vn][i] = atof(strtok(NULL, " "));
                    
            vn++;
            free(l);
        } else if(strcmp(substr,"f ") == 0) {
            char *l = (char *) malloc((strlen(buffer) + 1)*sizeof(char));
            strcpy(l,buffer);                    
            strtok(l, " ");
            for(int i=0; i<9; i++)
                faces[f][i] = atof(strtok(NULL, " /"));
            faces[f++][9] = mtl;
            free(l);
        }
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
    fprintf(fp,"// Vertices: %d\n\n",a.vertices); 
    
    // Write declarations
    fprintf(fp,"const int %sVertices;\n", a.name);
    fprintf(fp,"const float %sPositions[%d];\n",a.name,a.vertices*3); 
    fprintf(fp,"const float %sTexels[%d];\n",a.name,a.vertices*2); 
    fprintf(fp,"const float %sNormals[%d];\n\n",a.name,a.vertices*3); 

    fprintf(fp,"const int %sMaterials;\n",a.name); 
    fprintf(fp,"const int %sFirsts[%d];\n",a.name,a.materials);    
    fprintf(fp,"const int %sCounts[%d];\n\n",a.name,a.materials); 

    fprintf(fp,"const float %sDiffuses[%d][3];\n",a.name,a.materials); 
    fprintf(fp,"const float %sSpeculars[%d][3];\n\n",a.name,a.materials); 

    fprintf(fp,"void render_object_%s();\n",a.name);

    fclose(fp);
}

void writeCvertices(const char* filename, Model a){
    FILE *fp;
    fp = fopen(filename,"a");
    
    fprintf(fp,"//%s %s\n","This is .c file for the model:",a.name);

    fprintf(fp,"#include \"%s.h\"\n",a.name);
    fprintf(fp,"const int %sVertices = %d;\n",a.name,a.vertices);
    fclose(fp);
}

void writeCpositions(const char *filename,Model a, int** faces, float** positions, int* counts)
{    

    FILE *fp;
    fp = fopen(filename,"a");

    fprintf(fp,"const float %sPositions[%d] = {\n",a.name,a.vertices*3);
    for(int j=0;j<a.materials;j++) {
        counts[j]=0;
        for(int i=0;i<a.faces;i++){
            if(faces[i][9]==j) {
                int va = faces[i][0] -1;
                int vb = faces[i][3] -1;
                int vc = faces[i][6] -1;

                fprintf(fp,"%f, %f, %f,\n",positions[va][0],positions[va][1],positions[va][2]);
                fprintf(fp,"%f, %f, %f,\n",positions[vb][0],positions[vb][1],positions[vb][2]);
                fprintf(fp,"%f, %f, %f,\n",positions[vc][0],positions[vc][1],positions[vc][2]);
                counts[j]+=3;
            }
        }
    }

    fprintf(fp,"};\n");
    fclose(fp);
}

void writeCtexels(const char* filename,Model a, int** faces, float** texels)
{
    FILE *fp;
    fp = fopen(filename,"a");

    fprintf(fp,"const float %sTexels[%d] = {\n",a.name,a.vertices*2);
    for(int j = 0 ;j<a.materials;j++)
        for(int i = 0; i < a.faces; i++){
            if(faces[i][9]==j){
                int vta = faces[i][1] - 1;
                int vtb = faces[i][4] - 1;
                int vtc = faces[i][7] - 1;

                fprintf(fp,"%f, %f,\n",texels[vta][0],texels[vta][1]);
                fprintf(fp,"%f, %f,\n",texels[vtb][0],texels[vtb][1]);
                fprintf(fp,"%f, %f,\n",texels[vtc][0],texels[vtc][1]);
            }
        }
    fprintf(fp,"};\n");
    fclose(fp);
}

void writeCnormals(const char* filename,Model a, int** faces, float** normals)
{
    FILE *fp;
    fp = fopen(filename,"a");

    fprintf(fp,"const float %sNormals[%d] = {\n",a.name,a.vertices*3);
    for(int j=0;j<a.materials;j++)
        for(int i = 0; i < a.faces; i++){
            if(faces[i][9]==j){
                int vna = faces[i][2] - 1;
                int vnb = faces[i][5] - 1;
                int vnc = faces[i][8] - 1;

                fprintf(fp,"%f, %f, %f,\n",normals[vna][0],normals[vna][1],normals[vna][2]);
                fprintf(fp,"%f, %f, %f,\n",normals[vnb][0],normals[vnb][1],normals[vnb][2]);
                fprintf(fp,"%f, %f, %f,\n",normals[vnc][0],normals[vnc][1],normals[vnc][2]);
            }
        }

    fprintf(fp,"};\n");
    fclose(fp);
}
void writeCmaterials(const char* filepath, Model a, int* firsts, int* counts)
{
    FILE *fp;
    fp = fopen(filepath,"a");
    
    // Materials
    fprintf(fp,"const int %sMaterials = %d;\n",a.name,a.materials);
    
    // Firsts
    fprintf(fp,"const int %sFirsts[%d] = {\n",a.name,a.materials);
    for(int i=0; i<a.materials; i++) {
        if(i == 0)
            firsts[i] = 0;
        else
            firsts[i] = firsts[i-1]+counts[i-1];
        
        fprintf(fp,"%d,\n",firsts[i]);
    }
    fprintf(fp,"};\n");
    
    // Counts
    fprintf(fp,"const int %sCounts[%d] = {\n",a.name,a.materials);
    for(int i=0; i<a.materials; i++)
      fprintf(fp,"%d,\n",counts[i]);

    fprintf(fp,"};\n");
   
    fclose(fp);
}

float** float_init(int size, int default_size){
    float **a = malloc(size*sizeof(float*));

    for(int i = 0; i < size; i++)
        a[i]=malloc(default_size*sizeof(float));
    return a;
}

int** int_init(int size, int default_size){
    int **a = malloc(size*sizeof(int*));

    for(int i = 0; i < size; i++)
        a[i]=malloc(default_size*sizeof(int));
    return a;    
}

void modelData(Model a,const char* filepath,const char* header,const char* cont,const char* mtlFile){
    float** positions = float_init(a.positions,3);
    float** texels = float_init(a.texels,2);
    float** normals = float_init(a.normals,3);
    int** faces = int_init(a.faces,10);
    
    const char** materials = malloc(10000*sizeof(char*));
    float** diffuses = float_init(a.materials,3);
    float** speculars = float_init(a.materials,3);
    printf("Writting header...\n");
    if(access(header,R_OK)==-1)
        writeH(header,a);

    printf("Header done, now: extracting!\n");
    extractMTLdata(mtlFile,materials,diffuses,speculars);
    printf("\t...mtl done...\n");
    extractOBJdata(filepath, positions, texels, normals, faces,materials,a.materials);
    printf("\t...data done...\n");

    int firsts[a.materials];	// Starting vertex
    int counts[a.materials];	// Number of vertices

    if(access(cont,R_OK)==-1) {
        writeCvertices(cont,a);
        writeCpositions(cont,a,faces,positions,counts);
        writeCtexels(cont,a,faces,texels);
        writeCnormals(cont,a,faces,normals);
        writeCmaterials(cont,a,firsts,counts);
        render_object_c(a,cont);
    }
}

void render_object_c(Model a,const char* cont){
    FILE *fp;
    fp=fopen(cont,"a");
    

    fprintf(fp,"void render_object_%s() {\n\n",a.name);
    fprintf(fp,"\tint size = (sizeof(%sPositions)/sizeof(%sPositions[0]));\n",a.name,a.name);
    fprintf(fp,"\tglBegin(GL_TRIANGLES); {\n");
    fprintf(fp,"\t\tfor(int i=0;i<size;i+=3){\n");
    fprintf(fp,"\t\t\tglNormal3f(%sNormals[i],%sNormals[i+1],%sNormals[i+2]);\n",a.name,a.name,a.name);
    fprintf(fp,"\t\t\tglVertex3f(%sPositions[i],%sPositions[i+1],%sPositions[i+2]);\n\t\t}\n",a.name,a.name,a.name);
    fprintf(fp,"\t}\tglEnd();\n}\n");

    fclose(fp);
}

void texture_render_c(Model a,const char* cont){
    FILE *fp;
    fp=fopen(cont,"a");
    

    fprintf(fp,"void texture_render_%s() {\n\n",a.name);
    fprintf(fp,"\tint size = (sizeof(%sTextels)/sizeof(%sTextels[0]));\n",a.name,a.name);

    fclose(fp);
}

