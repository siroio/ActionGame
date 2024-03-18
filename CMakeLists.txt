cmake_minimum_required(VERSION 3.4)

# プロジェクト名とバージョンの設定
project(ActionGame VERSION 1.0.0 LANGUAGES CXX)

# C++標準を20に設定
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)
include(cmake/MakeFilter.cmake)

# UTF-8コンパイルオプションの追加
add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
if(MSVC)
    # UTF8に変更
    add_compile_options("$<$<CXX_COMPILER_ID:MSVC>:/utf-8>")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /MTd")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /MT")
endif()

# ソースの追加
set(App
    App/App.h
    App/App.cpp
)

set(Scene
    Scene/TitleScene.h
    Scene/PlayScene.h
    Scene/ResultScene.h
    Scene/TitleScene.cpp
    Scene/PlayScene.cpp
    Scene/ResultScene.cpp
)

set(Utility
    Utility/Enum.h
    Utility/AssetLoader.h
    Utility/AssetLoader.cpp
)
list(APPEND MODULES ${App} ${Scene} ${Utility})

MakeFilter(${MODULES})

# メインの実行可能ファイル
add_executable(${PROJECT_NAME} WIN32 main.cpp ${MODULES} $<$<CXX_COMPILER_ID:MSVC>:utf8api.manifest>)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# ライブラリの場所
set(GEARS_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/Library/GearsLibrary)
set(DEBUG_LIB "${GEARS_LIBRARY_DIR}/Lib/debug")
set(RELEASE_LIB "${GEARS_LIBRARY_DIR}/Lib/release")

# ヘッダーファイルのインクルードディレクトリの設定
file(GLOB INTERNAL_DIRS ${GEARS_LIBRARY_DIR}/Include/*/)
target_include_directories(${PROJECT_NAME} PUBLIC ${GEARS_LIBRARY_DIR}/Include)
target_include_directories(${PROJECT_NAME} PUBLIC ${INTERNAL_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${MODULES})
target_link_libraries(${PROJECT_NAME} debug ${DEBUG_LIB}/*.lib)
target_link_libraries(${PROJECT_NAME} optimized ${RELEASE_LIB}/*.lib)

#DLLのコピー
set(DLL_FILES "${GEARS_LIBRARY_DIR}/Dll/*.dll")
#set(DLL_DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
