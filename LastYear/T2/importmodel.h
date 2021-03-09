#ifndef importmodel_h
#define importmodel_h
#define NELEMS(x) (sizeof(x)/sizeof(x[0]))



typedef struct{
    float x,y,z;
}Vertix;

typedef struct{
    char name[100],path[100];
    float Ns,Ni,d,illum;
    float Ka[3];
    float Kd[3];
    float Ks[3];
    float Ke[3];
}Texture;
typedef struct{
    int vertices,positions,texels,normals,faces,materials;
    char name[100];
}Model;
typedef struct{
    float positions[10000][3];    // XYZ
    float texels[10000][2];          // UV
    float normals[10000][3];        // XYZ
    int faces[10000][9];              // PTN PTN PTN PTN
}ModelDatal;

Vertix vertix(float x, float y, float z);
Model model(const char* name, int v, int p, int t , int n, int f, int materials);
Texture reg_texture(const char*name, float Ns,float Ni, float d, float illum,float* Ka,float* Kd, float *Ks,float* Ke);
int register_objects(char* filename, const char** object_names);
const char *to_format(const char *word, char *format);
void all_to_format(const char**objs,int n, char*format);
int form_data(char *filename,const char** objsn, const char **objs, const char **objsouth, const char** objsoutc, const char** objstxt);
int get_object_textures(const char* filepath);
Model get_object_info(const char* modelpath,const char* name, const char* mtlpath);
void model_info_print(Model a);
void extractOBJdata(const char* modelpath, float** positions, float** texels, float** normals, int** faces,const char** materials, int m);
void writeH(const char* filename, Model a);
void writeCvertices(const char* filename, Model a);
void writeCpositions(const char *filename, Model a, int** faces, float** positions, int* counts);
void writeCtexels(const char* filename,Model a, int** faces, float** texels);
void writeCnormals(const char* filename,Model a, int** faces, float** normals);
void writeCmaterials(const char* filepath, Model a, int* firsts, int* counts);
void modelData(Model a,const char* filepath,const char* header,const char* cont,const char* mtlFile);
void render_object_c(Model a,const char* cont);
void reverse_all_to_format(const char** objs, int n,const char* prefix);
void extractMTLdata(const char* filepath, const char** materials, float** diffuses, float** speculars);

#endif