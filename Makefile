
WISELIB_PATH=../..


WISELIB_STABLE=$(WISELIB_PATH)/wiselib.stable
WISELIB_TESTING=$(WISELIB_PATH)/wiselib.testing
export SOURCES=example_app.cpp
export TARGET=example_app


CXX=g++
LD=ld
CXXFLAGS+=-I$(WISELIB_STABLE) -I$(WISELIB_TESTING) -I$(WISELIB_TESTING)/external_interface/pc -I$(WISELIB_TESTIG)/algorithms/block_memory/
LDFLAGS+=-lpthread -lrt

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LDFLAGS)

clean:
	rm -rf example_app
