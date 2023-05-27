// content.hpp
#ifndef _CONTENT_
#define _CONTENT_

// types
#define _NULL_TYPE 0
#define _ITEM 100
#define _ADD_ON 101
#define _OFFERING 200
#define _PERK 300

// rarities
#define _NULL_RARITY 0
#define _COMMON 3000
#define _UNCOMMON 4000  // tier 1 perk
#define _RARE 5000  // tier 2 perk
#define _VERY_RARE 6000  // tier 3 perk
#define _ULTRA_RARE 7000

/**
 * @brief Content class shows more
 * detailed information about a node.
 * 
 */
class Content {
public:
  int type;   //!< Represents type of node
  int rarity; //!< Represents rarity of node

/**
 * @brief Default constructor
 * 
 */
  Content();
/**
 * @brief Copy constructor
 * 
 * @param other other Content object to be copied
 */
  Content(const Content& other);  
/**
 * @brief Construct a new Content object
 * 
 * @param type type of the node
 * @param rarity rarity of the node
 */
  Content(const int type, const int rarity);
/**
 * @brief Copy operator
 * 
 * @param other other Content object to be copied
 * @return Content& - Updated *this
 */
  Content& operator=(const Content& other);
};

#endif
