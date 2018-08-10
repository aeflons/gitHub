#ifndef MESH_H
#define MESH_H

#include "shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>
#include "vmath.h"
using namespace std;

struct Vertex {
    // position
    vmath::vec3 Position;
    // normal
    vmath::vec3 Normal;
    // texCoords
    vmath::vec2 TexCoords;
    // tangent
    vmath::vec3 Tangent;
    // bitangent
    vmath::vec3 Bitangent;
};

struct Texture {
    unsigned int id;
    string type;
    string path;
};
GLfloat verticesc[] = {
    // Positions
    -0.5f, -0.5f, -0.5f,
    -0.5f, 0.5f, -0.5f,
    0.5f, -0.5f, -0.5f,
};
class Mesh {
public:
    
    /*  Mesh Data  */
    vector<Vertex> vertices;
    vector<unsigned int> indices;
    vector<Texture> textures;
    unsigned int VAO;
    unsigned int VCO;
    /*  Functions  */
    // constructor
    Mesh(vector<Vertex> vertices, vector<unsigned int> indices, vector<Texture> textures)
    {
        this->vertices = vertices;
        this->indices = indices;
        this->textures = textures;
//        for(unsigned int i = 0; i <  this->vertices.size(); i++){
//
//            if ((i + 1) % 3 == 1) {
//                 this->vertices[i].Position = vmath::vec3(-0.5f, -0.5f, -0.5f);
//            }
//            if ((i + 1) % 3 == 2) {
//               this->vertices[i].Position = vmath::vec3(0.5f, -0.5f, -0.5f);
//            }
//            if ((i + 1) % 3 == 0) {
//            this->vertices[i].Position = vmath::vec3(-0.5f, 0.5f, -0.5f);
//            }
//        }
        // now that we have all the required data, set the vertex buffers and its attribute pointers.
        setupMesh();
    }

    // render the mesh
    void Draw(Shader shader) 
    {
        // bind appropriate textures
        unsigned int diffuseNr  = 1;
        unsigned int specularNr = 1;
        unsigned int normalNr   = 1;
        unsigned int heightNr   = 1;
        for(unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // active proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            string number;
            string name = textures[i].type;
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to stream
            else if(name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to stream
             else if(name == "texture_height")
                number = std::to_string(heightNr++); // transfer unsigned int to stream

            GLuint ss = glGetUniformLocation(shader.ID, (name + number).c_str());                                     // now set the sampler to the correct texture unit
            glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i);
            // and finally bind the texture
            glBindTexture(GL_TEXTURE_2D, textures[i].id);
        }
        
        // draw mesh
        glBindVertexArray(VAO);
       // glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, &indices);

        //glBindVertexArray(VCO);
        glDrawArrays(GL_TRIANGLES, 0, indices.size());
        glBindVertexArray(0);

        // always good practice to set everything back to defaults once configured.
        glActiveTexture(GL_TEXTURE0);
    }

private:
    /*  Render data  */
    unsigned int VBO, EBO,vbco;

    /*  Functions    */
    // initializes all the buffer objects/arrays
    void setupMesh()
    {
        // create buffers/arrays
        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glGenBuffers(1, &VBO);
        //glGenBuffers(1, &EBO);

        // load data into vertex buffers
        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        // A great thing about structs is that their memory layout is sequential for all its items.
        // The effect is that we can simply pass a pointer to the struct and it translates perfectly to a vmath::vec3/2 array which
        // again translates to 3/2 floats which translates to a byte array.
        glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);  

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

        // set the vertex attribute pointers
        // vertex Positions[2]    Vertex
        GLuint size = offsetof(Vertex, Tangent);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        glEnableVertexAttribArray(0);

        // vertex normals
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Normal));
        glEnableVertexAttribArray(1);

        // vertex texture coords
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, TexCoords));
        glEnableVertexAttribArray(2);

        // vertex tangent
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Tangent));
        glEnableVertexAttribArray(3);

        // vertex bitangent
        glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, Bitangent));
        glEnableVertexAttribArray(4);

        glBindVertexArray(0);
        
        glGenVertexArrays(1, &VCO);
        glBindVertexArray(VCO);
        
        glGenBuffers(1,&vbco);
        glBindBuffer(GL_ARRAY_BUFFER,vbco);
        glBufferData(GL_ARRAY_BUFFER,  sizeof(verticesc), verticesc,GL_STATIC_DRAW);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,  3* sizeof(GLfloat),(GLvoid *)0);
        glEnableVertexAttribArray(0);
        glBindVertexArray(0);

    }
};
#endif
