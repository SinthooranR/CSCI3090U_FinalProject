#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

class objectModel {
   public:
    objectModel(string filename);
    vector<glm::vec3> vertices;
    vector<glm::vec2> uvs;
    vector<glm::vec3> normals;
};

objectModel::objectModel(string filename) {
    vector<glm::vec3> temp_vertices;
    vector<glm::vec2> temp_uvs;
    vector<glm::vec3> temp_normals;

    vector<unsigned int> vertex_indices;
    vector<unsigned int> uv_indices;
    vector<unsigned int> normal_indices;

    ifstream obj_file(filename); 
    string line;

    // If the file can be read
    if (obj_file) {
        // Get the lines from the file
        while (getline(obj_file, line)) {
            // Get the line type
            string line_type;
            line_type = line.substr(0, line.find(" "));

            stringstream line_data(
                line.substr(line.find(" ") + 1, line.length()));
            if (line_type == "v" || line_type == "vn") {
                // Used to hold the point
                glm::vec3 vertex;
                string x, y, z;

                line_data >> x >> y >> z;  

                vertex.x = strtof(x.c_str(), 0);
                vertex.y = strtof(y.c_str(), 0);
                vertex.z = strtof(z.c_str(), 0);

                if (line_type == "v") {
                    temp_vertices.push_back(vertex);
                } else if (line_type == "vn") {
                    temp_normals.push_back(vertex);
                }
            } else if (line_type == "vt") {
                // Used to hold the point
                glm::vec2 uv;
                string x, y;

                line_data >> x >> y;

                uv.x = strtof(x.c_str(), 0);
                uv.y = strtof(y.c_str(), 0);

                temp_uvs.push_back(uv);
            } else if (line_type == "f") {
                // Iterate through the string getting the data
                unsigned int v1, v2, v3, u1, u2, u3, n1, n2, n3;

                sscanf(line.c_str(), "f %d/%d/%d %d/%d/%d %d/%d/%d", &v1, &u1,
                       &n1, &v2, &u2, &n2, &v3, &u3, &n3);

                vertex_indices.push_back(v1);
                vertex_indices.push_back(v2);
                vertex_indices.push_back(v3);

                uv_indices.push_back(u1);
                uv_indices.push_back(u2);
                uv_indices.push_back(u3);

                normal_indices.push_back(n1);
                normal_indices.push_back(n2);
                normal_indices.push_back(n3);
            }
        }
        obj_file.close();

        for (unsigned int i = 0; i < vertex_indices.size(); i++) {
            unsigned int vertex_index = vertex_indices[i];
            glm::vec3 vertex = temp_vertices[vertex_index - 1];
            vertices.push_back(vertex);
        }

        for (unsigned int i = 0; i < uv_indices.size(); i++) {
            unsigned int uv_index = uv_indices[i];
            glm::vec2 uv = temp_uvs[uv_index - 1];
            uvs.push_back(uv);
        }

        for (unsigned int i = 0; i < normal_indices.size(); i++) {
            unsigned int normal_index = normal_indices[i];
            glm::vec3 normal = temp_normals[normal_index - 1];
            normals.push_back(normal);
        }
    }
}