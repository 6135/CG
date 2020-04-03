#ifndef importmodel_h
#define importmodel_h

typedef struct{
    int vertices,positions,texels,normals,faces;
    char name[100];
}Model;

typedef struct{
    float x,y,z;
}Vertix;

typedef struct{
    float positions[0000][3];    // XYZ
    float texels[0000][2];          // UV
    float normals[0000][3];        // XYZ
    int faces[0000][12];              // PTN PTN PTN PTN
}ModelDatal;

Vertix vertix(float x, float y, float z);
Model model(char* name, int v, int p, int t , int n, int f);
int register_objects(char* filename, const char** object_names);
const char *to_format(const char *word, char *format);
void all_to_format(const char**objs,int n, char*format);
int form_data(char *filename,const char** objsn, const char **objs, const char **objsouth, const char** objsoutc);
Model get_object_info(const char* modelpath, char* name);
void model_info_print(Model a);
void extractOBJdata(const char* modelpath, float positions[][3], float texels[][2], float normals[][3], int faces[][12]);
void writeH(const char* filename, Model a);
void writeCvertices(const char* filename, Model a);
void writeCpositions(const char *filename, Model a, int faces[][12], float positions[][3]);
void writeCtexels(const char* fp,Model a, int faces[][12], float texels[][2]);
void writeCnormals(const char* fp,Model a, int faces[][12], float normals[][3]);
#endif