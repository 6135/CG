//This is header file for the model: house
// Positions: 251
// vt's: 633
// Normals: 72
// Faces: 440
// Vertices: 1320

const int houseVertices;
const float housePositions[3960];
const float houseTexels[2640];
const float houseNormals[3960];

const int houseMaterials;
const int houseFirsts[3];
const int houseCounts[3];

const float houseDiffuses[3][3];
const float houseSpeculars[3][3];

const char *images[3]={"window.jpg","brick.jpg","wood.png"};
GLint width, height;

void render_object_house();
unsigned int texture_object_house(char *image);
