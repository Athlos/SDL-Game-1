# Install script for directory: F:/Desktop/Desktop/Box2D-master/Box2D/Box2D

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Box2D")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D" TYPE FILE FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Box2D.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Collision" TYPE FILE FILES
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Collision/b2BroadPhase.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Collision/b2Collision.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Collision/b2Distance.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Collision/b2DynamicTree.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Collision/b2TimeOfImpact.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Collision/Shapes" TYPE FILE FILES
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Collision/Shapes/b2CircleShape.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Collision/Shapes/b2EdgeShape.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Collision/Shapes/b2ChainShape.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Collision/Shapes/b2PolygonShape.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Collision/Shapes/b2Shape.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Common" TYPE FILE FILES
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Common/b2BlockAllocator.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Common/b2Draw.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Common/b2GrowableStack.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Common/b2Math.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Common/b2Settings.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Common/b2StackAllocator.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Common/b2Timer.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Dynamics" TYPE FILE FILES
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/b2Body.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/b2ContactManager.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/b2Fixture.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/b2Island.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/b2TimeStep.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/b2World.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/b2WorldCallbacks.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Dynamics/Contacts" TYPE FILE FILES
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2CircleContact.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2Contact.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2ContactSolver.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2PolygonAndCircleContact.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndCircleContact.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2EdgeAndPolygonContact.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2ChainAndCircleContact.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2ChainAndPolygonContact.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Contacts/b2PolygonContact.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Dynamics/Joints" TYPE FILE FILES
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Joints/b2DistanceJoint.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Joints/b2FrictionJoint.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Joints/b2GearJoint.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Joints/b2Joint.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Joints/b2MotorJoint.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Joints/b2MouseJoint.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Joints/b2PrismaticJoint.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Joints/b2PulleyJoint.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Joints/b2RevoluteJoint.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Joints/b2RopeJoint.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Joints/b2WeldJoint.h"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Dynamics/Joints/b2WheelJoint.h"
    )
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/Box2D/Rope" TYPE FILE FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Rope/b2Rope.h")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Debug/Box2D.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Release/Box2D.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/MinSizeRel/Box2D.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/RelWithDebInfo/Box2D.lib")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Debug/Box2D.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Release/Box2D.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/MinSizeRel/Box2D.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/RelWithDebInfo/Box2D.dll")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Debug/Box2D.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Release/Box2D.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/MinSizeRel/Box2D.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/RelWithDebInfo/Box2D.lib")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/Box2D/Box2D-targets.cmake")
    file(DIFFERENT EXPORT_FILE_CHANGED FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/Box2D/Box2D-targets.cmake"
         "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/CMakeFiles/Export/lib/Box2D/Box2D-targets.cmake")
    if(EXPORT_FILE_CHANGED)
      file(GLOB OLD_CONFIG_FILES "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/Box2D/Box2D-targets-*.cmake")
      if(OLD_CONFIG_FILES)
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/Box2D/Box2D-targets.cmake\" will be replaced.  Removing files [${OLD_CONFIG_FILES}].")
        file(REMOVE ${OLD_CONFIG_FILES})
      endif()
    endif()
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Box2D" TYPE FILE FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/CMakeFiles/Export/lib/Box2D/Box2D-targets.cmake")
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Box2D" TYPE FILE FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/CMakeFiles/Export/lib/Box2D/Box2D-targets-debug.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Box2D" TYPE FILE FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/CMakeFiles/Export/lib/Box2D/Box2D-targets-minsizerel.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Box2D" TYPE FILE FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/CMakeFiles/Export/lib/Box2D/Box2D-targets-relwithdebinfo.cmake")
  endif()
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Box2D" TYPE FILE FILES "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/CMakeFiles/Export/lib/Box2D/Box2D-targets-release.cmake")
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/Box2D" TYPE FILE FILES
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/Box2DConfig.cmake"
    "F:/Desktop/Desktop/Box2D-master/Box2D/Box2D/UseBox2D.cmake"
    )
endif()

