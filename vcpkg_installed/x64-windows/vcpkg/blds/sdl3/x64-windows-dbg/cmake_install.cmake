# Install script for directory: D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/pkgs/sdl3_x64-windows/debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "OFF")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/pkgconfig" TYPE FILE FILES "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/x64-windows-dbg/sdl3.pc")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/x64-windows-dbg/SDL3.lib")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/x64-windows-dbg/SDL3.dll")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE FILE OPTIONAL FILES "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/x64-windows-dbg/SDL3.pdb")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/sdl3/SDL3headersTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/sdl3/SDL3headersTargets.cmake"
         "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/x64-windows-dbg/CMakeFiles/Export/4dd1f946b649bbfc73d93f0f0b7161ef/SDL3headersTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/sdl3/SDL3headersTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/sdl3/SDL3headersTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sdl3" TYPE FILE FILES "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/x64-windows-dbg/CMakeFiles/Export/4dd1f946b649bbfc73d93f0f0b7161ef/SDL3headersTargets.cmake")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/sdl3/SDL3sharedTargets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/sdl3/SDL3sharedTargets.cmake"
         "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/x64-windows-dbg/CMakeFiles/Export/4dd1f946b649bbfc73d93f0f0b7161ef/SDL3sharedTargets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/sdl3/SDL3sharedTargets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/share/sdl3/SDL3sharedTargets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sdl3" TYPE FILE FILES "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/x64-windows-dbg/CMakeFiles/Export/4dd1f946b649bbfc73d93f0f0b7161ef/SDL3sharedTargets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sdl3" TYPE FILE FILES "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/x64-windows-dbg/CMakeFiles/Export/4dd1f946b649bbfc73d93f0f0b7161ef/SDL3sharedTargets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/share/sdl3" TYPE FILE FILES
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/x64-windows-dbg/SDL3Config.cmake"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/x64-windows-dbg/SDL3ConfigVersion.cmake"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/SDL3" TYPE FILE FILES
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_assert.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_asyncio.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_atomic.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_audio.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_begin_code.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_bits.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_blendmode.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_camera.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_clipboard.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_close_code.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_copying.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_cpuinfo.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_dialog.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_egl.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_endian.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_error.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_events.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_filesystem.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_gamepad.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_gpu.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_guid.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_haptic.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_hidapi.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_hints.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_init.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_intrin.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_iostream.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_joystick.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_keyboard.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_keycode.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_loadso.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_locale.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_log.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_main.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_main_impl.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_messagebox.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_metal.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_misc.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_mouse.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_mutex.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_oldnames.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_opengl.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_opengl_glext.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_opengles.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_opengles2.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_opengles2_gl2.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_opengles2_gl2ext.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_opengles2_gl2platform.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_opengles2_khrplatform.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_pen.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_pixels.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_platform.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_platform_defines.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_power.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_process.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_properties.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_rect.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_render.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_scancode.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_sensor.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_stdinc.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_storage.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_surface.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_system.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_thread.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_time.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_timer.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_touch.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_tray.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_version.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_video.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/include/SDL3/SDL_vulkan.h"
    "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/x64-windows-dbg/include-revision/SDL3/SDL_revision.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/licenses/SDL3" TYPE FILE FILES "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/src/ease-3.2.4-d381bc6db0.clean/LICENSE.txt")
endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "D:/DesktopFile/Game Dev/SDL_Game/vcpkg_installed/x64-windows/vcpkg/blds/sdl3/x64-windows-dbg/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
