set(AVT_SOURCES main.cpp
                AVToys.ui
                AVToys.qrc
                AVToys.h
                AVToys.cpp
                HCSDK.ui
                HCSDKWidget.h
                HCSDKWidget.cpp
                DHSDK.ui
                DHSDKWidget.h
                DHSDKWidget.cpp)

add_executable(AVToys WIN32 ${AVT_SOURCES})
target_link_libraries(AVToys Qt5::Widgets HCSDK DHSDK)
target_link_options(AVToys PRIVATE "/SUBSYSTEM:WINDOWS")
                