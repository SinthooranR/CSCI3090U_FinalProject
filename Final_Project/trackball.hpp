#define SCALE_FACTOR 0.1f
#define ROTATION_FACTOR 2.0f

float lastX = std::numeric_limits<float>::infinity();
float lastY = std::numeric_limits<float>::infinity();

// camera-related variables
glm::vec3 eyePosition;
float scaleFactor = 30.0f;
glm::quat rotation = glm::angleAxis(1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
float cameraDistance = 100.0f;

glm::vec3 getTrackballVector(int x, int y, int width, int height) {
   glm::vec3 P = glm::vec3(1.0 * x / width * 2 - 1.0,
   	                     1.0 * y / height * 2 - 1.0,
   	                     0);
   P.y = -P.y;
   float OP_squared = P.x * P.x + P.y * P.y;
   if (OP_squared <= 1 * 1) {
      P.z = sqrt(1 * 1 - OP_squared);  // Pythagoras
   } else {
      P = glm::normalize(P);  // nearest point
   }
   return P;
}

void drag(GLFWwindow* window, double xpos, double ypos) {
   int width, height;
   glfwGetFramebufferSize(window, &width, &height);

   int stateLeft = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
   int stateRight = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT);

   bool areScaling = stateRight == GLFW_PRESS;
   bool mouseDown = (stateLeft == GLFW_PRESS) || (stateRight == GLFW_PRESS);

   if (mouseDown) {
      int x = (int)xpos;
      int y = (int)ypos;
      if (!std::isinf(lastX) && !std::isinf(lastY)) {
         if (areScaling) {
            float dx = lastX - (float)x;
            float dy = lastY - (float)y;

            // scale in/out (right button drag)
            float distance = sqrt(dx * dx + dy * dy);
            float scaleChange = distance * SCALE_FACTOR;
            if ((dx + dy) > 0.0f) {
               scaleChange *= -1.0f;
            }
            scaleFactor += scaleChange;

            lastX = x;
            lastY = y;
         } else {
            // trackball rotation (left button drag)
            glm::vec3 a = getTrackballVector(lastX, lastY, width, height);
            glm::vec3 b = getTrackballVector(x, y, width, height);

            float rotateSpeed = 1.0f;
            float angle = ROTATION_FACTOR * -(float)acos(glm::dot(a, b) / glm::length(a) / glm::length(b));

            if (!std::isnan(angle)) {
            	glm::vec3 axis = glm::normalize(glm::cross(a, b));

            	if (std::isnan(axis.x) || std::isnan(axis.y) || std::isnan(axis.z)) {
                  return;
               }

         	   angle *= rotateSpeed;
               glm::quat quaternion = glm::angleAxis(-angle, axis);

               //glm::mat4 rotationMatrix = glm::mat4_cast(quaternion);
         		eyePosition = eyePosition * quaternion;

               lastX = (float)x;
               lastY = (float)y;
            }
         }
      } else {
         lastX = (float)x;
         lastY = (float)y;
      }
   }
}

void mouse(GLFWwindow* window, int button, int action, int mods) {
   if (action == GLFW_RELEASE) {
      lastX = std::numeric_limits<float>::infinity();
      lastY = std::numeric_limits<float>::infinity();
   }
}
