
CAT_HOME = ../../acTypes/ac_types-stable/include
INCLUDES = -I"$(CAT_HOME)" -I"../cmn/"

DEFINES  = 

CXX      = g++
CXXFLAGS = -g -O0 -fpermissive $(DEFINES) $(INCLUDES)

#VPATH   = ../../src/:../cmn/
VPATH    = ../cmn/

TARGET   = tb
OBJECTS  = vwScaler.o vwScalerTB.o


DEPENDS  = stdIncludes.h acIncludes.h vwScalerTypes.h vwScaler.h

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJECTS)
    
$(OBJECTS): $(DEPENDS)


#phony target to remove all objects and executables
.PHONE: clean
clean:
	rm -f *.o *.exe
  
  
