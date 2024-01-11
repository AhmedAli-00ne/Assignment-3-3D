#include "Angel.h"
#include "Sphere.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"


typedef Angel::vec4  color4;
typedef Angel::vec4  point4;


int Index = 0;
float speed = 0.1f, yaw = -90.0f;
GLuint program, vao, vbo1, vbo2, ibo1, ibo2, vbo3, ibo3, vbo4, ibo4, vbo5, ibo5, vbo6, ibo6, vbo7, ibo7, vbo8, ibo8, vbo9, ibo9, vPosition, vNormal, vTexture, modelUnifrom, modelAttrib, viewUniform, projectionUniform, cameraUniform, texture1, texture2, texture3, texture4, texture5, texture6, texture7, texture8, texture9;
glm::mat4 model;
enum { Xaxis = 0, Yaxis = 0, Zaxis = 0, NumAxes = 3 };
int   Axis = Xaxis;
GLfloat  Theta[3] = { 0.0, 0.0, 0.0 };
GLuint theta, transAttrib;
glm::mat4 trans;

glm::vec3 cameraPos, cameraTarget, cameraDirection, cameraRight, cameraUp, cameraFront;
glm::mat4 view, projection;

Sphere Sun(0.1f);
Sphere Mercury(0.03f);
Sphere Venus(0.05f);
Sphere Earth(0.05f);
Sphere Mars(0.02f);
Sphere Jupiter(0.09f);
Sphere Saturn(0.08f);
Sphere Uranus(0.06f);
Sphere Neptune(0.06f);


float translate = 0.f, scaleSun = 1.0f, scale = 0.5f; 
float factor = 0.0005;
float rotationAngle = 0.0f;
float rotationAngle1 = 30.0f;
float rotationAngle2 = 60.0f;
float rotationAngle3 = 90.f;
float rotationAngle4 = 120.0f;
float rotationAngle5 = 150.0f;
float rotationAngle6 = 180.0f;
float rotationAngle7 = 210.0f;
float rotationAngle8 = 240.0f;


GLuint  sphereColor;


void initLight()

{
    point4 light_direction1(-0.2, 0.0, 0.0, 1.0);
    point4 light_direction2(0.2, 0.0, 0.0, 1.0);

    color4 light_ambient(0.5, 0.5, 0.5, 1.0);
    color4 light_diffuse(1.0, 1.0, 0.0, 0.0);
    color4 light_specular(1.0, 1.0, 1.0, 1.0);

    color4 material_ambient(0.5, 0.5, 0.5, 1.0);
    color4 material_diffuse(1.0, 1.0, 1.0, 1.0);
    color4 material_specular(1.0, 1.0, 1.0, 1.0);
    float material_shininess = 100.0;

    glUniform4fv(glGetUniformLocation(program, "lights[0].ambient"), 1, light_ambient);
    glUniform4fv(glGetUniformLocation(program, "lights[0].diffuse"), 1, light_diffuse);
    glUniform4fv(glGetUniformLocation(program, "lights[0].specular"), 1, light_specular);
    glUniform4fv(glGetUniformLocation(program, "lights[0].direction"), 1, light_direction1);

    glUniform4fv(glGetUniformLocation(program, "lights[1].ambient"), 1, light_ambient);
    glUniform4fv(glGetUniformLocation(program, "lights[1].diffuse"), 1, light_diffuse);
    glUniform4fv(glGetUniformLocation(program, "lights[1].specular"), 1, light_specular);
    glUniform4fv(glGetUniformLocation(program, "lights[1].direction"), 1, light_direction2);

    glUniform4fv(glGetUniformLocation(program, "material.ambient"), 1, material_ambient);
    glUniform4fv(glGetUniformLocation(program, "material.diffuse"), 1, material_diffuse);
    glUniform4fv(glGetUniformLocation(program, "material.specular"), 1, material_specular);
    glUniform1f(glGetUniformLocation(program, "material.shininess"), material_shininess);


}

void initTexture()
{ 
    stbi_set_flip_vertically_on_load(true);

    glGenTextures(1, &texture1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, channels;
    unsigned char* data1 = stbi_load("sun.jpg", &width, &height, &channels, 0);

    if (data1)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data1);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data1);

    glGenTextures(1, &texture2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data2 = stbi_load("mercury.jpg", &width, &height, &channels, 0);

    if (data2)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data2);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data2);

    glGenTextures(1, &texture3);
    glBindTexture(GL_TEXTURE_2D, texture3);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data3 = stbi_load("venus.jpg", &width, &height, &channels, 0);

    if (data3)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data3);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data3);

    glGenTextures(1, &texture4);
    glBindTexture(GL_TEXTURE_2D, texture4);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data4 = stbi_load("earth.bmp", &width, &height, &channels, 0);

    if (data4)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data4);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data4);

    glGenTextures(1, &texture5);
    glBindTexture(GL_TEXTURE_2D, texture5);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data5 = stbi_load("mars.jpg", &width, &height, &channels, 0);

    if (data5)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data5);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data5);

    glGenTextures(1, &texture6);
    glBindTexture(GL_TEXTURE_2D, texture6);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data6 = stbi_load("jupiter.jpg", &width, &height, &channels, 0);

    if (data6)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data6);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data6);

    glGenTextures(1, &texture7);
    glBindTexture(GL_TEXTURE_2D, texture7);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data7 = stbi_load("saturn.jpg", &width, &height, &channels, 0);

    if (data7)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data7);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data7);

    glGenTextures(1, &texture8);
    glBindTexture(GL_TEXTURE_2D, texture8);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data8 = stbi_load("uranus.jpg", &width, &height, &channels, 0);

    if (data8)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data8);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data8);

    glGenTextures(1, &texture9);
    glBindTexture(GL_TEXTURE_2D, texture9);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    unsigned char* data9 = stbi_load("neptune.jpg", &width, &height, &channels, 0);

    if (data9)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data9);
        glGenerateMipmap(GL_TEXTURE_2D);
    }

    stbi_image_free(data9);
}

void init()
{

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);


    glGenBuffers(1, &vbo1);
    glBindBuffer(GL_ARRAY_BUFFER, vbo1);




    glBufferData(GL_ARRAY_BUFFER, Sun.getInterleavedVertexSize(),
        Sun.getInterleavedVertices(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Sun.getIndexSize(), Sun.getIndices(), GL_STATIC_DRAW);



    glGenBuffers(1, &vbo2);
    glBindBuffer(GL_ARRAY_BUFFER, vbo2);



    glBufferData(GL_ARRAY_BUFFER, Mercury.getInterleavedVertexSize(),
        Mercury.getInterleavedVertices(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Mercury.getIndexSize(), Mercury.getIndices(), GL_STATIC_DRAW);


    glGenBuffers(1, &vbo3);
    glBindBuffer(GL_ARRAY_BUFFER, vbo3);



    glBufferData(GL_ARRAY_BUFFER, Venus.getInterleavedVertexSize(),
        Venus.getInterleavedVertices(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo3);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo3);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Venus.getIndexSize(), Venus.getIndices(), GL_STATIC_DRAW);

    glGenBuffers(1, &vbo4);
    glBindBuffer(GL_ARRAY_BUFFER, vbo4);



    glBufferData(GL_ARRAY_BUFFER, Earth.getInterleavedVertexSize(),
        Venus.getInterleavedVertices(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo4);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo4);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Earth.getIndexSize(), Earth.getIndices(), GL_STATIC_DRAW);

    glGenBuffers(1, &vbo5);
    glBindBuffer(GL_ARRAY_BUFFER, vbo5);



    glBufferData(GL_ARRAY_BUFFER, Mars.getInterleavedVertexSize(),
        Venus.getInterleavedVertices(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo5);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo5);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Mars.getIndexSize(), Mars.getIndices(), GL_STATIC_DRAW);

    glGenBuffers(1, &vbo6);
    glBindBuffer(GL_ARRAY_BUFFER, vbo6);



    glBufferData(GL_ARRAY_BUFFER, Jupiter.getInterleavedVertexSize(),
        Jupiter.getInterleavedVertices(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo6);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo6);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Jupiter.getIndexSize(), Jupiter.getIndices(), GL_STATIC_DRAW);


    glGenBuffers(1, &vbo7);
    glBindBuffer(GL_ARRAY_BUFFER, vbo7);



    glBufferData(GL_ARRAY_BUFFER, Saturn.getInterleavedVertexSize(),
        Saturn.getInterleavedVertices(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo7);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo7);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Saturn.getIndexSize(), Saturn.getIndices(), GL_STATIC_DRAW);


    glGenBuffers(1, &vbo8);
    glBindBuffer(GL_ARRAY_BUFFER, vbo8);



    glBufferData(GL_ARRAY_BUFFER, Uranus.getInterleavedVertexSize(),
        Uranus.getInterleavedVertices(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo8);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo8);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Uranus.getIndexSize(), Uranus.getIndices(), GL_STATIC_DRAW);


    glGenBuffers(1, &vbo9);
    glBindBuffer(GL_ARRAY_BUFFER, vbo9);



    glBufferData(GL_ARRAY_BUFFER, Neptune.getInterleavedVertexSize(),
        Neptune.getInterleavedVertices(), GL_STATIC_DRAW);

    glGenBuffers(1, &ibo9);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo9);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, Neptune.getIndexSize(), Neptune.getIndices(), GL_STATIC_DRAW);

    program = InitShader("vshader.glsl", "fshader.glsl");
    glUseProgram(program);

    vPosition = glGetAttribLocation(program, "vertexPosition");
    glEnableVertexAttribArray(vPosition);

    vNormal = glGetAttribLocation(program, "vertexNormal");
    glEnableVertexAttribArray(vNormal);


    vTexture = glGetAttribLocation(program, "vertexTexture");
    glEnableVertexAttribArray(vTexture);
    sphereColor = glGetUniformLocation(program, "vColor");

    theta = glGetUniformLocation(program, "theta");

    modelUnifrom = glGetUniformLocation(program, "model");
    transAttrib = glGetUniformLocation(program, "trans");
    viewUniform = glGetUniformLocation(program, "view");
    projectionUniform = glGetUniformLocation(program, "projection");
    cameraUniform = glGetUniformLocation(program, "camera");

    cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
    cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
    cameraDirection = glm::normalize(cameraPos - cameraTarget);
    cameraRight = glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), cameraDirection));
    cameraUp = glm::cross(cameraDirection, cameraRight);
    cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    sphereColor = glGetUniformLocation(program, "vColor");
    projection = glm::perspective(glm::radians(45.f), 512.0f / 512.0f, 0.1f, 100.0f);
    glUniformMatrix4fv(projectionUniform, 1, GL_FALSE, glm::value_ptr(projection));
    initLight();
    initTexture();

    glEnable(GL_DEPTH_TEST);
    glClearColor(0.0, 0.0, 0.0, 1.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    glUniformMatrix4fv(viewUniform, 1, GL_FALSE, glm::value_ptr(view));
    glUniform3fv(cameraUniform, 1, glm::value_ptr(cameraPos));

    glBindBuffer(GL_ARRAY_BUFFER, vbo1);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo1);
    glBindTexture(GL_TEXTURE_2D, texture1);

    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, Sun.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, Sun.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, Sun.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);

    model = glm::rotate(model, glm::radians(rotationAngle), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glUniform4fv(sphereColor, 1, color4(1.0, 1.0, 0.0, 1.0));
    glDrawElements(GL_TRIANGLES, Sun.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo2);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo2);
    glBindTexture(GL_TEXTURE_2D, texture2);

    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, Mercury.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, Mercury.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, Mercury.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotationAngle1), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(-0.15f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationAngle1), glm::vec3(0.0f, 1.0f, 0.0f));



    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glUniform4fv(sphereColor, 1, color4(0.80, 0.80, 0.80, 0.0));
    glDrawElements(GL_TRIANGLES, Mercury.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo3);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo3);
    glBindTexture(GL_TEXTURE_2D, texture3);


    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, Venus.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, Venus.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, Venus.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotationAngle2), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(-0.25f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationAngle2), glm::vec3(0.0f, 1.0f, 0.0f));


    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glUniform4fv(sphereColor, 1, color4(1.0, 1.0, 3.0, 1.0));
    glDrawElements(GL_TRIANGLES, Venus.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo4);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo4);
    glBindTexture(GL_TEXTURE_2D, texture4);

    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, Earth.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, Earth.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, Earth.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotationAngle3), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.35f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationAngle3), glm::vec3(0.0f, 1.0f, 0.0f));



    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glUniform4fv(sphereColor, 1, color4(0.0, 0.0, 1.0, 1.0));
    glDrawElements(GL_TRIANGLES, Earth.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
 
    glBindBuffer(GL_ARRAY_BUFFER, vbo5);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo5);
    glBindTexture(GL_TEXTURE_2D, texture5);


    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, Mars.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, Mars.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, Mars.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotationAngle4), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.35f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationAngle4), glm::vec3(0.0f, 1.0f, 0.0f));


    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glUniform4fv(sphereColor, 1, color4(0.8, 0.4, 0.2, 1.0));
    glDrawElements(GL_TRIANGLES, Earth.getIndexCount(), GL_UNSIGNED_INT, (void*)0);


    glBindBuffer(GL_ARRAY_BUFFER, vbo6);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo6);
    glBindTexture(GL_TEXTURE_2D, texture6);


    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, Jupiter.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, Jupiter.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, Jupiter.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotationAngle5), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.65f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationAngle5), glm::vec3(0.0f, 1.0f, 0.0f));




    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glUniform4fv(sphereColor, 1, color4(0.9, 0.5, 0.6, 1.0));
    glDrawElements(GL_TRIANGLES, Jupiter.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo7);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo7);
    glBindTexture(GL_TEXTURE_2D, texture7);
    

    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, Saturn.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, Saturn.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, Saturn.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotationAngle6), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.75f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationAngle6), glm::vec3(0.0f, 1.0f, 0.0f));



    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glUniform4fv(sphereColor, 1, color4(0.8, 0.7, 0.4, 1.0));
    glDrawElements(GL_TRIANGLES, Saturn.getIndexCount(), GL_UNSIGNED_INT, (void*)0);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo8);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo8);
    glBindTexture(GL_TEXTURE_2D, texture8);

    

    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, Uranus.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, Uranus.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, Uranus.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotationAngle7), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.65f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationAngle7), glm::vec3(0.0f, 1.0f, 0.0f));


    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glUniform4fv(sphereColor, 1, color4(0.0, 0.5, 0.5, 1.0));
    glDrawElements(GL_TRIANGLES, Uranus.getIndexCount(), GL_UNSIGNED_INT, (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, vbo9);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo9);
    glBindTexture(GL_TEXTURE_2D, texture9);


    glVertexAttribPointer(vPosition, 3, GL_FLOAT, GL_FALSE, Neptune.getInterleavedStride(), BUFFER_OFFSET(0));
    glVertexAttribPointer(vNormal, 3, GL_FLOAT, false, Neptune.getInterleavedStride(), (void*)(3 * sizeof(float)));
    glVertexAttribPointer(vTexture, 2, GL_FLOAT, false, Neptune.getInterleavedStride(), (void*)(6 * sizeof(float)));
    model = glm::mat4(1.0f);
    model = glm::rotate(model, glm::radians(rotationAngle8), glm::vec3(0.0f, 1.0f, 0.0f));
    model = glm::translate(model, glm::vec3(0.95f, 0.0f, 0.0f));
    model = glm::rotate(model, glm::radians(rotationAngle8), glm::vec3(0.0f, 1.0f, 0.0f));



    glUniformMatrix4fv(modelUnifrom, 1, GL_FALSE, glm::value_ptr(model));
    glUniform4fv(sphereColor, 1, color4(0.2, 0.2, 0.8, 1.0));
    glDrawElements(GL_TRIANGLES, Neptune.getIndexCount(), GL_UNSIGNED_INT, (void*)0);


    glutSwapBuffers();
}


void idle() {
    
    if (rotationAngle >= 360.0f) {
        rotationAngle -= 360.0f;
    }

    float rotationSpeed = 0.02f;

    rotationAngle += rotationSpeed;
    
    if (rotationAngle1 >= 360.0f) {
        rotationAngle1 -= 360.0f;
    }

    float rotationSpeed1 = 0.16f;

    rotationAngle1 += rotationSpeed1;
    
    if (rotationAngle2 >= 360.0f) {
        rotationAngle2 -= 360.0f;
    }

    float rotationSpeed2 = 0.14f;

    rotationAngle2 += rotationSpeed2;
    
    if (rotationAngle3 >= 360.0f) {
        rotationAngle3 -= 360.0f;
    }

    float rotationSpeed3 = 0.12f;

    rotationAngle3 += rotationSpeed3;
    
    if (rotationAngle4 >= 360.0f) {
        rotationAngle4 -= 360.0f;
    }

    float rotationSpeed4 = 0.1f;

    rotationAngle4 += rotationSpeed4;
    
    if (rotationAngle5 >= 360.0f) {
        rotationAngle5 -= 360.0f;
    }

    float rotationSpeed5 = 0.08f;

    rotationAngle5 += rotationSpeed5;
    
    if (rotationAngle6 >= 360.0f) {
        rotationAngle6 -= 360.0f;
    }

    float rotationSpeed6 = 0.06f;

    rotationAngle6 += rotationSpeed6;
    
    if (rotationAngle7 >= 360.0f) {
        rotationAngle7 -= 360.0f;
    }

    float rotationSpeed7 = 0.04f;

    rotationAngle7 += rotationSpeed7;
    
    if (rotationAngle8 >= 360.0f) {
        rotationAngle8 -= 360.0f;
    }

    float rotationSpeed8 = 0.02f;

    rotationAngle8 += rotationSpeed8;

    glutPostRedisplay();

}

void keyboard(unsigned char key, int x, int y)
{
    switch (key) {
    case 033:
        exit(EXIT_SUCCESS);
        break;
    case 'r':
        cameraPos += speed * cameraUp;
        break;
    case 'f':
        cameraPos -= speed * cameraUp;
        break;
    case 'w':
        cameraPos += speed * cameraFront;
        break;
    case 's':
        cameraPos -= speed * cameraFront;
        break;
    case 'a':
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
        break;
    case 'd':
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * speed;
        break;
    }
}


int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(600, 600);
    glutInitContextVersion(3, 2);
    glutInitContextProfile(GLUT_CORE_PROFILE);
    glutCreateWindow("Assignment 3");

    glewInit();

    init();

    glutDisplayFunc(display);
    glutIdleFunc(idle);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}

