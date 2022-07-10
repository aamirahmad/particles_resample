cmake_minimum_required(VERSION 2.8)
project( particles_resample )

find_package(Boost REQUIRED COMPONENTS
    iostreams system filesystem
)
add_library(gnuplot_iostream INTERFACE)
target_include_directories(gnuplot_iostream INTERFACE
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/>
    $<INSTALL_INTERFACE:>)
target_link_libraries(gnuplot_iostream INTERFACE
    Boost::iostreams
    Boost::system
    Boost::filesystem
)


# find_package( OpenCV REQUIRED )
add_executable( particles_resample main.cpp )
# target_link_libraries( particles_resample ${OpenCV_LIBS} ) 
target_compile_features(particles_resample PRIVATE cxx_std_17)
target_link_libraries( particles_resample PRIVATE
      gnuplot_iostream
      boost_iostreams
      boost_system
      boost_filesystem) 


add_executable( particles_resample_lvs main_LVS.cpp )
# target_link_libraries( particles_resample ${OpenCV_LIBS} ) 
target_compile_features(particles_resample_lvs PRIVATE cxx_std_17)
target_link_libraries( particles_resample_lvs PRIVATE
      gnuplot_iostream
      boost_iostreams
      boost_system
      boost_filesystem) 
