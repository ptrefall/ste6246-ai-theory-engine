###
# This software is provided 'as-is', without any express or implied
# warranty.  In no event will the authors be held liable for any damages
# arising from the use of this software.
#
# Permission is granted to anyone to use this software for any purpose,
# including commercial applications, and to alter it and redistribute it
# freely, subject to the following restrictions:
# 
# 1. The origin of this software must not be misrepresented; you must not
#    claim that you wrote the original software. If you use this software
#    in a product, an acknowledgment in the product documentation would be
#    appreciated but is not required.
# 2. Altered source versions must be plainly marked as such, and must not be
#    misrepresented as being the original software.
# 3. This notice may not be removed or altered from any source distribution.
#
# Note: Some of the libraries GMEngine may link to may have additional
# requirements or restrictions.
#
###

cmake_minimum_required(VERSION 2.8)
 
project(Perceptron)

set(HDRS
  Loader.h
  StringHelper.h
  Random.h
  Perceptron.h
  BackPropagation.h
  Network.h
)

set(SRCS
  main.cpp
  Loader.cpp
  StringHelper.cpp
  Random.cpp
  Perceptron.cpp
  BackPropagation.cpp
  Network.cpp
)
 
add_executable(Perceptron ${HDRS} ${SRCS})
