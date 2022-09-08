include config.mk

find-by-extension = $(shell find $(strip ${1}) -type f -name '*.$(strip ${2})')

SRC_DIR = src
SRC_DIR_STRUCT = $(shell find ${SRC_DIR} -type d)
SRC = $(call find-by-extension, ${SRC_DIR}, c)
HDR = $(call find-by-extension, ${SRC_DIR}, h)
SHARED_HDR = ${SRC_DIR}/${NAME}.h

BUILD_DIR = build
OBJ_DIR = ${BUILD_DIR}/obj
OBJ_DIR_STRUCT = ${SRC_DIR_STRUCT:${SRC_DIR}%=${OBJ_DIR}%/}
OBJ = ${SRC:${SRC_DIR}/%.c=${OBJ_DIR}/%.o}
SHARED_BUILD_HDR = ${SHARED_HDR:${SRC_DIR}%=${BUILD_DIR}%}

.PHONY: all
all: ${OBJ_DIR_STRUCT} ${BUILD_DIR}/${SHARED} ${SHARED_BUILD_HDR}

${OBJ_DIR_STRUCT}: ${SRC_DIR_STRUCT}
	@mkdir -p $@

${BUILD_DIR}/${SHARED}: ${OBJ}
	${CC} $^ ${LDFLAGS} -shared -o $@

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c ${HDR}
	${CC} ${CFLAGS} -c $< -o $@

${SHARED_BUILD_HDR}: ${SHARED_HDR}
	cp $< $@

.PHONY: dev
dev: CFLAGS := $(filter-out -DNDEBUG,${CFLAGS})
dev: CFLAGS += -pedantic -Wall -Werror -g
dev: options all

options-echo = @echo -e "$(strip ${1})\t= $(strip ${2})"

.PHONY: options
options:
	@echo "----COMPILE FLAGS----"
	$(call options-echo, VERSION, ${VERSION})
	$(call options-echo, CFLAGS , ${CFLAGS})
	$(call options-echo, LDFLAGS, ${LDFLAGS})
	$(call options-echo, CC     , ${CC})
	@echo "-----DIRECTORIES-----"
	$(call options-echo, BUILD , ${BUILD_DIR})
	$(call options-echo, OBJ   , ${OBJ_DIR})
	@echo "--------FILES--------"
	$(call options-echo, SRC   , ${SRC})
	$(call options-echo, HDR   , ${HDR})
	$(call options-echo, SHARED, ${BUILD_DIR}/${SHARED})
	$(call options-echo, HEADER, ${SHARED_BUILD_HDR})
	@echo "---------------------"

.PHONY: options
clean:
	@rm -rf ${BUILD_DIR}
	@echo "Cleaned!"
