//
// Created by luiz0tavio on 6/10/18.
//

#ifndef HEDGEHOG_OBJECT3D_HPP
#define HEDGEHOG_OBJECT3D_HPP

#include <assimp/scene.h>
#include <assimp/cimport.h>
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/cexport.h>

namespace Renderer
{
    class Object3D
    {
        Object3D(const std::string& file_path)
        {
            Assimp::Importer Importer;
            const aiScene* pScene = Importer.ReadFile(file_path.c_str(),
                aiProcess_Triangulate |
                aiProcess_GenSmoothNormals |
                aiProcess_FlipUVs);

            if (pScene && pScene->HasMeshes()) {

                for (int i = 0; i < pScene->mNumMeshes; i++) {

                    //Position pos{.x = , .y = , .z = };
                    //Size size{};
                    //auto* object = new Renderer::Object2D();
                }

            } else {
                printf("Error parsing '%s': '%s'\n", file_path.c_str(), Importer.GetErrorString());
            }

        }

    };
}



#endif //HEDGEHOG_OBJECT3D_HPP
