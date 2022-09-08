VERSION = 0.1 (in development)
NAME = onaga
SHARED = ${NAME}.so

LIBS = vulkan glfw

CFLAGS = -O2 -pipe -fPIC -DNDEBUG
LDFLAGS = ${LIBS:%=-l%}

CC = cc
