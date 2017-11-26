// Copyright (c) 1989-2008 James E. Wilson, Robert A. Koeneke, David J. Grabiner
//
// Umoria is free software released under a GPL v2 license and comes with
// ABSOLUTELY NO WARRANTY. See https://www.gnu.org/licenses/gpl-2.0.html
// for further details.

// Functions related to Player stats

#include "headers.h"
#include "externs.h"

// Adjustment for wisdom/intelligence -JWT-
int playerStatAdjustmentWisdomIntelligence(int stat) {
    int value = py.stats.used[stat];

    int adjustment;

    if (value > 117) {
        adjustment = 7;
    } else if (value > 107) {
        adjustment = 6;
    } else if (value > 87) {
        adjustment = 5;
    } else if (value > 67) {
        adjustment = 4;
    } else if (value > 17) {
        adjustment = 3;
    } else if (value > 14) {
        adjustment = 2;
    } else if (value > 7) {
        adjustment = 1;
    } else {
        adjustment = 0;
    }

    return adjustment;
}

// Adjustment for charisma -RAK-
// Percent decrease or increase in price of goods
int playerStatAdjustmentCharisma() {
    int charisma = py.stats.used[A_CHR];

    if (charisma > 117) {
        return 90;
    }

    if (charisma > 107) {
        return 92;
    }

    if (charisma > 87) {
        return 94;
    }

    if (charisma > 67) {
        return 96;
    }

    if (charisma > 18) {
        return 98;
    }

    switch (charisma) {
        case 18:
            return 100;
        case 17:
            return 101;
        case 16:
            return 102;
        case 15:
            return 103;
        case 14:
            return 104;
        case 13:
            return 106;
        case 12:
            return 108;
        case 11:
            return 110;
        case 10:
            return 112;
        case 9:
            return 114;
        case 8:
            return 116;
        case 7:
            return 118;
        case 6:
            return 120;
        case 5:
            return 122;
        case 4:
            return 125;
        case 3:
            return 130;
        default:
            return 100;
    }
}

// Returns a character's adjustment to hit points -JWT-
int playerStatAdjustmentConstitution() {
    int con = py.stats.used[A_CON];

    if (con < 7) {
        return (con - 7);
    }

    if (con < 17) {
        return 0;
    }

    if (con == 17) {
        return 1;
    }

    if (con < 94) {
        return 2;
    }

    if (con < 117) {
        return 3;
    }

    return 4;
}

static uint8_t playerModifyStat(int stat, int16_t amount) {
    uint8_t new_stat = py.stats.current[stat];

    int loop = (amount < 0 ? -amount : amount);

    for (int i = 0; i < loop; i++) {
        if (amount > 0) {
            if (new_stat < 18) {
                new_stat++;
            } else if (new_stat < 108) {
                new_stat += 10;
            } else {
                new_stat = 118;
            }
        } else {
            if (new_stat > 27) {
                new_stat -= 10;
            } else if (new_stat > 18) {
                new_stat = 18;
            } else if (new_stat > 3) {
                new_stat--;
            }
        }
    }

    return new_stat;
}

// Set the value of the stat which is actually used. -CJS-
void playerSetAndUseStat(int stat) {
    py.stats.used[stat] = playerModifyStat(stat, py.stats.modified[stat]);

    if (stat == A_STR) {
        py.flags.status |= PY_STR_WGT;
        playerRecalculateBonuses();
    } else if (stat == A_DEX) {
        playerRecalculateBonuses();
    } else if (stat == A_INT && classes[py.misc.class_id].class_to_use_mage_spells == SPELL_TYPE_MAGE) {
        playerCalculateAllowedSpellsCount(A_INT);
        playerGainMana(A_INT);
    } else if (stat == A_WIS && classes[py.misc.class_id].class_to_use_mage_spells == SPELL_TYPE_PRIEST) {
        playerCalculateAllowedSpellsCount(A_WIS);
        playerGainMana(A_WIS);
    } else if (stat == A_CON) {
        playerCalculateHitPoints();
    }
}

// Increases a stat by one randomized level -RAK-
bool playerStatRandomIncrease(int stat) {
    int new_stat = py.stats.current[stat];

    if (new_stat >= 118) {
        return false;
    }

    if (new_stat < 18) {
        new_stat++;
    } else if (new_stat < 116) {
        // stat increases by 1/6 to 1/3 of difference from max
        int gain = ((118 - new_stat) / 3 + 1) >> 1;

        new_stat += randomNumber(gain) + gain;
    } else {
        new_stat++;
    }

    py.stats.current[stat] = (uint8_t) new_stat;

    if (new_stat > py.stats.max[stat]) {
        py.stats.max[stat] = (uint8_t) new_stat;
    }

    playerSetAndUseStat(stat);
    displayCharacterStats(stat);

    return true;
}

// Decreases a stat by one randomized level -RAK-
bool playerStatRandomDecrease(int stat) {
    int new_stat = py.stats.current[stat];

    if (new_stat <= 3) {
        return false;
    }

    if (new_stat < 19) {
        new_stat--;
    } else if (new_stat < 117) {
        int loss = (((118 - new_stat) >> 1) + 1) >> 1;
        new_stat += -randomNumber(loss) - loss;

        if (new_stat < 18) {
            new_stat = 18;
        }
    } else {
        new_stat--;
    }

    py.stats.current[stat] = (uint8_t) new_stat;

    playerSetAndUseStat(stat);
    displayCharacterStats(stat);

    return true;
}

// Restore a stat.  Return true only if this actually makes a difference.
bool playerStatRestore(int stat) {
    int new_stat = py.stats.max[stat] - py.stats.current[stat];

    if (new_stat == 0) {
        return false;
    }

    py.stats.current[stat] += new_stat;

    playerSetAndUseStat(stat);
    displayCharacterStats(stat);

    return true;
}

// Boost a stat artificially (by wearing something). If the display
// argument is true, then increase is shown on the screen.
void playerStatBoost(int stat, int amount) {
    py.stats.modified[stat] += amount;

    playerSetAndUseStat(stat);

    // can not call displayCharacterStats() here:
    //   might be in a store,
    //   might be in inventoryExecuteCommand()
    py.flags.status |= (PY_STR << stat);
}

// Returns a character's adjustment to hit. -JWT-
int playerToHitAdjustment() {
    int total;

    int dexterity = py.stats.used[A_DEX];
    if (dexterity < 4) {
        total = -3;
    } else if (dexterity < 6) {
        total = -2;
    } else if (dexterity < 8) {
        total = -1;
    } else if (dexterity < 16) {
        total = 0;
    } else if (dexterity < 17) {
        total = 1;
    } else if (dexterity < 18) {
        total = 2;
    } else if (dexterity < 69) {
        total = 3;
    } else if (dexterity < 118) {
        total = 4;
    } else {
        total = 5;
    }

    int strength = py.stats.used[A_STR];
    if (strength < 4) {
        total -= 3;
    } else if (strength < 5) {
        total -= 2;
    } else if (strength < 7) {
        total -= 1;
    } else if (strength < 18) {
        total -= 0;
    } else if (strength < 94) {
        total += 1;
    } else if (strength < 109) {
        total += 2;
    } else if (strength < 117) {
        total += 3;
    } else {
        total += 4;
    }

    return total;
}

// Returns a character's adjustment to armor class -JWT-
int playerArmorClassAdjustment() {
    int stat = py.stats.used[A_DEX];

    int adjustment;

    if (stat < 4) {
        adjustment = -4;
    } else if (stat == 4) {
        adjustment = -3;
    } else if (stat == 5) {
        adjustment = -2;
    } else if (stat == 6) {
        adjustment = -1;
    } else if (stat < 15) {
        adjustment = 0;
    } else if (stat < 18) {
        adjustment = 1;
    } else if (stat < 59) {
        adjustment = 2;
    } else if (stat < 94) {
        adjustment = 3;
    } else if (stat < 117) {
        adjustment = 4;
    } else {
        adjustment = 5;
    }

    return adjustment;
}

// Returns a character's adjustment to disarm -RAK-
int playerDisarmAdjustment() {
    int stat = py.stats.used[A_DEX];

    int adjustment;

    if (stat < 4) {
        adjustment = -8;
    } else if (stat == 4) {
        adjustment = -6;
    } else if (stat == 5) {
        adjustment = -4;
    } else if (stat == 6) {
        adjustment = -2;
    } else if (stat == 7) {
        adjustment = -1;
    } else if (stat < 13) {
        adjustment = 0;
    } else if (stat < 16) {
        adjustment = 1;
    } else if (stat < 18) {
        adjustment = 2;
    } else if (stat < 59) {
        adjustment = 4;
    } else if (stat < 94) {
        adjustment = 5;
    } else if (stat < 117) {
        adjustment = 6;
    } else {
        adjustment = 8;
    }

    return adjustment;
}

// Returns a character's adjustment to damage -JWT-
int playerDamageAdjustment() {
    int stat = py.stats.used[A_STR];

    int adjustment;

    if (stat < 4) {
        adjustment = -2;
    } else if (stat < 5) {
        adjustment = -1;
    } else if (stat < 16) {
        adjustment = 0;
    } else if (stat < 17) {
        adjustment = 1;
    } else if (stat < 18) {
        adjustment = 2;
    } else if (stat < 94) {
        adjustment = 3;
    } else if (stat < 109) {
        adjustment = 4;
    } else if (stat < 117) {
        adjustment = 5;
    } else {
        adjustment = 6;
    }

    return adjustment;
}
