#define MIN_NR_VERTEX 20
#define NR_COLORS 24 

typedef struct vec {
  float x;
  float y;
  float z;
  float normalize;
} Vec;

struct coordinate {
  GLfloat x;
  GLfloat y;
  GLfloat z;
};

struct color {
  GLfloat r;
  GLfloat g;
  GLfloat b;
};

typedef struct object {
  int nrPoints;
  float angle;
  struct coordinate point[MIN_NR_VERTEX];    
  struct color c[NR_COLORS];
} Object;


