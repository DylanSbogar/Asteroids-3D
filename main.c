#include <stdlib.h>
#include <stdio.h>
#include "main.h"

int screenWidth = 0;
int screenHeight = 0;

int roundNum = 0;

int currentTime = 0;
float previousTime = 0.0;

bool firstMouse = true;
bool gameOver = false;
bool roundOver;

static DrawObject drawObject;

keyHandler kh;
camera cam;
ship player;
// bullet testBullet;
bullet bullets[MAX_BULLETS];
asteroid asteroids[MAX_ROUNDS];

void placeCamera(camera *camera) {
    gluLookAt(camera->pos.x, camera->pos.y, camera->pos.z,
        player.pos.x + camera->front.x, player.pos.y + camera->front.y, player.pos.z + camera->front.z,
        0, 1, 0);
}

void onReshape(int w, int h) {
    glViewport(0, 0, w, h);

    screenWidth = w;
    screenHeight = h;

    const double aspectRatio = (double)w / (double)h;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(90.0, aspectRatio, 1.0, 2000.0);

    

    // Initialise the random number generator.
    time_t t;
    srand((unsigned) time(&t));

    initCamera(&cam);
    initShip(&player);

    for(int i = 0; i < roundNum; i++) {
        initAsteroid(&asteroids[i], &player);
    }
}

void initLighting() {
    float ambient[] = { 1.0, 1.0, 1.0, 1.0 };
    float diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    float specular[] = { 1.0, 1.0, 1.0, 1.0 };

    glEnable(GL_LIGHTING);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
    glEnable(GL_LIGHT0);
}

void renderFrame() {
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

     //TODO: Put draw methods here.
    placeCamera(&cam);
    shipWarning(&player);
    drawArena();
    
    // drawAxes();
    drawShip(&player, cam.yaw, cam.roll, cam.pitch);

    Draw(&drawObject);

    for(int i = 0; i < roundNum; i++) {
        if(asteroids[i].alive) {
            drawAsteroid(&asteroids[i]);
        }
    }

    for(int i = 0; i < MAX_BULLETS; i++) {
        if(bullets[i].activated) {
            drawBullet(&bullets[i]);
        }
    }
}

void updateCameraPosition(camera *camera, float deltaTime) {
    camera->pos.x = player.pos.x - 20 * cos(DEG_TO_RAD(camera->yaw));
    camera->pos.y = player.pos.y + 10;
    camera->pos.z = player.pos.z - 20 * sin(DEG_TO_RAD(camera->yaw));
}

void onDisplay() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);

    // Handles all drawing functionality.
    renderFrame();

    glutSwapBuffers();

    // Check for errors.
    int err;
    while ((err = glGetError()) != GL_NO_ERROR)
        printf("Error: %s\n", gluErrorString(err));
}

void onIdle() {
    // Calculate deltaTime.
    currentTime = glutGet(GLUT_ELAPSED_TIME);
    float deltaTime = currentTime - previousTime;
    previousTime = currentTime;

    // Perform idle checks for when the player is not moving (moving camera, asteroids)
    moveCamera(&cam, deltaTime, 1, &player.pos);
    updateGameState(&cam, &player, deltaTime);

    // Move all the asteroids.
    for(int i = 0; i < roundNum; i++) {
        if(asteroids[i].alive) {
            moveAsteroid(&asteroids[i], deltaTime, roundNum);
        }
    }
    glutPostRedisplay();
}

void updateGameState(camera *camera, ship *ship, float deltaTime) {
    if(kh.movingForward) {
        moveShip(&player, deltaTime, 1);
        moveCamera(&cam, deltaTime, 1, &ship->pos);
    }
    if(kh.movingBackward) {
        moveShip(&player, deltaTime, -1);
        moveCamera(&cam, deltaTime, -1, &ship->pos);
    }
    if(kh.restartGame) {
        initGame();
    }
    if(shipCollision(&player)) {
        initGame();
    }
    for(int i = 0; i < MAX_BULLETS; i++) {
        if(bullets[i].activated) {
            moveBullet(&bullets[i], deltaTime);
        }
        
        // Check if the bullet collides with the wall.
        bulletCollision(&bullets[i]);
    }

    // Used to calculate when the round ends.
    roundOver = true;

    for(int j = 0; j < roundNum; j++) {
        // 'Activate' asteroids as they enter the arena, and perform wall collision checks.
        checkActivated(&asteroids[j]);

        for(int d = 0; d < roundNum; d++) {
            if (d != j) {
                if(asteroids[d].alive) {
                    asteroidBouncing(&asteroids[j], &asteroids[d]);
                }
            }
        }

        // Check whether any of the asteroids are ready to bounce off the walls.
        asteroidWallCollision(&asteroids[j]);
        
        for(int k = 0; k < MAX_BULLETS; k++) {
            // Check whether a bullet has destroyed any of the asteroids.
            bulletAsteroidCollision(&bullets[k], &asteroids[j]);
        }
   
        // If the ship has collided with an asteroid, end the game.
        if(asteroidShipCollision(&player, &asteroids[j])) {
            // TODO: Replace with restartGame().
            initGame();
        }

        // If any asteroids are still alive, the round is not over.
        if(asteroids[j].alive) {
            roundOver = false;
        }
    }

    // If all asteroids are dead and the round is over.
    if(roundOver) {
        roundNum++;

        // TODO: Wait 5 seconds before starting the next wave.

        // Create x amount of new asteroids corresponding with the round number.
        for(int i = 0; i < roundNum; i++)
        {
            initAsteroid(&asteroids[i], &player);
        }
    }
}

void onKeyPress(unsigned char key, int x, int y) {
    switch(toupper(key)) {
        case 'W':
            kh.movingForward = true;
            kh.movingBackward = false;
            break;
        case 'A':
            kh.rollingLeft = true;
            kh.rollingRight = false;
            break;
        case 'S':
            kh.movingBackward = true;
            kh.movingForward = false;
            break;
        case 'D':
            kh.rollingRight = true;
            kh.rollingLeft = false;
            break;
        case 'R':
            gameOver = false;
            kh.restartGame = true;
            break;
        case KEY_ESC:
            exit(EXIT_SUCCESS);
            break;
    }
}
void onKeyUp(unsigned char key, int x, int y) {
    switch(toupper(key)) {
        case 'W':
            kh.movingForward = false;
            break;
        case 'A':
            kh.rollingLeft = false;
            break;
        case 'S':
            kh.movingBackward = false;
            break;
        case 'D':
            kh.rollingRight = false;
            break;
        case 'R':
            gameOver = false;
            kh.restartGame = false;
            break;
    }
}

void onMousePress(int state, int button, int x, int y) {
    // If the left mouse button is pressed down.
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        bool fired = false;

        for(int i = 0; i < MAX_BULLETS; i++) {
            if(!bullets[i].activated && !fired) {
                initBullet(&bullets[i], &player);
                bullets[i].activated = true;
                fired = true;
            }
        }
    }
}

// START INPUT METHODS
void onMouseMove(int x, int y) {
    int screenWidth = glutGet(GLUT_SCREEN_WIDTH);
    int screenHeight = glutGet(GLUT_SCREEN_HEIGHT);

    if (firstMouse) {
        cam.lastX = x;
        cam.lastY = y;
        firstMouse = false;
    }
    // Everytime the cursor is warped, I do not want to perform any changes in the camera.
    if (cam.warpedCursor) {
        cam.lastX = x;
        cam.lastY = y;
        cam.warpedCursor = false;
    }

    float xOffset = (x - cam.lastX) * 0.1;
    float yOffset = (cam.lastY - y) * 0.1;
    cam.lastX = x;
    cam.lastY = y;

    cam.yaw += xOffset;
    cam.pitch += yOffset;

    // Set a limiter for the pitch of the camera.
    float limit = 45;
    if (cam.pitch > limit) {
        cam.pitch = limit;
    } else if (cam.pitch < -limit) {
        cam.pitch = -limit;
    }
    
    // Set the camera's direction (look) vector and normalise it.
    vec3d front;
    front.x = cos(DEG_TO_RAD(cam.yaw)) * cos(DEG_TO_RAD(cam.pitch));
    front.y = sin(DEG_TO_RAD(cam.pitch));
    front.z = sin(DEG_TO_RAD(cam.yaw)) * cos(DEG_TO_RAD(cam.pitch));
    cam.front = normalise(front);
    player.dir = normalise(front);


    // If the cursor reaches the edge of the screen, place it back in the center.
    int centerX = screenWidth / 2.0;
    int centerY = screenHeight / 2.0;
    if (x <= 10 || y <= 10 || x >= screenWidth - 10 || y >= screenHeight - 10) {
        cam.warpedCursor = true;
        CGPoint p = {(CGFloat) centerX, (CGFloat) centerY};
        CGWarpMouseCursorPosition(p);
    }
}
// END INPUT METHODS

void initKeyHandler() {
    kh.movingForward = false;
    kh.movingBackward = false;
    kh.rollingLeft = false;
    kh.rollingRight = false;
    kh.restartGame = false;
}

void initGame() {
    // Set the roundNum number to 1.
    roundNum = 1;

    // Since the game is starting, set all keyHandler values to false.
    initKeyHandler();

    // Setting up the window.
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
    glutCreateWindow("Asteroids Arena 3D");
    glutFullScreen();

    // Various glut functions for gameplay.
    glutReshapeFunc(onReshape);
    glutKeyboardFunc(onKeyPress);
    glutKeyboardUpFunc(onKeyUp);
    glutMouseFunc(onMousePress);
    glutPassiveMotionFunc(onMouseMove);
    glutDisplayFunc(onDisplay);
    glutIdleFunc(onIdle);

    initAsteroidVertices();
    initLighting();
    glEnable(GL_NORMALIZE);

    // Hide the cursor on screen.
    glutSetCursor(GLUT_CURSOR_NONE);
}

int main(int argc, char **argv) {
    if(argc < 2) {
        fprintf(stderr, "Needs input.obj\n");
        return 0;
    }

    glutInit(&argc, argv);
    initGame();

    // PUT OBJLOADER HERE
    float bmin[3], bmax[3];
    float maxExtent;
    if (0 == LoadObjAndConvert(bmin, bmax, argv[1])) {
      printf("failed to load & conv\n");
      return -1;
    }

    maxExtent = 0.5f * (bmax[0] - bmin[0]);
    if (maxExtent < 0.5f * (bmax[1] - bmin[1])) {
      maxExtent = 0.5f * (bmax[1] - bmin[1]);
    }
    if (maxExtent < 0.5f * (bmax[2] - bmin[2])) {
      maxExtent = 0.5f * (bmax[2] - bmin[2]);
    }

    glutMainLoop();
    return(EXIT_SUCCESS);
}

static void CalcNormal(float N[3], float v0[3], float v1[3], float v2[3]) {
    float v10[3];
    float v20[3];
    float len2;

    v10[0] = v1[0] - v0[0];
    v10[1] = v1[1] - v0[1];
    v10[2] = v1[2] - v0[2];

    v20[0] = v2[0] - v0[0];
    v20[1] = v2[1] - v0[1];
    v20[2] = v2[2] - v0[2];

    N[0] = v20[1] * v10[2] - v20[2] * v10[1];
    N[1] = v20[2] * v10[0] - v20[0] * v10[2];
    N[2] = v20[0] * v10[1] - v20[1] * v10[0];

    len2 = N[0] * N[0] + N[1] * N[1] + N[2] * N[2];
    if (len2 > 0.0f) {
        float len = (float)sqrt((double)len2);

        N[0] /= len;
        N[1] /= len;
    }
}

static char* mmap_file(size_t* len, const char* filename) {
    #ifdef _WIN64
    HANDLE file =
        CreateFileA(filename, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,
                    FILE_ATTRIBUTE_NORMAL | FILE_FLAG_SEQUENTIAL_SCAN, NULL);

    if (file == INVALID_HANDLE_VALUE) { /* E.g. Model may not have materials. */
        return NULL;
    }

    HANDLE fileMapping = CreateFileMapping(file, NULL, PAGE_READONLY, 0, 0, NULL);
    assert(fileMapping != INVALID_HANDLE_VALUE);

    LPVOID fileMapView = MapViewOfFile(fileMapping, FILE_MAP_READ, 0, 0, 0);
    char* fileMapViewChar = (char*)fileMapView;
    assert(fileMapView != NULL);

    DWORD file_size = GetFileSize(file, NULL);
    (*len) = (size_t)file_size;

    return fileMapViewChar;
    #else

    FILE* f;
    long file_size;
    struct stat sb;
    char* p;
    int fd;

    (*len) = 0;

    f = fopen(filename, "r");
    if (!f) {
        perror("open");
        return NULL;
    }
    fseek(f, 0, SEEK_END);
    file_size = ftell(f);
    fclose(f);

    fd = open(filename, O_RDONLY);
    if (fd == -1) {
        perror("open");
        return NULL;
    }

    if (fstat(fd, &sb) == -1) {
        perror("fstat");
        return NULL;
    }

    if (!S_ISREG(sb.st_mode)) {
        fprintf(stderr, "%s is not a file\n", "lineitem.tbl");
        return NULL;
    }

    p = (char*)mmap(0, (size_t)file_size, PROT_READ, MAP_SHARED, fd, 0);

    if (p == MAP_FAILED) {
        perror("mmap");
        return NULL;
    }

    if (close(fd) == -1) {
        perror("close");
        return NULL;
    }

    (*len) = (size_t)file_size;

    return p;

    #endif
}

static char* get_dirname(char* path) {
    char* last_delim = NULL;

    if (path == NULL) {
        return path;
    }

    #if defined(_WIN32)
    /* TODO: Unix style path */
    last_delim = strrchr(path, '\\');
    #else
    last_delim = strrchr(path, '/');
    #endif

    if (last_delim == NULL) {
        /* no delimiter in the string. */
        return path;
    }

    /* remove '/' */
    last_delim[0] = '\0';

    return path;
}

static void get_file_data(void* ctx, const char* filename, const int is_mtl, const char* obj_filename, char** data, size_t* len) {
    // NOTE: If you allocate the buffer with malloc(),
    // You can define your own memory management struct and pass it through `ctx`
    // to store the pointer and free memories at clean up stage(when you quit an
    // app)
    // This example uses mmap(), so no free() required.
    (void)ctx;

    if (!filename) {
        fprintf(stderr, "null filename\n");
        (*data) = NULL;
        (*len) = 0;
        return;
    }

    const char* ext = strrchr(filename, '.');

    size_t data_len = 0;

    if (strcmp(ext, ".gz") == 0) {
        assert(0); /* todo */

    } else {
        char* basedirname = NULL;

        char tmp[1024];
        tmp[0] = '\0';

        /* For .mtl, extract base directory path from .obj filename and append .mtl
        * filename */
        if (is_mtl && obj_filename) {
        /* my_strdup is from tinyobjloader-c.h implementation(since strdup is not
        * a C standard library function */
        basedirname = my_strdup(obj_filename, strlen(obj_filename));
        basedirname = get_dirname(basedirname);
        printf("basedirname = %s\n", basedirname);
        }

        if (basedirname) {
        strncpy(tmp, basedirname, strlen(basedirname) + 1);

    #if defined(_WIN32)
        strncat(tmp, "/", 1023 - strlen(tmp));
    #else
        strncat(tmp, "/", 1023 - strlen(tmp));
    #endif
        strncat(tmp, filename, 1023 - strlen(tmp));
        } else {
        strncpy(tmp, filename, strlen(filename) + 1);
        }

        printf("tmp = %s\n", tmp);

        if (basedirname) {
        free(basedirname);
        }

        *data = mmap_file(&data_len, tmp);
    }

    (*len) = data_len;
}

static int LoadObjAndConvert(float bmin[3], float bmax[3], const char* filename) {
    tinyobj_attrib_t attrib;
    tinyobj_shape_t* shapes = NULL;
    size_t num_shapes;
    tinyobj_material_t* materials = NULL;
    size_t num_materials;

    {
        unsigned int flags = TINYOBJ_FLAG_TRIANGULATE;
        int ret =
            tinyobj_parse_obj(&attrib, &shapes, &num_shapes, &materials,
                            &num_materials, filename, get_file_data, NULL, flags);
        if (ret != TINYOBJ_SUCCESS) {
        return 0;
        }

        printf("# of shapes    = %d\n", (int)num_shapes);
        printf("# of materials = %d\n", (int)num_materials);

        /*
        {
        int i;
        for (i = 0; i < num_shapes; i++) {
            printf("shape[%d] name = %s\n", i, shapes[i].name);
        }
        }
        */
    }

    bmin[0] = bmin[1] = bmin[2] = FLT_MAX;
    bmax[0] = bmax[1] = bmax[2] = -FLT_MAX;

    {
        DrawObject o;
        float* vb;
        /* std::vector<float> vb; //  */
        size_t face_offset = 0;
        size_t i;

        /* Assume triangulated face. */
        size_t num_triangles = attrib.num_face_num_verts;
        size_t stride = 9; /* 9 = pos(3float), normal(3float), color(3float) */

        vb = (float*)malloc(sizeof(float) * stride * num_triangles * 3);

        for (i = 0; i < attrib.num_face_num_verts; i++) {
        size_t f;
        assert(attrib.face_num_verts[i] % 3 ==
                0); /* assume all triangle faces. */
        for (f = 0; f < (size_t)attrib.face_num_verts[i] / 3; f++) {
            size_t k;
            float v[3][3];
            float n[3][3];
            float c[3];
            float len2;

            tinyobj_vertex_index_t idx0 = attrib.faces[face_offset + 3 * f + 0];
            tinyobj_vertex_index_t idx1 = attrib.faces[face_offset + 3 * f + 1];
            tinyobj_vertex_index_t idx2 = attrib.faces[face_offset + 3 * f + 2];

            for (k = 0; k < 3; k++) {
            int f0 = idx0.v_idx;
            int f1 = idx1.v_idx;
            int f2 = idx2.v_idx;
            assert(f0 >= 0);
            assert(f1 >= 0);
            assert(f2 >= 0);

            v[0][k] = attrib.vertices[3 * (size_t)f0 + k];
            v[1][k] = attrib.vertices[3 * (size_t)f1 + k];
            v[2][k] = attrib.vertices[3 * (size_t)f2 + k];
            bmin[k] = (v[0][k] < bmin[k]) ? v[0][k] : bmin[k];
            bmin[k] = (v[1][k] < bmin[k]) ? v[1][k] : bmin[k];
            bmin[k] = (v[2][k] < bmin[k]) ? v[2][k] : bmin[k];
            bmax[k] = (v[0][k] > bmax[k]) ? v[0][k] : bmax[k];
            bmax[k] = (v[1][k] > bmax[k]) ? v[1][k] : bmax[k];
            bmax[k] = (v[2][k] > bmax[k]) ? v[2][k] : bmax[k];
            }

            if (attrib.num_normals > 0) {
            int f0 = idx0.vn_idx;
            int f1 = idx1.vn_idx;
            int f2 = idx2.vn_idx;
            if (f0 >= 0 && f1 >= 0 && f2 >= 0) {
                assert(f0 < (int)attrib.num_normals);
                assert(f1 < (int)attrib.num_normals);
                assert(f2 < (int)attrib.num_normals);
                for (k = 0; k < 3; k++) {
                n[0][k] = attrib.normals[3 * (size_t)f0 + k];
                n[1][k] = attrib.normals[3 * (size_t)f1 + k];
                n[2][k] = attrib.normals[3 * (size_t)f2 + k];
                }
            } else { /* normal index is not defined for this face */
                /* compute geometric normal */
                CalcNormal(n[0], v[0], v[1], v[2]);
                n[1][0] = n[0][0];
                n[1][1] = n[0][1];
                n[1][2] = n[0][2];
                n[2][0] = n[0][0];
                n[2][1] = n[0][1];
                n[2][2] = n[0][2];
            }
            } else {
            /* compute geometric normal */
            CalcNormal(n[0], v[0], v[1], v[2]);
            n[1][0] = n[0][0];
            n[1][1] = n[0][1];
            n[1][2] = n[0][2];
            n[2][0] = n[0][0];
            n[2][1] = n[0][1];
            n[2][2] = n[0][2];
            }

            for (k = 0; k < 3; k++) {
            vb[(3 * i + k) * stride + 0] = v[k][0];
            vb[(3 * i + k) * stride + 1] = v[k][1];
            vb[(3 * i + k) * stride + 2] = v[k][2];
            vb[(3 * i + k) * stride + 3] = n[k][0];
            vb[(3 * i + k) * stride + 4] = n[k][1];
            vb[(3 * i + k) * stride + 5] = n[k][2];

            /* Use normal as color. */
            c[0] = n[k][0];
            c[1] = n[k][1];
            c[2] = n[k][2];
            len2 = c[0] * c[0] + c[1] * c[1] + c[2] * c[2];
            if (len2 > 0.0f) {
                float len = (float)sqrt((double)len2);

                c[0] /= len;
                c[1] /= len;
                c[2] /= len;
            }

            vb[(3 * i + k) * stride + 6] = (c[0] * 0.5f + 0.5f);
            vb[(3 * i + k) * stride + 7] = (c[1] * 0.5f + 0.5f);
            vb[(3 * i + k) * stride + 8] = (c[2] * 0.5f + 0.5f);
            }
        }
        /* You can access per-face material through attrib.material_ids[i] */

        face_offset += (size_t)attrib.face_num_verts[i];
        }

        o.vb = 0;
        o.numTriangles = 0;
        if (num_triangles > 0) {
        glGenBuffers(1, &o.vb);
        glBindBuffer(GL_ARRAY_BUFFER, o.vb);
        glBufferData(GL_ARRAY_BUFFER,
                    (GLsizeiptr)(num_triangles * 3 * stride * sizeof(float)), vb,
                    GL_STATIC_DRAW);
        o.numTriangles = (int)num_triangles;
        }

        free(vb);

        drawObject = o;
    }

    printf("bmin = %f, %f, %f\n", (double)bmin[0], (double)bmin[1],
            (double)bmin[2]);
    printf("bmax = %f, %f, %f\n", (double)bmax[0], (double)bmax[1],
            (double)bmax[2]);

    tinyobj_attrib_free(&attrib);
    tinyobj_shapes_free(shapes, num_shapes);
    tinyobj_materials_free(materials, num_materials);

    return 1;
}

void Draw(const DrawObject* drawObject) {
    glPolygonMode(GL_FRONT, GL_FILL);
    glPolygonMode(GL_BACK, GL_FILL);

    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.0, 1.0);
    glColor3f(1.0f, 1.0f, 1.0f);
    if (drawObject->vb >= 1) {
        glBindBuffer(GL_ARRAY_BUFFER, drawObject->vb);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);
        glVertexPointer(3, GL_FLOAT, 36, (const void*)0);
        glNormalPointer(GL_FLOAT, 36, (const void*)(sizeof(float) * 3));
        glColorPointer(3, GL_FLOAT, 36, (const void*)(sizeof(float) * 6));

        glDrawArrays(GL_TRIANGLES, 0, 3 * drawObject->numTriangles);
        // CheckErrors("drawarrays");
    }

    // /* draw wireframe */
    // glDisable(GL_POLYGON_OFFSET_FILL);
    // glPolygonMode(GL_FRONT, GL_LINE);
    // glPolygonMode(GL_BACK, GL_LINE);

    // glColor3f(0.0f, 0.0f, 0.4f);

    // if (drawObject->vb >= 1) {
    //     glBindBuffer(GL_ARRAY_BUFFER, drawObject->vb);
    //     glEnableClientState(GL_VERTEX_ARRAY);
    //     glEnableClientState(GL_NORMAL_ARRAY);
    //     glDisableClientState(GL_COLOR_ARRAY);
    //     glVertexPointer(3, GL_FLOAT, 36, (const void*)0);
    //     glNormalPointer(GL_FLOAT, 36, (const void*)(sizeof(float) * 3));

    //     glDrawArrays(GL_TRIANGLES, 0, 3 * drawObject->numTriangles);
    //     // CheckErrors("drawarrays");
    // }
}