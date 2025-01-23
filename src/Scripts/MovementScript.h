#pragma once

#include "RigidBodyProp.h"
#include "Script.h"
#include "TransformProp.h"
#include "easylogging++.h"

class MovementScript : public Script
{
   public:
    MovementScript()
    {
        requireProp_(TransformProp());
        requireProp_(RigidBodyProp());
    }

    void giveDirections_(std::unordered_map<std::string, IStore *> *propStores,
                         double deltaTime) override
    {
        for (auto actor : getScriptActors_())
        {
            auto endIt = propStores->end();
            auto tranformIt = propStores->find("TransformProp");
            auto rigidBodyIt = propStores->find("RigidBodyProp");

            if (tranformIt == endIt || rigidBodyIt == endIt)
            {
                LOG(FATAL) << "Tried to access a prop that doesn't exist";
            }

            TransformProp *transformProp =
                static_cast<TransformProp *>(tranformIt->second->get(actor->getName()));
            RigidBodyProp *rigidBodyProp =
                static_cast<RigidBodyProp *>(rigidBodyIt->second->get(actor->getName()));

            if (!transformProp || !rigidBodyProp)
            {
                LOG(FATAL) << "Casting has failed!";
            }

            // previous position
            transformProp->previousPosition.x = transformProp->position.x;
            transformProp->previousPosition.y = transformProp->position.y;

            // new position
            transformProp->position.x += rigidBodyProp->velocity.x * deltaTime;
            transformProp->position.y += rigidBodyProp->velocity.y * deltaTime;
        }
    }

    Script *clone_() const override { return new MovementScript(*this); };
};
