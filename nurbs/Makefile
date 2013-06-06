PROGRAM = libnurbs.a

INCLUDES = \
	-I. \
	-Iinclude/ \
	-I/usr/include

LIBS = \

SRC_FILES = \
	src/barray2d_char.cpp \
	src/barray2d_complex.cpp \
	src/barray2d_coordinate.cpp \
	src/barray2d_double.cpp \
	src/barray2d_float.cpp \
	src/barray2d_hpoint.cpp \
	src/barray2d_int.cpp \
	src/barray2d_point.cpp \
	src/barray2d_uchar.cpp \
	src/barray_char.cpp \
	src/barray_complex.cpp \
	src/barray_coordinate.cpp \
	src/barray_double.cpp \
	src/barray_float.cpp \
	src/barray_hpoint.cpp \
	src/barray_int.cpp \
	src/barray_point.cpp \
	src/barray_uchar.cpp \
	src/barray_void.cpp \
	src/chebexp_.cpp \
	src/color.cpp \
	src/coordinate.cpp \
	src/cvector.cpp \
	src/d_curve.cpp \
	src/d_nurbs.cpp \
	src/d_nurbs_sp.cpp \
	src/d_nurbsArray.cpp \
	src/d_nurbsS.cpp \
	src/d_nurbsS_sp.cpp \
	src/d_nurbsSub.cpp \
	src/d_surface.cpp \
	src/d_tri_spline.cpp \
	src/error.cpp \
	src/fft_.cpp \
	src/filter_.cpp \
	src/hpoint_nd.cpp \
	src/image_.cpp \
	src/intccq_.cpp \
	src/list.cpp \
	src/matrix_char.cpp \
	src/matrix_complex.cpp \
	src/matrix_double.cpp \
	src/matrix_float.cpp \
	src/matrix_hpoint.cpp \
	src/matrix_int.cpp \
	src/matrix_point.cpp \
	src/matrix_uchar.cpp \
	src/matrixMat_.cpp \
	src/matrixRT.cpp \
	src/point_nd.cpp \
	src/rec_filter_.cpp \
	src/statistic_.cpp \
	src/vector_char.cpp \
	src/vector_complex.cpp \
	src/vector_double.cpp \
	src/vector_float.cpp \
	src/vector_hpoint.cpp \
	src/vector_int.cpp \
	src/vector_point.cpp \
	src/vector_uchar.cpp


DEFINES = -D __USE_GNU -D _GNU_SOURCE \

OBJS1 = $(SRC_FILES)
OBJS2 = $(subst .cpp,.o,$(OBJS1))
OBJS = $(subst .c,.o,$(OBJS2))

CC = g++

CFLAGS = -g -O3 $(INCLUDES)

#####################################################################################################

all: $(PROGRAM)

%.o : %.cpp
	@echo $<
	@$(CC) $(CFLAGS) $(DEFINES) -fpermissive -Wno-non-template-friend -c $< -o $@

$(PROGRAM): $(OBJS)
#	@libtool --mode=link $(CC) $(CFLAGS) $(OBJS) -o $@
	ar cru libnurbs.a $(OBJS)
	ranlib libnurbs.a
	@echo ==============================================
	@echo ================= SUCCESS ====================

clean: #depend
	rm -f $(OBJS)
	rm -f $(PROGRAM)

#depend:
#	makedepend $(CFLAGS) $(DEFINES) $(SRC_CORE) $(SRC_PLUGINS) $(SRC_ZBSLIB)
