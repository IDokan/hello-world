/*
 *  1. sinil.gang
 *  2. Shader Programming / 3
 *  3. CS230
 *  4. Spring 2019
 */

#include "Color4f.hpp"
#include "Shader.hpp"
#include <matrix3.hpp>
#include <GL/glew.h>
#include <cassert>
#include <iostream>

    Shader::Shader(const std::string& vertex_shader_source_code, const std::string& fragment_shader_source_code)
    {
        if (!LoadFromSource(vertex_shader_source_code, fragment_shader_source_code))
        {
            std::cerr << "Shader compilation failed!\n";
        }
    }

    bool Shader::LoadFromSource(const std::string& vertex_shader_source_code,
                                       const std::string& fragment_shader_source_code)
    {
        if (handleToShader != NULL)
        {
            Delete();
        }

        GLuint vertexShader;
        (vertexShader = glCreateShader(GL_VERTEX_SHADER));

        const GLchar* vertexShaderSource = vertex_shader_source_code.c_str();
        // Check
        (glShaderSource(vertexShader, 1, &vertexShaderSource, NULL));
        (glCompileShader(vertexShader));

        GLint isCompiled = 0;
        (glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled));

        if (isCompiled == GL_FALSE)
        {
            GLsizei logLength = 0;
            (glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &logLength));

            GLchar* errorLog = new GLchar[logLength+1];
            (glGetShaderInfoLog(vertexShader, logLength, &logLength, errorLog));

            std::cerr << errorLog << '\n';

            delete[] errorLog;
            (glDeleteShader(vertexShader));

            return false;
        }

        GLuint fragmentShader;
        (fragmentShader = glCreateShader(GL_FRAGMENT_SHADER));

        const GLchar* fragmentShaderSource = fragment_shader_source_code.c_str();
        (glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL));

        (glCompileShader(fragmentShader));

        (glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled));

        if (isCompiled == GL_FALSE)
        {
            GLsizei logLength = 0;
            (glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &logLength));

            GLchar* errorLog = new GLchar[logLength + 1];
            (glGetShaderInfoLog(fragmentShader, logLength, &logLength, errorLog));

            std::cerr << errorLog << '\n';
            
            delete[] errorLog;
            (glDeleteShader(vertexShader));
            (glDeleteShader(fragmentShader));

            return false;
        }

        GLuint program;
        (program = glCreateProgram());

        (glAttachShader(program, vertexShader));
        (glAttachShader(program, fragmentShader));

        (glLinkProgram(program));

        GLint isLinked = 0;
        (glGetProgramiv(program, GL_LINK_STATUS, &isLinked));
        if (isLinked == GL_FALSE)
        {
            GLsizei logLength = 0;
            (glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLength));

            GLchar* errorLog = new GLchar[logLength + 1];
            (glGetProgramInfoLog(program, logLength, &logLength, errorLog));

            std::cerr << errorLog << '\n';

            delete[] errorLog;
            (glDeleteProgram(program));

            (glDeleteShader(vertexShader));
            (glDeleteShader(fragmentShader));

            return false;
        }

        (glUseProgram(program));

        (glDeleteShader(vertexShader));
        (glDeleteShader(fragmentShader));

        handleToShader = program;

        return true;
    }

    void Shader::SendUniformVariable(const std::string& variable_name, const matrix3& affine_matrix) noexcept
    {
        (glUniformMatrix3fv(GetUniformLocation(variable_name), 1, GL_FALSE, &affine_matrix.elements[0][0]));
    }

    void Shader::SendUniformVariable(const std::string& variable_name, float number) noexcept
    {
        (glUniform1f(GetUniformLocation(variable_name), number));
    }

    void Shader::SendUniformVariable(const std::string& variable_name, int number) noexcept
    {
        (glUniform1i(GetUniformLocation(variable_name), number));
    }

    void Shader::SendUniformVariable(const std::string& variable_name, Color4f color) noexcept
    {
        (glUniform4f(GetUniformLocation(variable_name), color.red, color.green, color.blue, color.alpha));
    }

    void Shader::Select(const Shader& shader) noexcept { (glUseProgram(shader.GetShaderHandler())); }

    void Shader::SelectNothing() noexcept { (glUseProgram(NULL)); }

    int Shader::GetUniformLocation(const std::string& name) noexcept
    {
        std::map<std::string, int>::iterator temp = uniformNameToLocation.find(name);
        if (temp != uniformNameToLocation.end())
        {
            return temp->second;
        }
        else
        {
            GLuint newLocation = glGetUniformLocation(handleToShader, name.c_str());
            uniformNameToLocation.insert(std::pair<std::string, int>(name, newLocation));
            return newLocation;
        }
    }

    void Shader::Delete() noexcept { (glDeleteProgram(handleToShader)); }