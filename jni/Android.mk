# Copyright (C) 2009 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)

TYPE_PRODUCT := TEST
ifeq ($(strip $(TYPE_PRODUCT)), SHARED_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := starcor-needle-lib

# LOCAL_C_INCLUDES := $(LOCAL_PATH)/include
# LOCAL_C_INCLUDES += $(shell ls -FR $(LOCAL_C_INCLUDES) | grep $(LOCAL_PATH)/$ | sed "s/:/ /g" )

LOCAL_SRC_FILES := DataNetParse/http-hdr.cpp \
	DataNetParse/SoftwareProbeDataPaser.cpp \
	DataNetFilter/SoftwareProbeFilter.cpp \
	DataNetPackage/NetPackage.cpp \
	DataProvider/DataProvider.cpp \
	DataProvider/DataProviderFactory.cpp \
	DataSysInfoColloct/SysInfoDataColloct.cpp \
	Native/native_jni.cpp \
	Utils/DataRegex.cpp \
	Utils/UtilsDataMsgQue.cpp

LOCAL_CXXFLAGS += --std=c++11 -O2
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_LDFLAGS += -lminidpi
LOCAL_LDFLAGS += -lpcre
LOCAL_LDFLAGS += -lyysdk
LOCAL_LDFLAGS += -Llibs

LOCAL_LDLIBS += -llog
LOCAL_LDLIBS += -pthread
LOCAL_LDLIBS += -lstdc++

include $(BUILD_SHARED_LIBRARY)

else

include $(CLEAR_VARS)
LOCAL_MODULE    := softwareProbe.elf

LOCAL_SRC_FILES := \
	DataSysInfoColloct/SysInfoDataColloct.cpp

LOCAL_CXXFLAGS += --std=c++11 -O2
LOCAL_C_INCLUDES := $(LOCAL_PATH)/include

LOCAL_LDFLAGS += libminidpi.a
LOCAL_LDFLAGS += libpcre.a
LOCAL_LDFLAGS += libyysdk.a

LOCAL_LDLIBS += -llog
LOCAL_LDLIBS += -pthread
LOCAL_LDLIBS += -lstdc++

include $(BUILD_EXECUTABLE)

endif


