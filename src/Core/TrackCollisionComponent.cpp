#include "Core/TrackCollisionComponent.hpp"

void TrackCollisionComponent::Init(std::span<const CollisionMeshData> meshes, Physics& physic_world)
{
    trackMesh  = std::make_unique<btTriangleMesh>();
    for (const CollisionMeshData& mesh : meshes) {
        if (mesh.indices) {
            for (int i = 0; i < mesh.triangleCount; ++i) {
                auto idx0 = mesh.indices[i * 3 + 0];
                auto idx1 = mesh.indices[i * 3 + 1];
                auto idx2 = mesh.indices[i * 3 + 2];

                btVector3 v0(mesh.vertices[idx0 * 3], mesh.vertices[idx0 * 3 + 1], mesh.vertices[idx0 * 3 + 2]);
                btVector3 v1(mesh.vertices[idx1 * 3], mesh.vertices[idx1 * 3 + 1], mesh.vertices[idx1 * 3 + 2]);
                btVector3 v2(mesh.vertices[idx2 * 3], mesh.vertices[idx2 * 3 + 1], mesh.vertices[idx2 * 3 + 2]);
            
                trackMesh->addTriangle(v0, v1, v2);
            }
        }
        else {
            for (int i = 0, j = 0; i < mesh.triangleCount; ++i) {
                j = i * 9;

                btVector3 v0(mesh.vertices[j + 0], mesh.vertices[j + 1], mesh.vertices[j + 2]);
                btVector3 v1(mesh.vertices[j + 3], mesh.vertices[j + 4], mesh.vertices[j + 5]);
                btVector3 v2(mesh.vertices[j + 6], mesh.vertices[j + 7], mesh.vertices[j + 8]);
                
                trackMesh->addTriangle(v0, v1, v2);
            }
        }
    }

    trackShape = std::make_unique<btBvhTriangleMeshShape>(trackMesh.get(), true);
    
    motion = std::make_unique<btDefaultMotionState>(btTransform::getIdentity());
    btRigidBody::btRigidBodyConstructionInfo trackCI(0.f, motion.get(), trackShape.get());
    track = std::make_unique<btRigidBody>(trackCI);

    physic_world.addRigidBody(track.get());
}

void TrackCollisionComponent::Destroy(Physics& physic_world)
{
    physic_world.removeRigidBody(track.get());
}