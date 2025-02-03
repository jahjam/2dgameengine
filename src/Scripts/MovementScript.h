#pragma once

#include "RigidBodyProp.h"
#include "Script.h"
#include "Store.h"
#include "TransformProp.h"

class MovementScript : public Script
{
   public:
    MovementScript()
    {
        requireProp<TransformProp>();
        requireProp<RigidBodyProp>();
    }

    void giveDirections_(double deltaTime)
    {
        for (auto actor : getScriptActors_())
        {
            auto actorName = actor->getName();
            TransformProp transformProp = Store<TransformProp>().get(actorName);
            RigidBodyProp rigidBodyProp = Store<RigidBodyProp>().get(actorName);

            // previous position
            transformProp.previousPosition.x = transformProp.position.x;
            transformProp.previousPosition.y = transformProp.position.y;

            // new position
            transformProp.position.x += rigidBodyProp.velocity.x * deltaTime;
            transformProp.position.y += rigidBodyProp.velocity.y * deltaTime;
        }
    }
};
