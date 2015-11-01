#pragma message("Compiling precompiled headers...")

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <cmath>
#include <functional>

#include <GL/gl3w.h>
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "core/Types.h"
#include "core/Assert.h"
#include "core/Log.h"
#include "core/HashTools.h"
#include "core/StringHash.h"

#define MATH_PI 3.14159265359f
