#include "TriggerBot.h"
#include "../Main/Modules/Butix.h"
#include <chrono>
#include <thread>
#include "../Main/options.h"
#include "../Main/Classes/CPlayer.h"
#include <random>

int getRandom(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

void TriggerBot::run() {
    static auto lastAttackTime = std::chrono::steady_clock::now();
    auto currentTime = std::chrono::steady_clock::now();

    int del = options::triggerbot::delay;
    int fms = options::triggerbot::randomFactorMs;
    std::chrono::milliseconds attackInterval = (std::chrono::milliseconds)getRandom(del - fms, del + fms);

    if (std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - lastAttackTime) >= attackInterval) {
        auto entity_obj = minecraft::instance->getObjectPosition();
        if (entity_obj != nullptr) {
            auto entity = std::make_unique<entity::CEntity>(entity_obj);

            int chance = getRandom(0, 100);

            if (chance <= options::triggerbot::hitChance) {
                if (checkEntity(std::move(entity))) {
                    mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
                    mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
                }
            }

            lastAttackTime = currentTime;
        }
    }
}

bool TriggerBot::checkEntity(std::unique_ptr<entity::CEntity> entity) {
    if (entity->isDead()) return false;
    if (options::triggerbot::distance != 4.f) {
        vec3 entityPos = entity->getPosition();

        vec3 playerPos = player::instance->getPosition();

        float distance = vec3::distance(entityPos, playerPos) - 1;

        if (distance > options::triggerbot::distance) return false;
    }

    int entityType = entity->getEntityType();

    if ((entityType == 5 && options::triggerbot::attackMobs) ||
        (entityType == 10 && options::triggerbot::attackMobs) ||
        (entityType == 0 && options::triggerbot::attackPlayers)) {

        if (entity->isInvisible() && options::triggerbot::attackInvisibles || !entity->isInvisible()) {

            if (!player::instance->getLastOnGround() && options::triggerbot::onlyCrits || !options::triggerbot::onlyCrits) {
                return true;
            }
        }
    }

    return false;
}