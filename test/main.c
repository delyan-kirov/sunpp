#include <dlfcn.h>
#include <stdio.h>
#include <unistd.h>

typedef void (*Pee)();

void peeCall() {
  void *libHandle = dlopen("./libtest.so", RTLD_LAZY);
  if (!libHandle) {
    fprintf(stderr, "Error loading library: %s\n", dlerror());
  }

  Pee pee = (Pee)dlsym(libHandle, "pee");
  if (!pee) {
    fprintf(stderr, "Error getting function address: %s\n", dlerror());
    dlclose(libHandle);
  }

  // Call the function
  pee();
  putc('\n', stdout);
  dlclose(libHandle);
}

int main() {

  // Call the function
  for (;;) {
    sleep(1);
    peeCall();
  }

  return 0;
}
