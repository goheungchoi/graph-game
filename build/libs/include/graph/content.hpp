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

class Content {
public:
  int type;
  int rarity;

  Content();  // Default constructor

  Content(const Content& other);  // Copy constructor

  Content(const int type, const int rarity);

  Content& operator=(const Content& other); // Copy operator

};

#endif