cmake_minimum_required(VERSION 3.5)

project(nmap_text_to_xml LANGUAGES C)

add_executable(nmap_text_to_xml main.c)

include_directories(/usr/include/libxml2)

link_directories(/usr/lib)

target_link_libraries(nmap_text_to_xml xml2)
