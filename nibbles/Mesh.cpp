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

void Mesh::computeHull(){
    
    std::vector<b2Vec2> verticesIn = std::vector<b2Vec2>();
    std::vector<b2Vec2> verticesOut = std::vector<b2Vec2>();

    unsigned int i = 0;
    unsigned int j = 0;

    //transfer vertices and compute radius
    maxRadius = 0;
    for(i = startvertex; i < startvertex + numvertices; ++i){
        //get vertex
        b2Vec2 vertex(indexed_vertices[i].x, indexed_vertices[i].z);
        
        //compute radius
        float curRad = vertex.Length();
        if(curRad > maxRadius){
            maxRadius = curRad;
        }

        //push to vector
        verticesIn.push_back(vertex);
    }

    //remove duplicates
    for(i = 0; i < verticesIn.size(); ++i){
        for(j = i+1; j < verticesIn.size();){
            if( (fabs(verticesIn[i].x - verticesIn[j].x) < 0.01) && 
                    (fabs(verticesIn[i].y - verticesIn[j].y) < 0.01) ){
                verticesIn.erase(verticesIn.begin() + j);
            }else{
                ++j;
            }
        }
    }

    //find furthest left vertex
    float farLeft = verticesIn[0].x;
    int farLeftIndex = 0;
    for(i = 1; i < verticesIn.size(); ++i){
        if(verticesIn[i].x < farLeft){
            farLeft = verticesIn[i].x;
            farLeftIndex = i;
        }
    }

    unsigned int curIdx = farLeftIndex;
    verticesOut.push_back(verticesIn[farLeftIndex]);

    //create hull wrap vertices (counter clockwise order)
    do{
        for(i = 0; i < verticesIn.size(); ++i){
            if(curIdx != i){
                bool nextOnHull = true;
                for(j = 0; j < verticesIn.size(); ++j){
                    if(curIdx != j && i != j){
                        int orientation = angleOrientation(verticesIn[curIdx], verticesIn[i], verticesIn[j]);
                        if(orientation == CLOCKWISE || (orientation == COLINEAR && (
                                    (floatSign(verticesIn[curIdx].x - verticesIn[i].x) == 
                                    floatSign(verticesIn[i].x - verticesIn[j].x)) &&
                                    (floatSign(verticesIn[curIdx].y - verticesIn[i].y) == 
                                    floatSign(verticesIn[i].y - verticesIn[j].y))  ) ) ){
                            nextOnHull = false;
                            break;
                        }
                    }
                }
                if(nextOnHull){
                    curIdx = i;
                    verticesOut.push_back(verticesIn[curIdx]);
                    break;
                }
            }
        }
    }while(curIdx != farLeftIndex);

    if(verticesOut.size() > 8){
        std::size_t halfSize = verticesOut.size()/2;
        std::vector<b2Vec2> out1(verticesOut.begin(), verticesOut.begin() + halfSize + 1);
        std::vector<b2Vec2> out2(verticesOut.begin() + halfSize, verticesOut.end());
        out2.push_back(verticesOut[0]);
        hullPoly.push_back(out1);
        hullPoly.push_back(out2);
    }else{
        hullPoly.push_back(verticesOut);
    }

    hullValid = true;
    
}

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
    computeHull();
}

std::vector<std::vector<b2Vec2> > & Mesh::getHullPoly(){
    if(valid && !hullValid){
        computeHull();
    }
    return hullPoly;
}

float Mesh::getRadius(){
    if(valid && !hullValid){
        computeHull();
    }
    return maxRadius;
}