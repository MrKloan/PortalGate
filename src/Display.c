#include "includes.h"

void DisplayInit(Display *this)
{
    glutInit(this->argc, this->argv);

    if(this->fullscreen)
    {
        this->width = (int)glutGet(GLUT_SCREEN_WIDTH);
        this->height = (int)glutGet(GLUT_SCREEN_HEIGHT);
    }
    else
    {
        this->width = 940;
        this->height = 580;
    }

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
	glutInitWindowSize(this->width, this->height);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("PortalGate");

    if(this->fullscreen)
        glutFullScreen();

	glutIgnoreKeyRepeat(1);

	//Callbacks
	glutDisplayFunc(this->render);
	glutReshapeFunc(this->resize);
	//glutIdleFunc(this->idle);
	glutKeyboardFunc(this->keys);
	glutKeyboardUpFunc(this->keysUp);
	glutSpecialFunc(this->specials);
	glutSpecialUpFunc(this->specialsUp);
	glutMouseFunc(this->click);
	glutMotionFunc(this->motion);
	glutPassiveMotionFunc(this->pressed);
	glutEntryFunc(this->entry);

	glutTimerFunc(DISPLAY_TICK, this->tick, this->running);

	glEnable(GL_DEPTH_TEST);

    //Lumières
	glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    glEnable(GL_NORMALIZE);

    //X docs say all polygons are emitted CCW, but tests show that some aren't.
    if(getenv("MODEL_IS_BROKEN"))
        glFrontFace(GL_CW);

    glColorMaterial(GL_FRONT_AND_BACK, GL_DIFFUSE);
}

void DisplayStart(void)
{
	glutMainLoop();
}

void DisplayIdle(void)
{
    //UNUSED
}

void DisplayTick(int running)
{
    display->mouse->click(display->mouse);
    display->keyboard->handle(display->keyboard);

    if(cube->moving)
    {
        if(cube->move[CUBE_FORWARD])
            cube->forward(cube);
        else if(cube->move[CUBE_BACK])
            cube->back(cube);
        else if(cube->move[CUBE_LEFT])
            cube->left(cube);
        else if(cube->move[CUBE_RIGHT])
            cube->right(cube);
    }

    display->render();

    if(running)
        glutTimerFunc(DISPLAY_TICK, display->tick, display->running);
}

void DisplayRender(void)
{
    int i;

    GLfloat lightColorDefault[] = {1.0f, 1.0f, 1.0f, 1.0f};
    //GLfloat lightColorRed[] = {1.0f, 0.f, 0.f, 1.0f};
	GLfloat lightPos0[] = {0.0f, 10.0f, 0.0f, 0.0f};
	GLfloat lightPos1[] = {0.0f, -1.0f, 0.0f, 1.0f};
	//GLfloat lightPos2[] = {-2.0f, 10.0f, -30.0f, 1.0f};

	//Nettoie les buffers de couleur et de profondeur
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

    //Gestion des lumières
	glLightfv(GL_LIGHT0, GL_DIFFUSE, lightColorDefault);
	glLightfv(GL_LIGHT0, GL_SPECULAR, lightColorDefault);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos0);

	glLightfv(GL_LIGHT1, GL_DIFFUSE, lightColorDefault);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPos1);

	/*glLightfv(GL_LIGHT2, GL_DIFFUSE, lightColorRed);
	glLightfv(GL_LIGHT2, GL_POSITION, lightPos2);*/

	glShadeModel(GL_SMOOTH);

	//Camera
	gluLookAt(
        camera->x, camera->y, camera->z,
        camera->x + camera->lx, camera->y + camera->ly,  camera->z + camera->lz,
        //0.f, 0.f, 0.f,
        0.0f, 1.0f,  0.0f
    );

    skybox->render(skybox);

    //Cube
    cube->render(cube);

	//Sol
	for(i = 0 ; i < tiles->size ; i++)
    {
        Tile *t = (Tile*)tiles->get(tiles, i);

        if(t != NULL)
            t->render(t);
	}

	//Stargate
	stargate->render(stargate);

	//Turret
	for(i = 0 ; i < turrets->size ; i++)
    {
        Turret *t = (Turret*)turrets->get(turrets, i);

        if(t != NULL)
        {
            t->render(t);
            t->ai(t);
        }
    }

    for(i = 0 ; i < pillars->size ; i++)
    {
        Pillar *p = (Pillar*)pillars->get(pillars, i);

        if(p != NULL)
            p->render(p);
    }

	glutSwapBuffers();
	glFlush();
}

void DisplayResize(int w, int h)
{
    float ratio;

	//Evite les divisions par 0
	if(h == 0)
		h = 1;

	ratio =  w * 1.0 / h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	glViewport(0, 0, w, h);
	gluPerspective(45.0f, ratio, 0.1f, 100.0f);

	glMatrixMode(GL_MODELVIEW);
}

void DisplayKeyboard(unsigned char key, int x, int y)
{
	display->keyboard->keys[key] = 1;
}

void DisplayKeyboardUp(unsigned char key, int x, int y)
{
	display->keyboard->keys[key] = 0;
}

void DisplaySpecials(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT :
            display->keyboard->keys[KEY_LEFT] = 1;
            break;
		case GLUT_KEY_RIGHT :
            display->keyboard->keys[KEY_RIGHT] = 1;
			break;
		case GLUT_KEY_UP :
            display->keyboard->keys[KEY_UP] = 1;
			break;
		case GLUT_KEY_DOWN :
            display->keyboard->keys[KEY_DOWN] = 1;
			break;
	}
}

void DisplaySpecialsUp(int key, int x, int y)
{
	switch(key)
	{
		case GLUT_KEY_LEFT :
            display->keyboard->keys[KEY_LEFT] = 0;
            break;
		case GLUT_KEY_RIGHT :
            display->keyboard->keys[KEY_RIGHT] = 0;
			break;
		case GLUT_KEY_UP :
            display->keyboard->keys[KEY_UP] = 0;
			break;
		case GLUT_KEY_DOWN :
            display->keyboard->keys[KEY_DOWN] = 0;
			break;
	}
}

void DisplayMouse(int button, int state, int x, int y)
{
    switch(button)
    {
        case GLUT_LEFT_BUTTON:
            display->mouse->state[MOUSE_LEFT] = (state == GLUT_DOWN) ? 1 : 0;
            break;

        case GLUT_RIGHT_BUTTON:
            display->mouse->state[MOUSE_RIGHT] = (state == GLUT_DOWN) ? 1 : 0;
            break;

        case GLUT_MIDDLE_BUTTON:
            display->mouse->state[MOUSE_MIDDLE] = (state == GLUT_DOWN) ? 1 : 0;
            break;
    }
}

void DisplayMouseMotion(int x, int y)
{
    display->mouse->x = x;
    display->mouse->y = y;

    display->mouse->move(display->mouse);
}


void DisplayMousePressed(int x, int y)
{
    display->mouse->px = x;
    display->mouse->py = y;

    display->mouse->move(display->mouse);
}

void DisplayEntry(int state)
{
    switch(state)
    {
        case GLUT_ENTERED:
            display->mouse->inWindow = 1;
            break;
        case GLUT_LEFT:
            display->mouse->inWindow = 0;
            break;
    }
}

void DisplayFree(Display *this)
{
    free(this->mouse);
    free(this->keyboard);
    free(this);
}

Display *NewDisplay(int *argc, char **argv, unsigned char fullscreen)
{
    Display *this       = malloc(sizeof(Display));

    this->argc          = argc;
    this->argv          = argv;
    this->running       = 1;
    this->fullscreen    = fullscreen;

    this->keyboard      = NewKeyboard();
    this->mouse         = NewMouse();

    this->init          = DisplayInit;
    this->free          = DisplayFree;
    this->start         = DisplayStart;

    this->idle          = DisplayIdle;
    this->tick          = DisplayTick;
    this->render        = DisplayRender;
    this->resize        = DisplayResize;
    this->keys          = DisplayKeyboard;
    this->keysUp        = DisplayKeyboardUp;
    this->specials      = DisplaySpecials;
    this->specialsUp    = DisplaySpecialsUp;
    this->click         = DisplayMouse;
    this->motion        = DisplayMouseMotion;
    this->pressed       = DisplayMousePressed;
    this->entry         = DisplayEntry;

    this->init(this);

    return this;
}

void color4_to_float4(const struct aiColor4D *c, float f[4])
{
    f[0] = c->r;
    f[1] = c->g;
    f[2] = c->b;
    f[3] = c->a;
}

void set_float4(float f[4], float a, float b, float c, float d)
{
    f[0] = a;
    f[1] = b;
    f[2] = c;
    f[3] = d;
}

void apply_material(const struct aiMaterial *mtl)
{
    float c[4];
    GLenum fill_mode;
    int ret1, ret2;
    struct aiColor4D diffuse;
    struct aiColor4D specular;
    struct aiColor4D ambient;
    struct aiColor4D emission;
    float shininess, strength;
    int two_sided;
    int wireframe;
    unsigned int max;

    set_float4(c, 1.0f, 1.0f, 1.0f, 1.0f);

    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_DIFFUSE, &diffuse))
        color4_to_float4(&diffuse, c);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, c);

    set_float4(c, 1.0f, 1.0f, 1.0f, 1.0f);
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_SPECULAR, &specular))
        color4_to_float4(&specular, c);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);

    set_float4(c, 0.5f, 0.5f, 0.5f, 1.0f);
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_AMBIENT, &ambient))
        color4_to_float4(&ambient, c);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, c);

    set_float4(c, 0.0f, 0.0f, 0.0f, 1.0f);
    if(AI_SUCCESS == aiGetMaterialColor(mtl, AI_MATKEY_COLOR_EMISSIVE, &emission))
        color4_to_float4(&emission, c);
    glMaterialfv(GL_FRONT_AND_BACK, GL_EMISSION, c);

    max = 1;
    ret1 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS, &shininess, &max);
    if(ret1 == AI_SUCCESS)
    {
        max = 1;
        ret2 = aiGetMaterialFloatArray(mtl, AI_MATKEY_SHININESS_STRENGTH, &strength, &max);

        if(ret2 == AI_SUCCESS)
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess * strength);
        else
            glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
    }
    else
    {
        glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0f);
        set_float4(c, 0.0f, 0.0f, 0.0f, 0.0f);
        glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, c);
    }

    max = 1;
    if(AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_ENABLE_WIREFRAME, &wireframe, &max))
        fill_mode = wireframe ? GL_LINE : GL_FILL;
    else
        fill_mode = GL_FILL;

    glPolygonMode(GL_FRONT_AND_BACK, fill_mode);
    max = 1;
    if((AI_SUCCESS == aiGetMaterialIntegerArray(mtl, AI_MATKEY_TWOSIDED, &two_sided, &max)) && two_sided)
        glDisable(GL_CULL_FACE);
    else
        glEnable(GL_CULL_FACE);
}

void recursive_render(const struct aiScene *sc, const struct aiNode *nd)
{
    unsigned int i;
    unsigned int n = 0, t;
    struct aiMatrix4x4 m = nd->mTransformation;

    /* update transform */
    aiTransposeMatrix4(&m);
    glPushMatrix();
    glMultMatrixf((float*)&m);

    /* draw all meshes assigned to this node */
    for (; n < nd->mNumMeshes; ++n)
    {
        const struct aiMesh* mesh = sc->mMeshes[nd->mMeshes[n]];

        apply_material(sc->mMaterials[mesh->mMaterialIndex]);

        if(mesh->mNormals == NULL)
            glDisable(GL_LIGHTING);
        else
            glEnable(GL_LIGHTING);

        for(t = 0; t < mesh->mNumFaces; ++t)
        {
            const struct aiFace* face = &mesh->mFaces[t];
            GLenum face_mode;

            switch(face->mNumIndices)
            {
                case 1: face_mode = GL_POINTS; break;
                case 2: face_mode = GL_LINES; break;
                case 3: face_mode = GL_TRIANGLES; break;
                default: face_mode = GL_POLYGON; break;
            }

            /*glEnable(GL_TEXTURE0);
            glEnable(GL_BLEND);
            glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

            glBindTexture(GL_TEXTURE0, texture);
            glTexParameteri(GL_TEXTURE0, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE0, GL_TEXTURE_MAG_FILTER, GL_NEAREST);*/

            glBegin(face_mode);
                for(i = 0; i < face->mNumIndices; i++)
                {
                    int index = face->mIndices[i];

                    if(mesh->mColors[0] != NULL)
                        glColor4fv((GLfloat*)&mesh->mColors[0][index]);

                    if(mesh->mNormals != NULL)
                        glNormal3fv(&mesh->mNormals[index].x);

                    //glTexCoord3f(0.f, 1.f, 0.f);
                    glVertex3fv(&mesh->mVertices[index].x);
                }
            glEnd();

            /*glDisable(GL_BLEND);
            glDisable(GL_TEXTURE0);*/
        }
    }

    /* draw all children */
    for(n = 0 ; n < nd->mNumChildren ; ++n)
        recursive_render(sc, nd->mChildren[n]);

    glPopMatrix();
}
