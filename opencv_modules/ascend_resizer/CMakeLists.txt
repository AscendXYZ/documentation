set(the_description "Ascend OpenCV Image Resizer")

ocv_define_module(ascend_resizer opencv_imgproc opencv_highgui)


set_target_properties(${PROJECT_NAME} PROPERTIES VS_DOTNET_REFERENCES "System;System.Core")
set_target_properties(${PROJECT_NAME} PROPERTIES COMPILE_FLAGS "/clr /EHa")
set_target_properties(${PROJECT_NAME} PROPERTIES DEBUG_POSTFIX "d")

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /AI\"C:\\dev\\ascendprojects\\Ascend Azure Pipeline\\Ascend.Algorithms\\Ascend.Algorithms.Interface\\bin\\x64\\Release\" ")

if(CMAKE_CXX_FLAGS_DEBUG MATCHES "/RTC1")
   string(REPLACE "/RTC1" " " CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG}")
endif()

if(CMAKE_CXX_FLAGS MATCHES "/EHsc")
   string(REPLACE "/EHsc" "" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
endif()




message(STATUS ${the_module})