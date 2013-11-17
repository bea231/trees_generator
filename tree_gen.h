/* Sergeev Artemiy, 33601/2 (3057/2) */

#ifndef _TREE_GEN_H_
#define _TREE_GEN_H_

#include <stdio.h>

/* Unique layout of rooted tree representation class.
 * Comment: layout of tree is the lexicographically greatest
 * distance sequence L(T, z) = [l1, l2, ..., ln], where
 * li is a distance from the i-th vertex to root 'z' */
class tree_layout
{
protected:
  unsigned int *labels;   // Array of vertices labels (distance to root)
  unsigned int labelsCount;
public:
  /* Default class constructor */
  tree_layout( unsigned int verticesCount );
  /* Copying constructor */
  tree_layout( const tree_layout &layout );
  /* Class destructor */
  ~tree_layout( void )
  {
    if (labels)
      delete[] labels;
    labelsCount = 0;
  }

  /* Allow to get and set 'index'-th label from layout function */
  unsigned int & operator[]( unsigned int index )
  {
    return labels[index % labelsCount];
  }

  /* Return size of labels array (count of vertices in tree) function */
  unsigned int size( void ) const
  {
    return labelsCount;
  }

  /* Search a maximum vertex label in 'labels' array function */
  unsigned int max( void ) const;
  /* Assignment new layout operator */
  tree_layout & operator=( const tree_layout &layout );
  /* Check tree for n-path rooted case function */
  bool isSimple( void ) const;
  /* Calculate height of left subtree function */
  unsigned int leftHeight( void ) const;
};

/* Compare two layouts with equal vertices count operator (compare lexicographically) */
bool operator<=( tree_layout &layout1, tree_layout &layout2 );
/* Check non-equal operator */
bool operator!=( tree_layout &layout1, tree_layout &layout2 );

/* Generator new layout helpful class */
class tree_generator
{
public:
  /* Construct new layout from some layout function.
   * (input) p - index of label for start */
  static tree_layout successor( tree_layout &layout, unsigned int p = 0 );
  /* Build next tree layout by some layout */
  static tree_layout buildLayout( tree_layout &layout );
};

#endif /* _TREE_GEN_H_ */
