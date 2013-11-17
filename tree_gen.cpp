/* Sergeev Artemiy, 33601/2 (3057/2) */

#include "tree_gen.h"


/* Default class constructor */
tree_layout::tree_layout( unsigned int verticesCount ) : labelsCount(verticesCount), labels(NULL)
{
  if (labelsCount > 0)
  {
    labels = new unsigned int[labelsCount];
    if (labels == NULL)
      return;
    /* Fill labels like in lined-tree *-*-*-...-*-* (this is a start-tree in algorithm) */
    for (unsigned int i = 0; i <= labelsCount / 2; i++)
      labels[i] = i;
    for (unsigned int i = labelsCount / 2 + 1; i < labelsCount; i++)
      labels[i] = i - labelsCount / 2;
  }
}

/* Copying constructor */
tree_layout::tree_layout( const tree_layout &layout ) : labelsCount(layout.labelsCount)
{
  labels = new unsigned int[labelsCount];
  if (labels == NULL)
    return;
  /* Fill labels like in lined-tree *-*-*-...-*-* (this is a start-tree in algorithm) */
  for (unsigned int i = 0; i < labelsCount; i++)
    labels[i] = layout.labels[i];
}

/* Search a maximum vertex label in 'labels' array function */
unsigned int tree_layout::max( void ) const
{
  if (labelsCount > 1)
  {
    unsigned int maxLabel = labels[1];

    for (unsigned int i = 2; i < labelsCount; i++)
      if (labels[i] > maxLabel)
        maxLabel = labels[i];
    return maxLabel;
  }
  else
    return 1;
}

/* Assignment new layout operator */
tree_layout & tree_layout::operator=( const tree_layout &layout )
{
  if (layout.size() == labelsCount)
    for (unsigned int i = 0; i < labelsCount; i++)
      labels[i] = layout.labels[i];
  return *this;
}

/* Check tree for n-path rooted case function */
bool tree_layout::isSimple( void ) const
{
  for (unsigned int i = 1; i < labelsCount; i++)
    if (labels[i] != 1)
      return false;
  return true;
}

/* Calculate height of left subtree function */
unsigned int tree_layout::leftHeight( void ) const
{
  unsigned int height = 0, max = labels[1];

  for (unsigned int i = 2; i < labelsCount; i++)
  {
    if (labels[i] <= max)
      break;
    else
    {
      max = labels[i];
      height++;
    }
  }
  return height;
}

/* Compare two layouts with equal vertices count operator (compare lexicographically) */
bool operator<=( tree_layout &layout1, tree_layout &layout2 )
{
  if (layout1.size() > layout2.size())
    return false;
  else if (layout1.size() < layout2.size())
    return true;
  else
    for (unsigned int i = 0; i < layout1.size(); i++)
    {
      if (layout1[i] < layout2[i])
        return true;
      else if (layout1[i] > layout2[i])
        return false;
    }
  return true;
}

/* Check non-equal operator */
bool operator!=( tree_layout &layout1, tree_layout &layout2 )
{
  if (layout1.size() != layout2.size())
    return true;
  else
  {
    for (unsigned int i = 2; i < layout1.size(); i++)
      if (layout1[i] != layout2[i])
        return true;
  }
  return false;
}

/* Construct new layout from some layout function.
 * (input) p - index of label for start */
tree_layout tree_generator::successor( tree_layout &layout, unsigned int p )
{
  unsigned int q;
  tree_layout newLayout(layout);

  if (p == 0)
  {
    /* Search maximum index of label, which isn't equal with 1 */
    for (p = layout.size() - 1; layout[p] == 1; p--)
      ;
    if (p == 0)
      return newLayout;
  }

  /* Search a parent of vertex with p-th label (search maximum index of label, which is equal with label[p] - 1 */
  for (q = p - 1; layout[q] != layout[p] - 1; q--)
    ;

  /* Copy a part of successor to the end of successor */
  for (unsigned int i = p; i < layout.size(); i++)
    newLayout[i] = newLayout[i - p + q];
  return newLayout;
}

tree_layout tree_generator::buildLayout( tree_layout &layout )
{
  tree_layout newLayout(successor(layout));
  unsigned int m;

  for (m = 2; m < newLayout.size(); m++)
    if (newLayout[m] == 1)
      break;
  if (m <= 1)
    return newLayout;
  tree_layout l1(m - 1);
  tree_layout l2(newLayout.size() - m + 1);

  for (unsigned int i = 0; i < l1.size(); i++)
    l1[i] = newLayout[i + 1] - 1;

  l2[0] = 0;
  for (unsigned int i = 1; i < l2.size(); i++)
    l2[i] = newLayout[i + m - 1];

  if (m != newLayout.size())
  {
    if (l2.max() > l1.max())
      return newLayout;
    else if (l2.max() == l1.max())
    {
      if (l1 <= l2)
        return newLayout;
    }
  }

  newLayout = successor(newLayout, m - 1);

  if (l1[m - 2] > 1)
  {
    unsigned int height = newLayout.leftHeight();
    for (unsigned int i = newLayout.size() - 1; i >= newLayout.size() - height - 1; i--)
      newLayout[i] = i - newLayout.size() + 2 + height;
  }
  return newLayout;
}
