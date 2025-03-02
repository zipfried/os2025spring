#include <stdio.h>
#include <unistd.h>

typedef struct mcb_t {
  int size; // 动态内存块的大小、
  unsigned char free; // 该内存块是否被使用，为true则代表可以分配给用户使用
  struct mcb_t *prev; // 前一个控制块的指针
} mcb_t;

mcb_t *g_top = NULL;

void *my_malloc(int size) {
  // 注意第一步需要从后往前找用没有合适的内存可以分配，没有开辟新的内存,真正的malloc是从前往后找
  mcb_t *mcb = g_top;
  while (mcb) {
    if (mcb->size >= size && mcb->free) {
      break;
    }
    mcb = mcb->prev;
  }
  if (mcb == NULL) // 之前的空间当中没有合适的控制块
  {
    mcb = (mcb_t *)sbrk(size + sizeof(mcb_t));
    if (mcb == (void *)-1) {
      return NULL;
    }
    mcb->size = size;
    mcb->prev = g_top;
    g_top = mcb;
    printf("Allocate a new block: %p\n", g_top);
  } else {
    printf("Use existing block: %p\n", mcb);
  }

  mcb->free = 0;            // 已经分配给用户了
  return (void *)(mcb + 1); // 返回可用的地址
}

void my_free(void *ptr) {
  if (ptr == NULL)
    return;
  mcb_t *mcb = (mcb_t *)ptr - 1;

  // TODO: 检查mcb是否是有效的节点
  mcb->free = 1;
}

int main() {
  char *ptr = my_malloc(100);
  fgets(ptr, 100, stdin);
  printf("Your input is : %s\n", ptr);
  my_free(ptr);
  return 0;
}
