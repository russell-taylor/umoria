// Copyright (c) 1989-2008 James E. Wilson, Robert A. Koeneke, David J. Grabiner
//
// Umoria is free software released under a GPL v2 license and comes with
// ABSOLUTELY NO WARRANTY. See https://www.gnu.org/licenses/gpl-2.0.html
// for further details.

// Declarations for global variables and initialized data

extern int hack_monptr;

extern FILE *highscore_fp;

extern Config_t config;
extern Game_t game;
extern Dungeon_t dg;

extern bool screen_has_changed;

extern bool teleport_player;

extern bool message_ready_to_print;
extern vtype_t messages[MESSAGE_HISTORY_SIZE];
extern int16_t last_message_id;

// Converted to uint16_t when saving the game.
extern int16_t missiles_counter;

extern int eof_flag;
extern bool panic_save;

// Following are player variables
extern Player_t py;

extern ClassRankTitle_t class_rank_titles[PLAYER_MAX_CLASSES][PLAYER_MAX_LEVEL];
extern Race_t character_races[PLAYER_MAX_RACES];
extern Background_t character_backgrounds[PLAYER_MAX_BACKGROUNDS];

extern uint8_t race_gold_adjustments[PLAYER_MAX_RACES][PLAYER_MAX_RACES];

extern Class_t classes[PLAYER_MAX_CLASSES];
extern int16_t class_level_adj[PLAYER_MAX_CLASSES][CLASS_MAX_LEVEL_ADJUST];
extern uint16_t class_base_provisions[PLAYER_MAX_CLASSES][5];

// Warriors don't have spells, so there is no entry for them.
extern Spell_t magic_spells[PLAYER_MAX_CLASSES - 1][31];
extern char *spell_names[62];

// Following are store definitions
extern Owner_t store_owners[MAX_OWNERS];
extern Store_t stores[MAX_STORES];
extern uint16_t store_choices[MAX_STORES][STORE_MAX_ITEM_TYPES];
extern bool (*store_buy[MAX_STORES])(int);
extern const char *speech_sale_accepted[14];
extern const char *speech_selling_haggle_final[3];
extern const char *speech_selling_haggle[16];
extern const char *speech_buying_haggle_final[3];
extern const char *speech_buying_haggle[15];
extern const char *speech_insulted_haggling_done[5];
extern const char *speech_get_out_of_my_store[5];
extern const char *speech_haggling_try_again[10];
extern const char *speech_sorry[5];

// Following are treasure arrays  and variables
extern GameObject_t game_objects[MAX_OBJECTS_IN_GAME];
extern uint8_t objects_identified[OBJECT_IDENT_SIZE];
extern int16_t treasure_levels[TREASURE_MAX_LEVELS + 1];
extern Inventory_t treasure_list[LEVEL_MAX_OBJECTS];
extern Inventory_t inventory[PLAYER_INVENTORY_SIZE];
extern char *special_item_names[SN_ARRAY_SIZE];
extern int16_t sorted_objects[MAX_DUNGEON_OBJECTS];

extern int16_t current_treasure_id;

// Following are creature arrays and variables
extern Creature_t creatures_list[MON_MAX_CREATURES];
extern Monster_t monsters[MON_TOTAL_ALLOCATIONS];
extern int16_t monster_levels[MON_MAX_LEVELS + 1];
extern MonsterAttack_t monster_attacks[MON_ATTACK_TYPES];
extern Recall_t creature_recall[MON_MAX_CREATURES]; // Monster memories. -CJS-
extern Monster_t blank_monster;
extern int16_t next_free_monster_id;
extern int16_t monster_multiply_total;
extern const char *recall_description_attack_type[25];
extern const char *recall_description_attack_method[20];
extern const char *recall_description_how_much[8];
extern const char *recall_description_move[6];
extern const char *recall_description_spell[15];
extern const char *recall_description_breath[5];
extern const char *recall_description_weakness[6];

// Following are arrays for descriptive pieces
extern const char *colors[MAX_COLORS];
extern const char *mushrooms[MAX_MUSHROOMS];
extern const char *woods[MAX_WOODS];
extern const char *metals[MAX_METALS];
extern const char *rocks[MAX_ROCKS];
extern const char *amulets[MAX_AMULETS];
extern const char *syllables[MAX_SYLLABLES];

extern uint8_t blows_table[7][6];

extern uint16_t normal_table[NORMAL_TABLE_SIZE];


// Function return values
//
// Only extern functions declared here, static functions
// declared inside the file that defines them.

// create.c
void characterCreate();

// death.c
void exitGame();

// desc.c
void magicInitializeItemNames();
int16_t objectPositionOffset(int category_id, int sub_category_id);
void itemSetAsIdentified(int category_id, int sub_category_id);
bool itemSetColorlessAsIdentified(int category_id, int sub_category_id, int identification);
void spellItemIdentifyAndRemoveRandomInscription(Inventory_t &item);
bool spellItemIdentified(const Inventory_t &item);
void spellItemRemoveIdentification(Inventory_t &item);
void itemIdentificationClearEmpty(Inventory_t &item);
void itemIdentifyAsStoreBought(Inventory_t &item);
bool itemStoreBought(int identification);
void itemSetAsTried(const Inventory_t &item);
void itemIdentify(Inventory_t &item, int &item_id);
void itemRemoveMagicNaming(Inventory_t &item);
void itemDescription(obj_desc_t description, const Inventory_t &item, bool add_prefix);
void itemChargesRemainingDescription(int item_id);
void itemTypeRemainingCountDescription(int item_id);

// generate.c
void generateCave();

// help.c
void displayWorldObjectDescription();

#ifndef _WIN32
// call functions which expand tilde before calling open/fopen
#define open topen
#define fopen tfopen

FILE *tfopen(const char *file, const char *mode);
int topen(const char *file, int flags, int mode);
bool tilde(const char *file, char *expanded);
#endif

bool checkFilePermissions();

// los.cpp
bool los(int from_y, int from_x, int to_y, int to_x);
void look();

// magic.c
void getAndCastMagicSpell();

// misc1.c
int diceDamageRoll(int dice, int sides);
int dicePlayerDamageRoll(uint8_t *notation_array);
int popt();
void pusht(uint8_t treasure_id);

// misc2.c
void magicTreasureMagicalAbility(int item_id, int level);

// misc3.c
int itemGetRandomObjectId(int level, bool must_be_small);
void statsAsString(uint8_t stat, char *stat_string);
void displayCharacterStats(int stat);
char *playerTitle();
void printCharacterTitle();
void printCharacterLevel();
void printCharacterCurrentMana();
void printCharacterMaxHitPoints();
void printCharacterCurrentHitPoints();
void printCharacterCurrentArmorClass();
void printCharacterGoldValue();
void printCharacterCurrentDepth();
void printCharacterHungerStatus();
void printCharacterBlindStatus();
void printCharacterConfusedState();
void printCharacterFearState();
void printCharacterPoisonedState();
void printCharacterMovementState();
void printCharacterSpeed();
void printCharacterStudyInstruction();
void printCharacterWinner();
void printCharacterStatsBlock();
void printCharacterInformation();
void printCharacterStats();
const char *statRating(int y, int x);
void printCharacterVitalStatistics();
void printCharacterLevelExperience();
void printCharacterAbilities();
void printCharacter();
void getCharacterName();
void changeCharacterName();
int playerCarryingLoadLimit();
void playerStrength();
void displaySpellsList(const int *spell_ids, int number_of_choices, bool comment, int non_consecutive);
bool spellGetId(int *spell_ids, int number_of_choices, int &spell_id, int &spell_chance, const char *prompt, int first_spell);
void playerCalculateAllowedSpellsCount(int stat);
void playerGainSpells();
void playerGainMana(int stat);
void displayCharacterExperience();
bool enterWizardMode();
int itemMagicAbilityDamage(const Inventory_t &item, int total_damage, int monster_id);
int playerWeaponCriticalBlow(int weapon_weight, int plus_to_hit, int damage, int attack_type_id);
bool playerSavingThrow();

// misc4.c
void itemInscribe();
void itemAppendToInscription(Inventory_t &item, uint8_t item_ident_type);
void itemReplaceInscription(Inventory_t &item, const char *inscription);

// monster_management.cpp
bool compactMonsters();
bool monsterPlaceNew(int y, int x, int creature_id, bool sleeping);
void monsterPlaceWinning();
void monsterPlaceNewWithinDistance(int number, int distance_from_source, bool sleeping);
bool monsterSummon(int &y, int &x, bool sleeping);
bool monsterSummonUndead(int &y, int &x);

// moria.cpp - also includes the main dungeon game loop: playDungeon()
void startMoria(int seed, bool start_new_game, bool use_roguelike_keys);

// moria1.c
void playerChangeSpeed(int speed);
void playerAdjustBonusesForItem(const Inventory_t &item, int factor);
void playerRecalculateBonuses();
int displayInventory(int item_id_start, int item_id_end, bool weighted, int column, const char *mask);
const char *playerItemWearingDescription(int body_location);
int displayEquipment(bool weighted, int column);
void playerTakeOff(int item_id, int pack_position_id);
void inventoryExecuteCommand(char command);
bool inventoryGetInputForItemId(int &command_key_id, const char *prompt, int item_id_start, int item_id_end, char *mask, const char *message);
bool getDirectionWithMemory(char *prompt, int &direction);
bool getAllDirections(const char *prompt, int &direction);
bool playerTestBeingHit(int base_to_hit, int level, int plus_to_hit, int armor_class, int attack_type_id);
void playerTakesHit(int damage, const char *creature_name);

// moria2.c
void dungeonChangeTrapVisibility(int y, int x);
void dungeonSearch(int y, int x, int chance);
void damageCorrodingGas(const char *creature_name);
void damagePoisonedGas(int damage, const char *creature_name);
void damageFire(int damage, const char *creature_name);
void damageCold(int damage, const char *creature_name);
void damageLightningBolt(int damage, const char *creature_name);
void damageAcid(int damage, const char *creature_name);

// moria3.c
int castSpellGetId(const char *prompt, int item_id, int &spell_id, int &spell_chance);
void playerGainKillExperience(const Creature_t &creature);
void chestTrap(int y, int x);
void objectOpen();
void dungeonCloseDoor();
bool dungeonTunnelWall(int y, int x, int digging_ability, int digging_chance);
void objectBlockedByMonster(int monster_id);
void playerAttackPosition(int y, int x);
int getRandomDirection();

// player_eat.cpp
void playerEat();
void playerIngestFood(int amount);

// player_bash.cpp
void playerBash();

// player_magic.cpp
bool playerCureConfusion();
bool playerCureBlindness();
bool playerCurePoison();
bool playerRemoveFear();
bool playerProtectEvil();
void playerBless(int adjustment);
void playerDetectInvisible(int adjustment);

// player_move.cpp
void playerMove(int direction, bool do_pickup);

// player_run.cpp
void playerFindInitialize(int direction);
void playerRunAndFind();
void playerEndRunning();
void playerAreaAffect(int direction, int y, int x);

// player_stats.cpp
int playerStatAdjustmentWisdomIntelligence(int stat);
int playerStatAdjustmentCharisma();
int playerStatAdjustmentConstitution();
void playerSetAndUseStat(int stat);
bool playerStatRandomIncrease(int stat);
bool playerStatRandomDecrease(int stat);
bool playerStatRestore(int stat);
void playerStatBoost(int stat, int amount);
int playerToHitAdjustment();
int playerArmorClassAdjustment();
int playerDisarmAdjustment();
int playerDamageAdjustment();

// player_throw.cpp
void playerThrowItem();

// player_traps.cpp
void playerDisarmTrap();

// player_tunnel.cpp
void playerTunnel(int direction);

// potions.c
void quaff();

// prayer.c
void pray();

// recall.c
bool memoryMonsterKnown(const Recall_t &memory);
int memoryRecall(int monster_id);

// rng.cpp
uint32_t getRandomSeed();
void setRandomSeed(uint32_t seed);
int32_t rnd();

// save.c
bool saveGame();
bool loadGame(bool &generate);
void setFileptr(FILE *file);
void saveHighScore(const HighScore_t &score);
void readHighScore(HighScore_t &score);

// scrolls.c
void readScroll();

// sets.c
bool setRooms(int tile_id);
bool setCorridors(int tile_id);
bool setFloors(int tile_id);
bool setCorrodableItems(Inventory_t *item);
bool setFlammableItems(Inventory_t *item);
bool setFrostDestroyableItems(Inventory_t *item);
bool setAcidAffectedItems(Inventory_t *item);
bool setLightningDestroyableItems(Inventory_t *item);
bool setNull(Inventory_t *item);
bool setAcidDestroyableItems(Inventory_t *item);
bool setFireDestroyableItems(Inventory_t *item);
bool setItemsLargerThanChests(GameObject_t *item);
bool setGeneralStoreItems(int item_id);
bool setArmoryItems(int item_id);
bool setWeaponsmithItems(int item_id);
bool setTempleItems(int item_id);
bool setAlchemistItems(int item_id);
bool setMagicShopItems(int item_id);

// spells.c
bool dungeonDetectTreasureOnPanel();
bool dungeonDetectObjectOnPanel();
bool dungeonDetectTrapOnPanel();
bool dungeonDetectSecretDoorsOnPanel();
bool spellDetectInvisibleCreaturesOnPanel();
bool spellLightArea(int y, int x);
bool spellDarkenArea(int y, int x);
void spellMapCurrentArea();
bool spellIdentifyItem();
bool spellAggravateMonsters(int affect_distance);
bool spellSurroundPlayerWithTraps();
bool spellSurroundPlayerWithDoors();
bool spellDestroyAdjacentDoorsTraps();
bool spellDetectMonsters();
void spellLightLine(int x, int y, int direction);
void spellStarlite(int y, int x);
bool spellDisarmAllInDirection(int y, int x, int direction);
void spellFireBolt(int y, int x, int direction, int damage_hp, int spell_type, const std::string &spell_name);
void spellFireBall(int y, int x, int direction, int damage_hp, int spell_type, const std::string &spell_name);
void spellBreath(int y, int x, int monster_id, int damage_hp, int spell_type, const std::string &spell_name);
bool spellRechargeItem(int number_of_charges);
bool spellChangeMonsterHitPoints(int y, int x, int direction, int damage_hp);
bool spellDrainLifeFromMonster(int y, int x, int direction);
bool spellSpeedMonster(int y, int x, int direction, int speed);
bool spellConfuseMonster(int y, int x, int direction);
bool spellSleepMonster(int y, int x, int direction);
bool spellWallToMud(int y, int x, int direction);
bool spellDestroyDoorsTrapsInDirection(int y, int x, int direction);
bool spellPolymorphMonster(int y, int x, int direction);
bool spellBuildWall(int y, int x, int direction);
bool spellCloneMonster(int y, int x, int direction);
void spellTeleportAwayMonster(int monster_id, int distance_from_player);
void spellTeleportPlayerTo(int y, int x);
bool spellTeleportAwayMonsterInDirection(int y, int x, int direction);
bool spellMassGenocide();
bool spellGenocide();
bool spellSpeedAllMonsters(int speed);
bool spellSleepAllMonsters();
bool spellMassPolymorph();
bool spellDetectEvil();
bool spellChangePlayerHitPoints(int adjustment);
void dungeonEarthquake();
void spellCreateFood();
bool spellDispelCreature(int creature_defense, int damage);
bool spellTurnUndead();
void spellWardingGlyph();
void spellLoseSTR();
void spellLoseINT();
void spellLoseWIS();
void spellLoseDEX();
void spellLoseCON();
void spellLoseCHR();
void spellLoseEXP(int32_t adjustment);
bool spellSlowPoison();
void spellDestroyArea(int y, int x);
bool spellEnchantItem(int16_t &plusses, int16_t max_bonus_limit);
bool spellRemoveCurseFromAllItems();
bool spellRestorePlayerLevels();

// staffs.c
void useStaff();

// wands.c
void wandAim();

// wizard.c
void wizardLightUpDungeon();
void wizardCharacterAdjustment();
void wizardGenerateObject();
void wizardCreateObjects();
