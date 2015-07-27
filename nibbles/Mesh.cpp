#include <vector>
#include <stdio.h>
#include <math.h>
#include <limits>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <common/objloader.hpp>
#include <common/vboindexer.hpp>

#include "Mesh.hpp"
#include "globals.hpp"
#include "utils.hpp"

Mesh::Mesh(const char * path)
{
    valid = true;
    startindex = (GLuint)indices.size();
    startvertex = (GLuint)indexed_vertices.size();
	std::vector<glm::vec3> vertices;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> normals;
    bool res = loadOBJ(path, vertices, uvs, normals);
    indexVBO(vertices, uvs, normals, indices, indexed_vertices, indexed_uvs, indexed_normals);
    numindices = (GLuint)indices.size() - startindex;
    numvertices = (GLuint)indexed_vertices.size() - startvertex;
}

b2PolygonShape Mesh::getHullWrap(){
    std::vector<b2Vec2> verticesIn = std::vector<b2Vec2>();
    std::vector<b2Vec2> verticesOut = std::vector<b2Vec2>();

    unsigned int i = 0;
    unsigned int j = 0;

    //transfer vertices
    for(i = startindex; i < startindex + numvertices; ++i){
        verticesIn.push_back(b2Vec2(indexed_vertices[i].x, indexed_vertices[i].z));
    }

    //remove duplicates
    for(i = 0; i < verticesIn.size(); ++i){
        for(j = i+1; j < verticesIn.size(); ++j){
            if( (fabs(verticesIn[i].x - verticesIn[j].x) < 0.01) && 
                    (fabs(verticesIn[i].y - verticesIn[j].y) < 0.01) ){
                verticesIn.erase(verticesIn.begin() + j);
                --j;
            }
        }
    }

    //find furthest right vertex
    float farLeft = verticesIn[0].x;
    int farLeftIndex = 0;
    for(i = 1; i < verticesIn.size(); ++i){
        if(verticesIn[i].x < farLeft){
            farLeft = verticesIn[i].x;
            farLeftIndex = i;
        }
    }

    int nextIdx = farLeftIndex;
    verticesOut.push_back(verticesIn[farLeftIndex]);

    //create hull wrap vertices (counter clockwise order)
    do{
        for(i = 0; i < verticesIn.size(); ++i){
            bool nextOnHull = true;
            for(j = 0; j < verticesIn.size(); ++j){
                if(nextIdx != i && nextIdx != j && i != j){
                    int orientation = angleOrientation(verticesIn[nextIdx], verticesIn[i], verticesIn[j]);
                    if(orientation == CLOCKWISE){
                        nextOnHull = false;
                        break;
                    }
                }
            }
            if(nextOnHull){
                nextIdx = i;
                verticesOut.push_back(verticesIn[nextIdx]);
                break;
            }
        }
    }while(nextIdx != farLeftIndex);

    if(verticesOut.size() > 8){
        int endIndex1 = -1, endIndex2 = -1;
        for(i = 0; i < verticesOut.size(); ++i){
            if(fabs(verticesOut[i].y) < 0.01){
                
            }else if(floatSign(verticesOut[i].y) * floatSign(verticesOut[i].y) == -1){

            }
        }
    }

    return b2PolygonShape();
}