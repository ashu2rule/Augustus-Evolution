#ifndef AE_HOUSING_AUDIT_H
#define AE_HOUSING_AUDIT_H

/* Augustus Evolution: read-only live housing diagnosis.
 * No changes to simulation state or save formats.
 * Service ceiling is NOT a guarantee: footprint availability and evolution
 * timing must also be evaluated by the engine.
 */
#include "building/building.h"
#include "building/properties.h"
#include "city/resource.h"
#include "game/resource.h"

typedef enum {
    AE_WATER = 0, AE_ENTERTAINMENT, AE_EDUCATION, AE_RELIGION,
    AE_BARBER, AE_BATH, AE_HEALTH, AE_FOOD, AE_POTTERY,
    AE_OIL, AE_FURNITURE, AE_WINE, AE_DESIRABILITY,
    AE_REQUIREMENT_COUNT
} ae_requirement;

typedef struct {
    int current_level;
    int target_level;
    int service_ceiling;
    unsigned int missing_mask;
    int missing_count;
    int missing_amount[AE_REQUIREMENT_COUNT];
} ae_house_audit;

static inline int ae_food_types(const building *house)
{
    int count = 0;
    for (resource_type r = RESOURCE_MIN_FOOD; r < RESOURCE_MAX_FOOD; ++r) {
        if (resource_is_inventory(r) && house->resources[r] > 0) ++count;
    }
    return count;
}

static inline unsigned int ae_house_missing(const building *house, int target,
                                             int *amount)
{
    const model_house *m = model_get_house((house_level) target);
    unsigned int bits = 0;
    for (int i = 0; i < AE_REQUIREMENT_COUNT; ++i) amount[i] = 0;
#define AE_DEFICIT(key, actual, required) do { \
    int deficit = (required) - (actual); \
    if (deficit > 0) { bits |= 1u << (key); amount[key] = deficit; } \
} while (0)
    /* Two means latrine OR fountain; three means fountain required. */
    int water = house->has_water_access ? 3 :
                house->has_latrines_access ? 2 :
                house->has_well_access ? 1 : 0;
    AE_DEFICIT(AE_WATER, water, m->water);
    AE_DEFICIT(AE_ENTERTAINMENT, house->data.house.entertainment, m->entertainment);
    AE_DEFICIT(AE_EDUCATION, house->data.house.education, m->education);
    AE_DEFICIT(AE_RELIGION, house->data.house.num_gods, m->religion > 5 ? 5 : m->religion);
    AE_DEFICIT(AE_BARBER, house->data.house.barber, m->barber);
    AE_DEFICIT(AE_BATH, house->data.house.bathhouse, m->bathhouse);
    AE_DEFICIT(AE_HEALTH, house->data.house.health, m->health);
    AE_DEFICIT(AE_FOOD, ae_food_types(house), m->food_types);
    AE_DEFICIT(AE_POTTERY, house->resources[RESOURCE_POTTERY], m->pottery);
    AE_DEFICIT(AE_OIL, house->resources[RESOURCE_OIL], m->oil);
    AE_DEFICIT(AE_FURNITURE, house->resources[RESOURCE_FURNITURE], m->furniture);
    /* Two wine types depend on city-wide access, not merely inventory. */
    int wine = house->resources[RESOURCE_WINE] > 0 ? 1 : 0;
    if (wine && m->wine > 1 && city_resource_multiple_wine_available()) wine = 2;
    AE_DEFICIT(AE_WINE, wine, m->wine);
    if (target > house->subtype.house_level) {
        const model_house *current = model_get_house((house_level) house->subtype.house_level);
        int required_desirability = current->evolve_desirability;
        if (house->desirability < required_desirability) {
            bits |= 1u << AE_DESIRABILITY;
            amount[AE_DESIRABILITY] = required_desirability - house->desirability;
        }
    }
#undef AE_DEFICIT
    return bits;
}

static inline ae_house_audit ae_house_evaluate(const building *house)
{
    ae_house_audit result = {0};
    result.current_level = house->subtype.house_level;
    result.target_level = result.current_level < HOUSE_MAX ? result.current_level + 1 : result.current_level;
    result.missing_mask = ae_house_missing(house, result.target_level, result.missing_amount);
    for (int i = 0; i < AE_REQUIREMENT_COUNT; ++i) {
        if (result.missing_mask & (1u << i)) ++result.missing_count;
    }
    /* This is a current-services ceiling, NOT a projected build-out maximum. */
    result.service_ceiling = result.current_level;
    for (int lvl = result.current_level + 1; lvl <= HOUSE_MAX; ++lvl) {
        int amount[AE_REQUIREMENT_COUNT];
        if (ae_house_missing(house, lvl, amount)) break;
        result.service_ceiling = lvl;
    }
    return result;
}
#endif
