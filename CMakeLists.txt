cmake_minimum_required(VERSION 3.16)
project(NewsAggregator VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find Qt6 components
find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network Sql Xml Test)

# Enable Qt MOC, UIC, RCC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/src)

# Source files
set(SOURCES
    src/main.cpp
    src/AppController.cpp
    src/DataStore.cpp
    src/ui/LandingPageWidget.cpp
    src/ui/EventBuilderWidget.cpp
    src/ui/MonitorWidget.cpp
    src/network/RSSFetcher.cpp
    src/network/EmbeddingClient.cpp
    src/engine/RelevanceEngine.cpp
    src/worker/MonitorWorker.cpp
)

set(HEADERS
    src/AppController.h
    src/DataStore.h
    src/models/Group.h
    src/models/Event.h
    src/models/Headline.h
    src/models/HeadlineMatch.h
    src/ui/LandingPageWidget.h
    src/ui/EventBuilderWidget.h
    src/ui/MonitorWidget.h
    src/network/RSSFetcher.h
    src/network/EmbeddingClient.h
    src/engine/RelevanceEngine.h
    src/worker/MonitorWorker.h
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Link Qt6 libraries
target_link_libraries(${PROJECT_NAME}
    Qt6::Core
    Qt6::Widgets
    Qt6::Network
    Qt6::Sql
    Qt6::Xml
)

# Enable testing
enable_testing()

# Test executable for RelevanceEngine
add_executable(test_relevance_engine
    src/tests/test_relevance_engine.cpp
    src/engine/RelevanceEngine.cpp
)
target_link_libraries(test_relevance_engine
    Qt6::Core
    Qt6::Test
)
add_test(NAME RelevanceEngineTest COMMAND test_relevance_engine)




