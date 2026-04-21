#ifndef CORE_TRACK_COLLISION_COMPONENT_HPP
#define CORE_TRACK_COLLISION_COMPONENT_HPP

#include "Core/Physics.hpp"
#include "Core/CollisionMeshData.hpp"
#include <BulletCollision/CollisionShapes/btTriangleMesh.h>
#include <BulletCollision/CollisionShapes/btBvhTriangleMeshShape.h>
#include <memory>
#include <span>

class TrackCollisionComponent {
public:
    void Init(std::span<const CollisionMeshData> meshes, Physics& physic_world);
    void Destroy(Physics& physic_world);
    
private:
    std::unique_ptr<btTriangleMesh>         trackMesh;
    std::unique_ptr<btBvhTriangleMeshShape> trackShape;
    std::unique_ptr<btDefaultMotionState>   motion;
    std::unique_ptr<btRigidBody>            track;
};

#endif