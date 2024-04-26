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
    Scene/TitleScene.cpp
    Scene/PlayScene.h
    Scene/PlayScene.cpp
    Scene/ResultScene.h
    Scene/ResultScene.cpp
)

set(Constant
    Constant/CameraConstant.h
    Constant/GameObjectName.h
    Constant/ObjectTag.h
    Constant/SceneName.h
)

set(Character
    Character/Camera/MainCamera.h
    Character/Camera/MainCamera.cpp
    Character/Player/Player.h
    Character/Player/Player.cpp
    Character/Enemy/Skeleton/Skeleton.h
    Character/Enemy/Skeleton/Skeleton.cpp
    Character/DeadEffect/EnemyDeadEffect.h
    Character/DeadEffect/EnemyDeadEffect.cpp
)

set(Component
    Component/Common/AttackColliderController.h
    Component/Common/AttackColliderController.cpp
    Component/Common/Damageable.h
    Component/Common/Damageable.cpp
    Component/Common/ElapsedTimer.h
    Component/Common/ElapsedTimer.cpp
    Component/Common/Rotator.h
    Component/Common/Rotator.cpp
    Component/Camera/CameraController.h
    Component/Camera/CameraController.cpp
    Component/Camera/CameraRotator.h
    Component/Camera/CameraRotator.cpp
    Component/Camera/CameraObstacleDetection.h
    Component/Camera/CameraObstacleDetection.cpp
    Component/Effect/DelayedEffectPlayer.h
    Component/Effect/DelayedEffectPlayer.cpp
    Component/Enemy/CharacterSearcher.h
    Component/Enemy/CharacterSearcher.cpp
    Component/Enemy/State/EnemyAttackState.h
    Component/Enemy/State/EnemyAttackState.cpp
    Component/Enemy/State/EnemyDamageState.h
    Component/Enemy/State/EnemyDamageState.cpp
    Component/Enemy/State/EnemyDeadState.h
    Component/Enemy/State/EnemyDeadState.cpp
    Component/Enemy/State/EnemyChaseState.h
    Component/Enemy/State/EnemyChaseState.cpp
    Component/Enemy/State/EnemySearchState.h
    Component/Enemy/State/EnemySearchState.cpp
    Component/Enemy/State/EnemySelectorState.h
    Component/Enemy/State/EnemySelectorState.cpp
    Component/Player/PlayerMoveState.h
    Component/Player/PlayerMoveState.cpp
    Component/Player/PlayerAttackState.h
    Component/Player/PlayerAttackState.cpp
    Component/Player/PlayerDamageState.h
    Component/Player/PlayerDamageState.cpp
    Component/Player/PlayerDeadState.h
    Component/Player/PlayerDeadState.cpp
    Component/Player/PlayerRollingState.h
    Component/Player/PlayerRollingState.cpp
    Component/StateMachine/State.h
    Component/StateMachine/State.cpp
    Component/StateMachine/AnimationInfo.h
    Component/StateMachine/StateBehavior.h
    Component/StateMachine/StateBehavior.cpp
)

set(Enum
    Enum/State/PlayerState.h
    Enum/State/EnemyState.h
    Enum/AnimationID.h
    Enum/AudioID.h
    Enum/AudioGroupID.h
    Enum/CollisionLayer.h
    Enum/EffectID.h
    Enum/MeshID.h
    Enum/TextureID.h
)

set(Input
    Input/Input.h
    Input/Input.cpp
)

set(Utility
    Utility/AssetLoader.h
    Utility/AssetLoader.cpp
    Utility/CameraUtility.h
    Utility/CameraUtility.cpp
    Utility/Enum.h
    Utility/Fuzzy.h
    Utility/Fuzzy.cpp
    Utility/ReceptionTimer.h
    Utility/ReceptionTimer.cpp
    Utility/RigidbodyUility.h
    Utility/RigidbodyUility.cpp
)

# ソース一覧
list(APPEND MODULES 
    ${App} 
    ${Scene}
    ${Constant}
    ${Character}
    ${Component} 
    ${Enum} 
    ${Context} 
    ${Input}
    ${Utility}
)

MakeFilter(${MODULES})

# メインの実行可能ファイル
add_executable(${PROJECT_NAME} WIN32 main.cpp ${MODULES} $<$<CXX_COMPILER_ID:MSVC>:utf8api.manifest>)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

# ライブラリの場所
set(GEARS_LIBRARY_DIR ${PROJECT_SOURCE_DIR}/Library/GearsLibrary)
set(DEBUG_LIB "${GEARS_LIBRARY_DIR}/Lib/Debug")
set(RELEASE_LIB "${GEARS_LIBRARY_DIR}/Lib/Release")

# ヘッダーファイルのインクルードディレクトリの設定
file(GLOB INTERNAL_DIRS ${GEARS_LIBRARY_DIR}/Include/*/)
target_include_directories(${PROJECT_NAME} PUBLIC ${GEARS_LIBRARY_DIR}/Include)
target_include_directories(${PROJECT_NAME} PUBLIC ${GEARS_LIBRARY_DIR}/External/DirectXTex)
target_include_directories(${PROJECT_NAME} PUBLIC ${GEARS_LIBRARY_DIR}/External/PhysX)
target_include_directories(${PROJECT_NAME} PUBLIC ${INTERNAL_DIRS})
target_include_directories(${PROJECT_NAME} PRIVATE ${MODULES})
target_link_libraries(${PROJECT_NAME} debug ${DEBUG_LIB}/*.lib)
target_link_libraries(${PROJECT_NAME} optimized ${RELEASE_LIB}/*.lib)

#DLLのコピー
set(DLL_FILES "${GEARS_LIBRARY_DIR}/Dll/*.dll")
#set(DLL_DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/bin)
