//This is header file for the model: cube
// Positions: 20
// vt's: 26
// Normals: 7
// Faces: 28
// Vertices: 84

const int cubeVertices;
const float cubePositions[252];
const float cubeTexels[168];
const float cubeNormals[252];

const int cubeMaterials;
const int cubeFirsts[2];
const int cubeCounts[2];

const float cubeDiffuses[2][3];
const float cubeSpeculars[2][3];

void render_object_cube();
