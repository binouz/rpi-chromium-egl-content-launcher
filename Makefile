# Copyright 2018 Aubin REBILLAT
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http:://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

SOURCES   = application.cc display_delegate.cc main_delegate.cc
SOURCES  += browser_delegate.cc dbus_interface.cc main.cc
OBJS      = $(SOURCES:.cc=.o)
C_FLAGS   = $(CFLAGS) -std=c++11 -g -ggdb -Wall -Werror -Wno-error=unused-but-set-variable
C_FLAGS  += $(shell pkg-config --cflags egl glesv2 dbus-c++-1)
LD_FLAGS  = $(LDFLAGS) -legl_content_lib -lpthread
LD_FLAGS += $(shell pkg-config --libs egl glesv2 dbus-c++-1)
TARGET    = rpi-launcher

all: $(TARGET)

dbus_bindings:
	dbusxx-xml2cpp rpi-launcher.xml --adaptor=dbus_adaptor.h

$(TARGET): dbus_bindings $(OBJS)
	$(CXX) $(OBJS) $(LD_FLAGS) -o $(TARGET)

%.o : %.cc
	$(CXX) $(C_FLAGS) -c $< -o $@

clean:
	rm -rf *.o $(TARGET)
