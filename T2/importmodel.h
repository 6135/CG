#ifndef importmodel_h
#define importmodel_h

typedef struct{
    int vertices,positions,texels,normals,faces;
}Model;

typedef struct{
    float x,y,z;
}Vertix;

typedef struct{
    float positions[2000][3];    // XYZ
    float texels[2000][2];          // UV
    float normals[2000][3];        // XYZ
    int faces[2000][12];              // PTN PTN PTN
}ModelDatal;

Vertix vertix(float x, float y, float z);
Model model(int v, int p, int t , int n, int f);
int register_objects(char* filename, const char** object_names);
const char *to_format(const char *word, char *format);
void all_to_format(const char**objs,int n, char*format);
int form_data(char *filename, const char **objs, const char **objsouth, const char** objsoutc);
Model get_object_info(char* modelpath);
void model_info_print(Model a);
void extractOBJdata(char* modelpath, float positions[][3], float texels[][2], float normals[][3], int faces[][12]);
#endif