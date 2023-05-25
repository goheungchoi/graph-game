#include "content.hpp"

/**
 * @brief Construct a new Content:: Content object
 * 
 */
Content::Content() {
  type = _NULL_TYPE;
  rarity = _NULL_RARITY;
}

/**
 * @brief Construct a new Content by copying another Content object
 * 
 * @param other Another Content object
 */
Content::Content(const Content& other) {
  if (this != &other) {
    this->type = other.type;
    this->type = other.rarity;
  }
}

/**
 * @brief Construct a new Content:: Content object
 * 
 * @param type _NULL_TYPE,  _ITEM, _ADD_ON, _OFFERING, _PERK
 * @param rarity _NULL_RARITY, _COMMON, _UNCOMMON (tier 1 perk), _RARE (tier 2 perk), _VERY_RARE (tier 3 perk), _ULTRA_RARE
 */
Content::Content(const int type, const int rarity) {
  this->type = type;
  this->rarity = rarity;
}

/**
 * @brief Copy operator
 * 
 * @param other Another Content object
 * @return Content& Content object gotten the copied Content
 */
Content& Content::operator=(const Content& other) {
  if (this != &other) {
    this->type = other.type;
    this->rarity = other.rarity;
  }
  return *this;
}