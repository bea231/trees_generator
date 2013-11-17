/* Sergeev Artemiy, 33601/2 (3057/2) */

#include <stdio.h>
#include <conio.h>
#include <vector>
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

/* Disable some 'idiots' (in my opinion) warnings about printf and scanf */
#pragma warning(disable:4996)

#define SIZE_X 20
#define SIZE_Y 10
#define MAX_TREE_STR 7

char treeTable[SIZE_X][SIZE_Y][MAX_TREE_STR] = {0};

/* Recursive function for print tree function */
unsigned int makeTreeTable( tree_layout &layout, unsigned int index, int &x, int y )
{
  unsigned int i = index + 1;
  unsigned int numOfChildrens = 0;
    
  if (index < layout.size())
  { 
    if (layout[index + 1] - 1 == layout[index])
      i = makeTreeTable(layout, index + 1, x, y + 1);
    
    sprintf(treeTable[x][y], "%i ", index);
    x++;
    while (layout[index] + 1 == layout[i])
      i = makeTreeTable(layout, i, x, y + 1);
  }    
  return i;
}

/* Simple print tree by layout function */
void printTree( tree_layout &layout )
{
  int i, j, x = 0;

  if (layout.leftHeight() + 1 > SIZE_Y || layout.size() - 1 > SIZE_X)
    printf("Tree is very big for print\n");

  /* Erase tree table for output */
  for (i = 0; i < SIZE_X; i++)
    for (j = 0; j < SIZE_Y; j++)
      sprintf(treeTable[i][j], " ");

  makeTreeTable(layout, 0, x, 0);

  /* Print tree table to screen */
  for (j = 0; j < SIZE_Y; j++)
  {
    for (i = 0; i < SIZE_X; i++)
      printf(treeTable[i][j]);
    printf("\n");
  }
}

/* Print one tree layout */
void printLayout( tree_layout &layout )
{
  printf("[0");
  for (unsigned int i = 1; i < layout.size(); i++)
    printf(" %u", layout[i]);
  printf("]\n");
}

/* Get free non-isomorphyc trees count function */
unsigned int getTreesCount( unsigned int vertexCount )
{
  unsigned int count = 1;
  tree_layout layout(vertexCount);

  while (!layout.isSimple())
  {
    count++;
    layout = tree_generator::buildLayout(layout);
  }
  return count;
}


unsigned int printLayouts( unsigned int vertexCount )
{
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
  return count;
}

unsigned int printTreesAdv( unsigned int vertexCount )
{
  unsigned int count = 1;
  tree_layout layout(vertexCount);

  while (!layout.isSimple())
  {
    printTree(layout);
    layout = tree_generator::buildLayout(layout);
  }  
  printTree(layout);
  
  return count;
}

void printTreesCount( unsigned int vertexNum )
{
  printf("%3u -> %u", 0, 0);
  for (unsigned int i = 1; i <= vertexNum; i++)
    printf("\n%3u -> %u", i, getTreesCount(i));
}

void printMenu( void )
{
  printf("\n0 - Exit\n"
         "1 - Print trees\n"
         "2 - Print trees count\n"
         "3 - Advanced print trees\n"
         "Your choise is: ");
}

int main( void )
{
  SetDbgMemHooks();
  bool run = true;
  unsigned int choice = 0;
  unsigned int vertexNum;
  
  while (run)
  {
    printMenu();
    scanf("%u", &choice);
    switch(choice)
    {
    case 0:
      run = 0;
      break;
    case 1:
      printf("\nPrint number of vertices: ");
      scanf("%u", &vertexNum);
      printLayouts(vertexNum);
      break;
    case 2:
      printf("\nPrint maximum vertices number: ");
      scanf("%u", &vertexNum);
      printTreesCount(vertexNum);
      break;
    case 3:
      printf("\nPrint number of vertices: ");
      scanf("%u", &vertexNum);
      printTreesAdv(vertexNum);
      break;
    }
  } 

  return 0;
}