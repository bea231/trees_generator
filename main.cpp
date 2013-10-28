/* Sergeev Artemiy, 33601/2 (3057/2) */

#include <stdio.h>
#include "tree_gen.h"

template <unsigned int labelsCount>
void printLayout( tree_layout<labelsCount> layout )
{
  printf("[0");
  for (unsigned int i = 1; i < labelsCount; i++)
    printf(" %u", layout[i]);
  printf("]\n");
}

int main( void )
{
  const unsigned int vertexCount = 11;
  unsigned int count = 1;
  tree_layout<vertexCount> layout, breakLayout;

  for (unsigned int i = 2; i < vertexCount; i++) 
    breakLayout[i] = 1;

  while (layout != breakLayout)
  {
    printf("%2i -> ", count++);
    printLayout(layout);
    layout = tree_generator<vertexCount>::buildLayout(layout);
  }
  printf("%2i -> ", count++);
  printLayout(layout);

  return 0;
}