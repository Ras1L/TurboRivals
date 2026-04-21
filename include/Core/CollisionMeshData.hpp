#ifndef CORE_COLLISION_MESH_DATA_HPP
#define CORE_COLLISION_MESH_DATA_HPP

struct CollisionMeshData {
    int             vertexCount;
    int             triangleCount;
    float*          vertices;
    unsigned short* indices;
};

#endif