/* Sergeev Artemiy, 33601/2 (3057/2) */

#include <stdio.h>
#include "tree_gen.h"

/* Debug memory check support */
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#  include <crtdbg.h>
#  define SetDbgMemHooks()                                         \
  _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_CHECK_ALWAYS_DF | \
  _CRTDBG_ALLOC_MEM_DF | _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG))
#else
  #define SetDbgMemHooks() 0
#endif /* _DEBUG */

void printLayout( tree_layout &layout )
{
  printf("[0");
  for (unsigned int i = 1; i < layout.size(); i++)
    printf(" %u", layout[i]);
  printf("]\n");
}

int main( void )
{
  SetDbgMemHooks();

  const unsigned int vertexCount = 15;
  unsigned int count = 1;
  tree_layout layout(vertexCount);

  while (!layout.isSimple())
  {
    printf("%2i -> ", count++);
    printLayout(layout);
    layout = tree_generator::buildLayout(layout);
  }
  printf("%2i -> ", count);
  printLayout(layout);

  return 0;
}