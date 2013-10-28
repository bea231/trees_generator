/* Sergeev Artemiy, 33601/2 (3057/2) */

#include <stdio.h>

/* Unique layout of rooted tree representation class.
 * Comment: layout of tree is the lexicographically greatest
 * distance sequence L(T, z) = [l1, l2, ..., ln], where
 * li is a distance from the i-th vertex to root 'z' */
template <unsigned int labelsCount>
class tree_layout
{
protected:
  unsigned int labels[labelsCount];   // Array of vertices labels (distance to root)
public:
  /* Default class constructor */
  tree_layout( void )
  {
    /* Fill labels like in lined-tree *-*-*-...-*-* (this is a start-tree in algorithm) */
    for (unsigned int i = 0; i <= labelsCount / 2; i++)
      labels[i] = i;
    for (unsigned int i = labelsCount / 2 + 1; i < labelsCount; i++)
      labels[i] = i - labelsCount / 2;
  }

  /* Copying class constructor */
  tree_layout( tree_layout &layout )
  {
    for (unsigned int i = 0; i < labelsCount; i++)
      labels[i] = layout.labels[i];
  }

  /* Allow to get and set 'index'-th label from layout function */
  unsigned int & operator[]( unsigned int index )
  {
    return labels[index % labelsCount];
  }

  /* Return size of labels array (count of vertices in tree) function */
  unsigned int size( void )
  {
    return labelsCount;
  }

  /* Search a maximum vertex label in 'labels' array function */
  unsigned int max( void )
  {
    unsigned int maxLabel = labels[1];

    for (unsigned int i = 2; i < labelsCount; i++)
      if (labels[i] > maxLabel)
        maxLabel = labels[i];
    return maxLabel;
  }

  /* Returns count of vertices in tree operator (allow to compare labels from trees with different vertices count) */
  operator unsigned int( void )
  {
    return labelsCount;
  }

  /* Assignment new layout operator */
  tree_layout & operator=( tree_layout &layout )
  {
    for (int i = 0; i < labelsCount; i++)
      labels[i] = layout.labels[i];
    return *this;
  }
};

/* Generator new layout helpful class */
template <unsigned int labelsCount>
class tree_generator
{
public:
  /* Construct new layout from some layout function.
   * (input) p - index of label for start */
  static tree_layout<labelsCount> successor( tree_layout<labelsCount> &layout, unsigned int p = 0 )
  {
    unsigned int q;
    tree_layout<labelsCount> newLayout = layout;

    if (p == 0)
    {
      /* Search maximum index of label, which isn't equal with 1 */
      for (p = labelsCount - 1; layout[p] == 1; p--)
        ;
      if (p == 0)
        return newLayout;
    }

    /* Search a parent of vertex with p-th label (search maximum index of label, which is equal with label[p] - 1 */
    for (q = p - 1; layout[q] != layout[p] - 1; q--)
      ;

    /* Copy a first part of 'layout' to successor */
    newLayout[0] = 0;
    newLayout[1] = 1;
    for (unsigned int i = 2; i < p; i++)
      newLayout[i] = layout[i];
    /* Copy a part of successor to the end of successor */
    for (unsigned int i = p; i < labelsCount; i++)
      newLayout[i] = newLayout[i - p + q];
    return newLayout;
  }

  static tree_layout<labelsCount> buildLayout( tree_layout<labelsCount> &layout )
  {
    tree_layout<labelsCount> newLayout;
    unsigned int m;

    newLayout = successor(layout);

    for (m = 2; m < labelsCount; m++)
      if (newLayout[m] == 1)
        break;
    tree_layout<labelsCount> l1;
    tree_layout<labelsCount> l2;

    for (unsigned int i = 0; i < m - 1; i++)
      l1[i] = newLayout[i + 1] - 1;
    for (unsigned int i = m - 1; i < labelsCount; i++)
      l1[i] = 0;

    l2[0] = 0;
    for (unsigned int i = 1; i < labelsCount - m + 1; i++)
      l2[i] = newLayout[i + m - 1];
    for (unsigned int i = labelsCount - m + 1; i < labelsCount; i++)
      l2[i] = 0;

    if (m != labelsCount && l2.max() >= l1.max())
    {
      if (l2.max() > l1.max())
        return newLayout;
      else if ((m - 1) <= (labelsCount - m + 1))   // case with (l2.max == l1.max)
      {
        if ((m - 1) < (labelsCount - m + 1))
          return newLayout;
        else if (l1 <= l2)
          return newLayout;
      }
    }
    newLayout = successor(newLayout, m - 1);

    if (l1[m - 2] > 1)
    {
      unsigned int height = 0, max = newLayout[1];
      for (unsigned int i = 2; i < labelsCount; i++)
        if (newLayout[i] <= max)
          break;
        else
        {
          max = newLayout[i];
          height++;
        }
      for (unsigned int i = labelsCount - 1; i >= labelsCount - height - 1; i--)
        newLayout[i] = i - labelsCount + 2 + height;
    }
    return newLayout;
  }
};

/* Compare two layouts with equal vertices count operator (compare lexicographically) */
template <unsigned int labelsCount>
bool operator<=( tree_layout<labelsCount> &layout1, tree_layout<labelsCount> &layout2 )
{
  for (unsigned int i = 2; i < labelsCount; i++)
    if (layout1[i] > layout2[i])
      return false;
  return true;
}

/* Check non-equal operator */
template <unsigned int labelsCount>
bool operator!=( tree_layout<labelsCount> &layout1, tree_layout<labelsCount> &layout2 )
{
  for (unsigned int i = 2; i < labelsCount; i++)
    if (layout1[i] != layout2[i])
      return true;
  return false;
}
