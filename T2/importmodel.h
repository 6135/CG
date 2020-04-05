#ifndef importmodel_h
#define importmodel_h
#define NELEMS(x) (sizeof(x)/sizeof(x[0]))

typedef struct{
    int vertices,positions,texels,normals,faces;
    char name[100];
}Model;

typedef struct{
    float x,y,z;
}Vertix;

typedef struct{
    float positions[10000][3];    // XYZ
    float texels[10000][2];          // UV
    float normals[10000][3];        // XYZ
    int faces[10000][9];              // PTN PTN PTN PTN
}ModelDatal;

Vertix vertix(float x, float y, float z);
Model model(char* name, int v, int p, int t , int n, int f);
int register_objects(char* filename, const char** object_names);
const char *to_format(const char *word, char *format);
void all_to_format(const char**objs,int n, char*format);
int form_data(char *filename,const char** objsn, const char **objs, const char **objsouth, const char** objsoutc);
Model get_object_info(const char* modelpath, char* name);
void model_info_print(Model a);
void extractOBJdata(const char* modelpath, float positions[][3], float texels[][2], float normals[][3], int faces[][9]);
void writeH(const char* filename, Model a);
void writeCvertices(const char* filename, Model a);
void writeCpositions(const char *filename, Model a, int faces[][9], float positions[][3]);
void writeCtexels(const char* filename,Model a, int faces[][9], float texels[][2]);
void writeCnormals(const char* filename,Model a, int faces[][9], float normals[][3]);
void modelData(Model a,const char* filepath,const char* header,const char* cont);
void render_object_c(Model a,const char* cont);

#endif